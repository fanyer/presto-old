// Filename: PRINT.C
// "MAP" Generated by WindowsMAKER Professional.
// Author:   TF

#include "core/pch.h"

#include "platforms/windows/windows_ui/printwin.h"

#include "adjunct/quick/dialogs/SimpleDialog.h"

#include "modules/locale/oplanguagemanager.h"
#include "modules/display/prn_dev.h"
#include "modules/doc/frm_doc.h"
#include "modules/locale/oplanguagemanager.h"
#include "modules/display/prn_info.h"

#include "platforms/windows/CustomWindowMessages.h"
#include "platforms/windows/pi/WindowsOpPrinterController.h"
#include "platforms/windows/pi/WindowsOpWindow.h"
#include "platforms/windows/windows_ui/res/resource.h"

extern HINSTANCE hInst;

Window*	source_window = NULL;			// the source window
Window* print_window = NULL;			// window actually being printed

#ifdef PRINT_SELECTION_USING_DUMMY_WINDOW
Window* selection_window = NULL;
#endif

PRINTDLG global_print_dlg;
BOOL printer_initial_landscape;
BOOL printer_current_landscape;

HWND    _hDlgPrintAbort = NULL ;    // handle of print abort dlg box
BOOL    _bPrintAbort ;              // bool is TRUE to abort printing

BOOL CALLBACK PrintStopDlg(HWND hDlg, UINT wMessage, WPARAM wParam, LPARAM lParam) ;
BOOL CALLBACK PrintAbort(HDC hdcPrinter, int nCode) ;

char szPrinter[100];				// Printer name etc.


/***********************************************************************************
**
**	Print a window / document
**
***********************************************************************************/

BOOL cdPrint(Window* window, BOOL use_default)
{
	if (!window)
		return FALSE;
	
	if (window->IsPrinting())
	{
		OpStatus::Ignore(SimpleDialog::ShowDialog(WINDOW_NAME_MESSAGE_DIALOG, NULL, Str::SI_ERR_ALREADY_PRINTING, Str::S_OPERA, Dialog::TYPE_OK, Dialog::IMAGE_ERROR));
		return FALSE;
	}

	DocumentManager* doc_man = window->DocManager();

	if (!doc_man)
		return FALSE;

	FramesDocument* doc = (FramesDocument*)doc_man->GetCurrentDoc();

	if (!doc)
		return FALSE;

	PrinterInfo* printer_info = OP_NEW(PrinterInfo, ());
	if (!printer_info)
		return FALSE;

	PrintDevice* printDevice = NULL;

	window->LockWindow(); // see bug #225957

#ifdef PRINT_SELECTION_USING_DUMMY_WINDOW
	selection_window = NULL;
	printer_info->GetPrintDevice(printDevice, use_default, doc->GetTopDocument()->GetSelectedTextLen(), window, &selection_window);
#else
	printer_info->GetPrintDevice(printDevice, use_default, FALSE, window);
#endif

	if (!printDevice)
	{
#ifdef PRINT_SELECTION_USING_DUMMY_WINDOW
		if (selection_window)
		{
			PostMessage(g_main_hwnd, WM_OPERA_DELAYED_CLOSE_WINDOW, 0, (LPARAM)selection_window);
			selection_window = NULL;
		}
#endif
		OP_DELETE(printer_info);
		window->UnlockWindow();
		return FALSE;
	}

	source_window = window;

#ifdef PRINT_SELECTION_USING_DUMMY_WINDOW
	print_window = selection_window ? selection_window : window;
#else
	print_window = window;
#endif

	source_window->SetState(BUSY);

	HWND hWnd = NULL;
	WindowsOpWindow *src_win = (WindowsOpWindow *)source_window->GetOpWindow();
	if(src_win)
	{
		hWnd = src_win->m_hwnd;
	}
	EnableWindow (GetParent(hWnd), FALSE) ;
	_hDlgPrintAbort = CreateDialog(hInst, LPTSTR(UNI_L("ABORTDLG")), GetParent(hWnd), (DLGPROC)PrintStopDlg);

	_bPrintAbort = FALSE ;

	SetAbortProc(global_print_dlg.hDC, (ABORTPROC) PrintAbort) ;

	// Initialize text to "Printing page..."
    OpString str;
	g_languageManager->GetString(Str::SI_PRINTING_PAGE_TEXT, str);
	if (str.HasContent())
	{
	    HWND h = GetDlgItem(_hDlgPrintAbort, IDM_PRINT_TEXT);
	    if (h) SetWindowText(h, str.CStr());
	}

	// Initialize title to "Print"
	g_languageManager->GetString(Str::DI_ABORTDLG, str);
	if (str.HasContent())
	{
		SetWindowText(_hDlgPrintAbort, str.CStr());
	}

	// Initialize cancel button text
	g_languageManager->GetString(Str::DI_ID_CANCEL, str);
	if (str.HasContent())
	{
	    HWND h = GetDlgItem(_hDlgPrintAbort, IDCANCEL);
	    if (h) SetWindowText(h, str.CStr());
	}


	const uni_char* doctitle = doc->GetWindow()->GetWindowTitle();
	DOCINFO lpdi = {sizeof(DOCINFO), doctitle ? doctitle : UNI_L("Opera"), NULL};

	if (StartDoc(global_print_dlg.hDC, &lpdi) <= 0)
	{
		AbortDoc(global_print_dlg.hDC) ;
		OpStatus::Ignore(SimpleDialog::ShowDialog(WINDOW_NAME_MESSAGE_DIALOG, NULL, Str::SI_ERR_PRINTER_COULD_NOT_START, Str::S_OPERA, Dialog::TYPE_OK, Dialog::IMAGE_ERROR));
		CleanUpAfterPrint(source_window);
	}
	else
		if (printDevice->StartPage())
		{
			if (!print_window->StartPrinting(printer_info, global_print_dlg.nFromPage, global_print_dlg.Flags & PD_SELECTION))
			{
				OpString msg;
				if (OpStatus::IsSuccess(g_languageManager->GetString(Str::SI_ERR_CANNOT_PRINT, msg)))
					OpStatus::Ignore(SimpleDialog::ShowDialog(WINDOW_NAME_MESSAGE_DIALOG, NULL, msg.CStr(), doctitle, Dialog::TYPE_OK, Dialog::IMAGE_ERROR));
				CleanUpAfterPrint(source_window);
			}
		}
		else
		{
			OpStatus::Ignore(SimpleDialog::ShowDialog(WINDOW_NAME_MESSAGE_DIALOG, NULL, Str::SI_ERR_CANNOT_PRINT, Str::S_OPERA, Dialog::TYPE_OK, Dialog::IMAGE_ERROR));
			CleanUpAfterPrint(source_window);
		}

	window->UnlockWindow();
	return TRUE;
}

BOOL cdPrintSetup( HWND hWndParent)
{
	PrinterInfo pi;
	return (BOOL) pi.GetUserPrinterSettings( hWndParent, TRUE, FALSE, FALSE);

}

LONG ucPrintDocFormatted()
{
	if (_hDlgPrintAbort)
	{
		OpString tmp;
	    OpString str;

		g_languageManager->GetString(Str::SI_PRINTING_PAGE_TEXT, str);
		if (str.HasContent())
			tmp.AppendFormat(UNI_L("%s %d..."), str.CStr(), 1);
	    else
	    	tmp.Set("Printing page 1...");

		HWND h = GetDlgItem(_hDlgPrintAbort, IDM_PRINT_TEXT);
	    if (h) SetWindowText(h, tmp);

		print_window->PrintNextPage(print_window->GetPrinterInfo(print_window->GetPreviewMode()));
	}

	return 0;
}

LONG ucPrintPagePrinted(WORD page)
{
    if (_hDlgPrintAbort)
	{
		HWND h = GetDlgItem(_hDlgPrintAbort, IDM_PRINT_TEXT);

	    if (h)
	    {
	    	OpString tmp;
	    	OpString str;

			g_languageManager->GetString(Str::SI_PRINTING_PAGE_TEXT, str);

			if (str.HasContent())
				tmp.AppendFormat(UNI_L("%s %d..."), str.CStr(), page + 1);
	    	else
	    		tmp.AppendFormat(UNI_L("Printing page %d..."), page + 1);

	    	SetWindowText(h, tmp);
	    }

		print_window->PrintNextPage(print_window->GetPrinterInfo(print_window->GetPreviewMode()));
	}
	return 0;
}

void CheckPrinterLandscape(BOOL landscape)
{
	if (printer_current_landscape != landscape)
	{
		printer_current_landscape = landscape;
		DEVMODE* devmode = (DEVMODE*)GlobalLock(global_print_dlg.hDevMode);
		devmode->dmOrientation = (landscape) ? DMORIENT_LANDSCAPE : DMORIENT_PORTRAIT;
		/*HDC hdc =*/ ::ResetDC(global_print_dlg.hDC, devmode);
		GlobalUnlock(global_print_dlg.hDevMode);
	}
}

/***********************************************************************************
**
**	Global printing init and deleting
**
***********************************************************************************/

void InitPrinterSettings(HWND hwnd)
{
 	memset(&global_print_dlg, 0 ,sizeof(PRINTDLG));

    global_print_dlg.lStructSize    = sizeof(PRINTDLG);
    global_print_dlg.hwndOwner      = hwnd;
    global_print_dlg.hDevMode       = NULL;
    global_print_dlg.hDevNames      = NULL;
    global_print_dlg.Flags          = PD_RETURNDC | PD_NOSELECTION | PD_NOPAGENUMS;
    global_print_dlg.nCopies        = 1;
}

void ClearPrinterSettings()
{
    if (global_print_dlg.hDC)
    	DeleteDC(global_print_dlg.hDC);
	if (global_print_dlg.hDevMode != NULL)
    	GlobalFree(global_print_dlg.hDevMode);
	if (global_print_dlg.hDevNames != NULL)
    	GlobalFree(global_print_dlg.hDevNames);
}

/***********************************************************************************
**
**	PrintStopDlg
**
***********************************************************************************/

BOOL CALLBACK PrintStopDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_INITDIALOG:
		{
//			InitDialog(hDlg, Str::DI_ABORTDLG, FALSE, TRUE);
			return TRUE;
		}

		case WM_COMMAND:       
		{
			_bPrintAbort = TRUE;
			return TRUE;
		}
	}

	return FALSE;
}

/***********************************************************************************
**
**	PrintAbort
**
**	the global variable _bPrintAbort is set to TRUE
**	if the user clicks the button on the abort dialog
**	box.  This exits this message loop, returning
**	control back to the program's message loop
**
***********************************************************************************/

BOOL CALLBACK PrintAbort (HDC hdcPrinter, int nCode)
{
    MSG msg ;
    while (!_bPrintAbort && PeekMessage (&msg, _hDlgPrintAbort, 0, 0, PM_REMOVE))
		if (!_hDlgPrintAbort || !IsDialogMessage (_hDlgPrintAbort, &msg))
        {
            TranslateMessage (&msg) ;
            DispatchMessage (&msg) ;
        }

	return (!_bPrintAbort) ;
}

LONG ucPrintingFinished(Window* window)
{
	PrinterInfo* printer_info = window ? window->GetPrinterInfo(window->GetPreviewMode()) : NULL;

	if (printer_info && printer_info->GetPrintDevice() && printer_info->GetPrintDevice()->GetPrinterController())
		printer_info->GetPrintDevice()->GetPrinterController()->EndPage();
	else
		EndPage(global_print_dlg.hDC);
	CheckPrinterLandscape(printer_initial_landscape);
	EndDoc(global_print_dlg.hDC);
	CleanUpAfterPrint(source_window);
	return 0;
}

LONG ucPrintingAborted(Window* window)
{
	PrinterInfo* printer_info = window ? window->GetPrinterInfo(window->GetPreviewMode()) : NULL;

	if (printer_info)
	{
		if (printer_info && printer_info->GetPrintDevice() && printer_info->GetPrintDevice()->GetPrinterController())
			printer_info->GetPrintDevice()->GetPrinterController()->EndPage();
		else
			EndPage(global_print_dlg.hDC);
		CheckPrinterLandscape(printer_initial_landscape);
		EndDoc(global_print_dlg.hDC);
		CleanUpAfterPrint(source_window);
	}

	return 0;
}

void CleanUpAfterPrint(Window* window)
{
	HWND hWnd = NULL;
	WindowsOpWindow *src_win = (WindowsOpWindow *)source_window->GetOpWindow();
	if(src_win)
	{
		hWnd = src_win->m_hwnd;
	}
	EnableWindow (GetParent(hWnd), TRUE);

    if (_hDlgPrintAbort)
		DestroyWindow(_hDlgPrintAbort);
    
	if (print_window)
	{
		print_window->StopPrinting();
		print_window = NULL;
	}

    source_window->SetState(NOT_BUSY);

	// in preview mode "preview_printer_info" field is used and it's lifetime is controlled
	// in Window::TogglePrintMode function
	if (window && !window->GetPreviewMode())
	{
		OP_DELETE(window->GetPrinterInfo(FALSE));
		window->SetPrinterInfo(NULL);
	}

	if (global_print_dlg.hDC)
	{
		DeleteDC(global_print_dlg.hDC);
		global_print_dlg.hDC = NULL;
	}

#ifdef PRINT_SELECTION_USING_DUMMY_WINDOW
	if (selection_window)
	{
		PostMessage(g_main_hwnd, WM_OPERA_DELAYED_CLOSE_WINDOW, 0, (LPARAM)selection_window);
		selection_window = NULL;
	}
#endif

	source_window = NULL;
}


/***********************************************************************************
**
**	Print Preview dialog
**
***********************************************************************************/
/*
int BLD_PrintPreviewModeDlgFunc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    return DialogBox(hInst,LPTSTR(UNI_L("PRINTPREVIEWMODE")), hWnd,BLD_PrintPreviewDlgProc);
}

BOOL BLD_CALLBACK BLD_PrintPreviewDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static Window* window;

	switch(message)
	{
		case WM_INITDIALOG:
		{
			InitDialog(hDlg, Str::DI_PRINTPREVIEWMODE, FALSE, TRUE);
			
			if (windowManager)
			{
				window = windowManager->GetActiveWindow();

				if (window)
				{
					Document* cDoc = window->GetCurrentDoc();
		
					if (cDoc)
					{
						OP_ASSERT(cDoc->IsFrameDoc());
						CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ASSCREEN, TRUE);
						CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ALLFRAMES, FALSE);
						EnableWindow(GetDlgItem(hDlg, IDM_PRINT_CURDOC_ACTIVEFRM), cDoc->GetActiveDocManager() != NULL);
					}
				}
			}

			return TRUE;
		}

		case WM_COMMAND:       
		{
			int id = LOWORD(wParam);
			int notification = HIWORD(wParam);

			switch(id)
			{
				case IDCANCEL:
				{
					switch (notification)
					{
						case BN_CLICKED:
							EndDialog(hDlg,IDCANCEL);
							return TRUE;
					}
					break;
				}

				case IDOK:
				{
					switch (notification)
					{
						case BN_CLICKED:
						{
							if(IsDlgButtonChecked(hDlg, IDM_PRINT_CURDOC_ASSCREEN) == BST_CHECKED)
							{
								window->SetFramesPrintType(PRINT_AS_SCREEN, TRUE);
							}
							else if(IsDlgButtonChecked(hDlg, IDM_PRINT_CURDOC_ALLFRAMES) == BST_CHECKED)
							{
								window->SetFramesPrintType(PRINT_ALL_FRAMES, TRUE);
							}
							else if(IsDlgButtonChecked(hDlg, IDM_PRINT_CURDOC_ACTIVEFRM) == BST_CHECKED)
							{
								window->SetFramesPrintType(PRINT_ACTIVE_FRAME, TRUE);			
							}
							window->TogglePrintMode(TRUE);
							EndDialog(hDlg,IDOK);
							return TRUE;
						}
					}
					break;
				}

				case IDM_HELP:
				{
					switch (notification)
					{
						case BN_CLICKED:
							return TRUE;
					}
					break;
				}

				case  IDM_PRINT_CURDOC_ASSCREEN:
				{
					switch(notification)
					{
						case BN_DOUBLECLICKED:
							window->SetFramesPrintType(PRINT_AS_SCREEN, TRUE);
						case BN_CLICKED:
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ASSCREEN, TRUE);
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ALLFRAMES, FALSE);
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ACTIVEFRM, FALSE);
							return TRUE;
					}
					break;
				}
					
				case IDM_PRINT_CURDOC_ALLFRAMES:
				{
					switch(notification)
					{
						case BN_DOUBLECLICKED:
							window->SetFramesPrintType(PRINT_ALL_FRAMES, TRUE);
						case BN_CLICKED:
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ASSCREEN, FALSE);
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ALLFRAMES, TRUE);
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ACTIVEFRM, FALSE);
							return TRUE;
					}
					break;
				}
				case IDM_PRINT_CURDOC_ACTIVEFRM:
				{
					switch(notification)
					{
						case BN_DOUBLECLICKED:
							window->SetFramesPrintType(PRINT_ACTIVE_FRAME, TRUE);
						case BN_CLICKED:
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ASSCREEN, FALSE);
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ALLFRAMES, FALSE);
							CheckDlgButton(hDlg, IDM_PRINT_CURDOC_ACTIVEFRM, TRUE);
							return TRUE;
					}
					break;
				}
			}

			break;
		}
	}

	return FALSE;
}
*/
