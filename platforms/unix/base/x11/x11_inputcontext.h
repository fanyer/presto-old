/* -*- Mode: c++; tab-width: 4; c-basic-offset: 4 -*-
 *
 * Copyright (C) 1995-2010 Opera Software AS.  All rights reserved.
 *
 * This file is part of the Opera web browser.
 * It may not be distributed under any circumstances.
 *
 * @author Arjan van Leeuwen (arjanl)
 */

#ifndef X11_INPUT_CONTEXT
#define X11_INPUT_CONTEXT

#include "platforms/utilix/x11_all.h"
#include "platforms/quix/utils/DebugLogger.h"

class OpInputMethodListener;
class OpInputMethodString;
class X11Widget;
struct IM_WIDGETINFO;
class X11InputMethod;

/** @brief Represents an X11 input context (XIC) and operations that can be executed on it
  */
class X11InputContext
{
public:
	/** Constructor
	  */
	X11InputContext();
	~X11InputContext();

	/** Initialize this input context.
	  * @param im Input method parameters to use when creating the XIC.
	  * @param window Window to handle input events for.
	  * @return OpStatus::OK on success, error codes otherwise
	  */
	OP_STATUS Init(X11InputMethod * im, X11Widget * window=0);

	/** Activate this input context and send IM events
	  * @param listener Listener to send IM events to
	  */
	void Activate(OpInputMethodListener* listener);

	/** Deactivate this input context and stop sending IM events
	  * @param listener Listener to stop sending IM events to
	  */
	void Deactivate(OpInputMethodListener* listener);

	/** Abort ongoing text compose
	  */
	void Abort();

	/** Set focus window for this input context
	  * @param window Window that has input focus
	  */
	void SetFocusWindow(X11Widget * window);

	/** Give the input context focus if this X11InputContext is
	 * currently activated.  This should typically be called to undo
	 * the effect of UnsetFocus().
	 */
	void SetFocusIfActive();

	/**
	 * Give the input context focus.
	 */
	void SetFocus();

	/** Take away the input context focus.  The focus should be unset
	 * when the window it belongs to loses ordinary keyboard focus.
	 */
	void UnsetFocus();

	/** Decode the key event in 'event', in the context of this input
	 * context.
	 *
	 * @param event Keypress event to decode.
	 *
	 * @param keysym Keysym of the key press, NoSymbol if the event
	 * does not represent a valid keysym.  But see return value.
	 *
	 * @param text The text generated by the key press, empty if no
	 * text is generated.  But see return value.
	 *
	 * @return true on successful decoding, false on error.  If this
	 * method returns true and produces the keysym NoSymbol and an
	 * empty 'text', the key event has been handled and should be
	 * dropped.  If this method returns false, 'keysym' and 'text' are
	 * undefined.
	 */
	bool GetKeyPress(XEvent* event, KeySym& keysym, OpString& text);

	/** Informs this object that the X11InputMethod object that was
	 * used in Init() is no longer valid and should not be accessed
	 * any more.
	 */
	void InputMethodIsDeleted();

	/** Informs this object that the XIM passed to Init() has been
	 * destroyed.  The X11InputMethod object is still alive, but the
	 * XIM and all XICs created from it have been deleted and should
	 * not be accessed any more.  They should not even be closed by
	 * calling XCloseIM() or XDestroyIC().
	 */
	void XIMHasBeenDestroyed();

private:
	struct CallbackList
	{
		XVaNestedList list;
		OpAutoVector<XIMCallback> callbacks;

		CallbackList() : list(0) {}
		~CallbackList() { if (list) XFree(list); }
	};

	OP_STATUS CreatePreeditList(CallbackList& list);
	OP_STATUS CreateStatusList(CallbackList& status);
	OP_STATUS AddToCallbacks(CallbackList& list, XIMProc callback_func);

	/** Tell the input method where the text input area is.
	 */
	void SetTextArea(const IM_WIDGETINFO & wi);

	/** Remove all indications about where the currently active text
	 * input area is.
	 */
	void ResetTextArea();

	/** Sets up Opera to be in compose mode (if it isn't already)
	  * @return whether this was successful
	  */
	bool StartComposing();

	/** Exits compose mode in Opera.
	 *
	 * If cancel is false, the current pre-edit string will be
	 * committed, otherwise the current pre-edit string will be
	 * cleared.
	 */
	void StopComposing(bool cancel=false);

	/** Whether Opera is in compose mode */
	bool IsComposing() { return m_listener && m_string; }

	void PreeditStart();
	void PreeditDone();
	void PreeditDraw(XIMPreeditDrawCallbackStruct* data);
	void DeleteFromPreedit(int pos, int length);
	void InsertIntoPreedit(int pos, const uni_char* string, int length);
	void InsertIntoPreedit(int pos, const char* string, int length);
	void DeterminePreeditUnderline(XIMFeedback* feedback, unsigned length);
	void PreeditCaret(XIMPreeditCaretCallbackStruct* data);
	void StatusStart();
	void StatusDone();
	void StatusDraw(XIMStatusDrawCallbackStruct* data);

	// Callbacks passed to XIC
	static int PreeditStartCallback(XIC ic, X11InputContext* input_context, XPointer call_data) { input_context->PreeditStart(); return 1024; }
	static void PreeditDoneCallback(XIC ic, X11InputContext* input_context, XPointer call_data) { input_context->PreeditDone(); }
	static void PreeditDrawCallback(XIC ic, X11InputContext* input_context, XIMPreeditDrawCallbackStruct* call_data) { input_context->PreeditDraw(call_data); }
	static void PreeditCaretCallback(XIC ic, X11InputContext* input_context, XIMPreeditCaretCallbackStruct* call_data) { input_context->PreeditCaret(call_data); }
	static void StatusStartCallback(XIC ic, X11InputContext* input_context, XPointer call_data) { input_context->StatusStart(); }
	static void StatusDoneCallback(XIC ic, X11InputContext* input_context, XPointer call_data) { input_context->StatusDone(); }
	static void StatusDrawCallback(XIC ic, X11InputContext* input_context, XIMStatusDrawCallbackStruct* call_data) { input_context->StatusDraw(call_data); }

	XIC m_xic;
	X11InputMethod * m_im;
	OpString8 m_keybuf;
	OpInputMethodListener* m_listener;
	OpInputMethodString* m_string;
	X11Widget * m_focus_window;
	DebugLogger m_logger;
};

#endif // X11_INPUT_CONTEXT
