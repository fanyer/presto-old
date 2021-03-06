// Bidi.cpp - version 26

// A note on updating this file: An unmodified copy of the current version of
// this file is kept as bidi_reference.cpp.dist in this directory. When
// upgrading, it is probably simplest to take a diff between it and the
// new version of the reference implementation, and then update this file
// accordingly.
//
// If there are changes in the "phony" bi-di alphabet (see TypesFromChar below),
// please make sure to update the selftests in bidiutils.ot accordingly.

#include "core/pch.h"
#ifdef SELFTEST
# define TCHAR char
# define LPTSTR char *
# define ASSERT OP_ASSERT
#endif

// Reference implementation for Unicode Bidirectional Algorithm

// Set BIDI_REFERENCE_WINDOWS_UI to 0 to get commandline UI
// Set BIDI_REFERENCE_WINDOWS_UI to 1 for generic win 32 dialog
// Set BIDI_REFERENCE_WINDOWS_UI to 2 for private build
#ifndef BIDI_REFERENCE_WINDOWS_UI
#define BIDI_REFERENCE_WINDOWS_UI 3
#endif

// Bidi include file
#if defined(SELFTEST) && defined(SUPPORT_TEXT_DIRECTION)

#include "modules/unicode/testsuite/bidi_reference.h"

// Set to 0 for default
// Set to 1 to run in debug mode
#ifndef BIDI_REFERENCE_DEBUGGING
#define BIDI_REFERENCE_DEBUGGING 0
#else
#define BIDI_REFERENCE_DEMO 1
#endif
// Debug mode enables Demo mode
// Debug mode enables Table checks


// Set to 1 if demo operation is
// desired outside debug mode
#ifndef BIDI_REFERENCE_DEMO
#define BIDI_REFERENCE_DEMO 0
#endif

// Demo mode restricts levels to 15

/*------------------------------------------------------------------------
	File: Bidi.Cpp

	Description
	-----------

	Sample Implementation of the Unicode Bidirectional Algorithm as it
	was revised by Revision 5 of the Uniode Technical Report # 9
	(1999-8-17)

	Verified for changes to the algorithm up through Unicode 5.2.0 (2009).

	This implementation is organized into several passes, each implemen-
	ting one or more of the rules of the Unicode Bidi Algorithm. The
	resolution of Weak Types and of Neutrals each use a state table
	approach.

	Both a printf based interface and a Windows DlgProc are provided for
	interactive testing.

	A stress harness comparing this implementation (v24) to a Java based 
	implementation was used by Doug Felt to verify that the two 
	implementations produce identical results for all strings up to six
	bidi classes and stochastic strings up to length 20.

	Version 26 was verified by the author against the Unicode 5.2.0
	file BidiTest.txt, which provides an exhaustive text of strings of
	length 4 or less, but covers some important cases where the language
	in UAX#9 had been clarified.

	To see this code running in an actual Windows program,
	download the free Unibook uitlity from http://unicode.org/unibook
	The bidi demo is executed from the tools menu. It is build from
	this source file.

	Build Notes
	-----------

	To compile the sample implementation please set the #define
	directives above so the correct headers get included. Not all the
	files are needed for all purposes. For the commandline version
	only bidi.h and bidi.cpp are needed.

	The Win32 version is provided as a dialog procedure. To use as a
	standalone program compile with the the lbmain.cpp file. If all you
	need is the ability to run the code "as is", you can instead download
	the unibook utility from http://uincode.org/unibook/ which contains
	the bidi demo compiled from this source file.

	This code uses an extension to C++ that gives variables declared in
	a for() statement function the same scope as the for() statement.
	If your compiler does not support this extension, you may need to
	move the declaration, e.g. int ich = 0; in front of the for statement.

	Implementation Note
	-------------------

	NOTE: The Unicode Bidirectional Algorithm removes all explicit
		formatting codes in rule X9, but states that this can be
		simulated by conformant implementations. This implementation
		attempts to demonstrate such a simulation

		To demonstrate this, the current implementation does the
		following:

		in resolveExplicit()
			- change LRE, LRO, RLE, RLO, PDF to BN
			- assign nested levels to BN

		in resolveWeak and resolveNeutrals
			- assign L and R to BN's where they exist in place of
			  sor and eor by changing the last BN in front of a
			  level change to a strong type
			- skip over BN's for the purpose of determining actions
			- include BN in the count of deferred runs
				which will resolve some of them to EN, AN and N

		in resolveWhiteSpace
			- set the level of any surviving BN to the base level,
				or the level of the preceding character
			- include LRE,LRO, RLE, RLO, PDF and BN in the count
			   whitespace to be reset

		This will result in the same order for non-BN characters as
		if the BN characters had been removed.

		The clean() function can be used to remove boundary marks for
		verification purposes.

	Notation
	--------
	Pointer variables generally start with the letter p
	Counter variables generally start with the letter c
	Index variables generally start with the letter i
	Boolean variables generally start with the letter f

	The enumerated bidirectional types have the same name as in the
	description for the Unicode Bidirectional Algorithm


	Using this code outside a demo context
	--------------------------------------

	The way the functions are broken down in this demo code is based
	on the needs of the demo to show the evolution in internal state
	as the algorithm proceeds. This obscures how the algorithm would
	be used in practice. These are the steps:

	1. Allocate a pair of arrays large enough to hold bidi class
	   and calculated levels (one for each input character)

	2. Provide your own function to assign directional types (bidi
	   classes) corresponding to each character in the input,
	   conflating ON, WS, S to N. Unlike the classify function in this
	   demo, the input would be actual Unicode characters.

	3. Process the first paragraph by calling BidiParagraph. That 
	   function changes B into BN and returns a length including the 
	   paragraph separator. (The iteration over multiple paragraphs 
	   is left as excercise for the reader). 
	
	4. Assign directional types again, but now assign specific types
	   to whitespace characters.

	5. Instead of reordering the input in place it is often desirable
	   to calculate an array of offsets indicating the reordering.
	   To that end, allocate such an array here and use it instead
	   of the input array in the next step.
	
	6. Resolve and reorder the lines by calling BidiLines. That 
	   function 'breaks' lines on LS characters. Provide an optional
	   array of flags indicating the location of other line breaks as
	   needed.


	Update History
	--------------
	Version 24 is the initial published and verified version of this
	reference implementation. Version 25 and its updates fix various
	minor issues with the scaffolding used for demonstrating the
	algorithm using pseudo-alphabets from the command line or dialog
	box. No changes to the implementation of the actual bidi algrithm
	are made in any of the minor updates to version 25. Version 26
	also makes no change to the actual algorithm but was verified
	against the official BidiTest.txt file for Unicode 5.2.0.

	- updated pseudo-alphabet

	- Last Revised 12-10-99 (25)

	- enable demo mode for release builds - no other changes

	- Last Revised 12-10-00 (25a)

	- fix regression in pseudo alphabet use for Windows UI

	- Last Revised 02-01-01 (25b)

	- fixed a few comments, renamed a variable

	- Last Revised 03-04-01 (25c)

	- make base level settable, enable mirror by default,
	fix dialog size

	- Last Revised 06-02-01 (25e)

	- fixed some comments

	- Last Revised 09-29-01 (25f)

	- fixed classification for LS,RLM,LRM in pseudo alphabet,
	focus issues in UI, regression fix to commandline from 25(e)
	fix DEMO switch

	- Last Revised 11-07-01 (25g)

	- fixed classification for plus/minus in pseudo alphabet
	to track changes made in Unicode 4.0.1

	- Last Revised 12-03-04 (25h)

	- now compiles as dialog-only program for BIDI_REFERENCE_WINDOWS_UI==1
	using new bidimain.cpp

	- Last Revised 12-02-07 (25i)

	- cleaned up whitespace and indenting in the source, 
	fixed two comments (table headers)

	- Last Revised 15-03-07 (25j)

	- named enumerations

	- Last Revised 30-05-07 (25k)

	- added usage notes, minor edits to comments, indentation, etc
	throughout. Added the bidiParagraph function. Checked against 
	changes in the Unicode Bidi Algorithm for Unicode 5.2.0. No
	changes needed to this implementation to match the values in
	the BidiTest.txt file in the Unicode Character Database.
	Minor fixes to dialog/windows proc, updated preprocessor directives.

	- Last Revised 03-08-09 (26)

	Credits:
	-------
	Written by: Asmus Freytag
	Command line interface by: Rick McGowan
	Verification (v24): Doug Felt

	Disclaimer and legal rights:
	---------------------------
	Copyright (C) 1999-2009, ASMUS, Inc. All Rights Reserved.
	Distributed under the Terms of Use in http://www.unicode.org/copyright.html.

	THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
	IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE
	BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES,
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
	WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
	ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE SOFTWARE.

	The file bid.rc is included in the software covered by the above.
------------------------------------------------------------------------*/


// === HELPER FUNCTIONS AND DECLARATIONS =================================

#define odd(x) ((x) & 1)

/*------------------------------------------------------------------------
	Bidirectional Character Types

	as defined by the Unicode Bidirectional Algorithm Table 3-7.

	Note:

	  The list of bidirectional character types here is not grouped the
	  same way as the table 3-7, since the numberic values for the types
	  are chosen to keep the state and action tables compact.
------------------------------------------------------------------------*/
enum bidi_class
{
	// input types
			 // ON MUST be zero, code relies on ON = N  = 0
	CT_ON = 0,  // Other Neutral
	CT_L,		 // Left Letter
	CT_R,		 // Right Letter
	CT_AN, 	 // Arabic Number
	CT_EN, 	 // European Number
	CT_AL, 	 // Arabic Letter (Right-to-left)
	CT_NSM,	 // Non-spacing Mark
	CT_CS, 	 // Common Separator
	CT_ES, 	 // European Separator
	CT_ET, 	 // European Terminator (post/prefix e.g. $ and %)

	// resolved types
	CT_BN, 	 // Boundary neutral (type of RLE etc after explicit levels)

	// input types,
	CT_S,		 // Segment Separator (TAB)		// used only in L1
	CT_WS, 	 // White space					// used only in L1
	CT_B,		 // Paragraph Separator (aka as PS)

	// types for explicit controls
	CT_RLO,	 // these are used only in X1-X9
	CT_RLE,
	CT_LRO,
	CT_LRE,
	CT_PDF,

	// resolved types, also resolved directions
	CT_N  = CT_ON,  // alias, where ON, WS and S are treated the same
};

/*----------------------------------------------------------------------
	The following array maps character codes to types for the purpose of
	this sample implementation. The legend string gives a human readable
	explanation of the pseudo alphabet.

	For simplicity, characters entered by buttons are given a 1:1 mapping
	between their type and pseudo character value. Pseudo characters that
	can be typed from the keyboard are explained in the legend string.

	Use the Unicode Character Database for the real values in real use.
 ---------------------------------------------------------------------*/

#if BIDI_REFERENCE_WINDOWS_UI > 0 && BIDI_REFERENCE_WINDOWS_UI < 3
const TCHAR legend[] =
TEXT("This sample uses the following pseudo-alphabet as input\r\n")
TEXT("Excplicit: LRE: [ RLE: ] LRO: { RLO: } PDF: 0x12,^ \r\n")
TEXT("Strong:    AL: A-F  R:  0x17,G-Z  L:  0x16,a-z   LRM: <btn>   RLM: <btn> \r\n")
TEXT("Numeric:   EN: 0-5  AN: 6-9       CS: [comma],.,: ES: /,+,-   ET: #,$,%  \r\n")
TEXT("Neutral:   WS: 0xc,0x15,[space]   ON: !,\",&,',(,),*,;,<,=,>,?,@,\\,0x7f \r\n")
TEXT("Special:   NSM: `   B: |    S: _  BN: ~ ");
#endif

const int chLRM = 4;
const int chRLM = 5;
const int chLS = 0x15;
const int chRLO = '}';
const int chLRO = '{';
const int chRLE = ']';
const int chLRE = '[';
const int chPDF = '^';
const int chBN	= '~';

int TypesFromChar[]  =
{

//0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
 CT_BN, CT_BN, CT_BN, CT_BN,  CT_L,  CT_R, CT_BN, CT_BN, CT_BN,  CT_S,  CT_B,  CT_S, CT_WS,  CT_B, CT_BN, CT_BN, /*00-0f*/
CT_LRO,CT_LRE,CT_PDF,CT_RLO,CT_RLE, CT_WS,  CT_L,  CT_R, CT_BN, CT_BN, CT_BN, CT_BN,  CT_B,  CT_B,  CT_B,  CT_S, /*10-1f*/
 CT_WS, CT_ON, CT_ON, CT_ET, CT_ET, CT_ET, CT_ON, CT_ON, CT_ON, CT_ON, CT_ON, CT_ES, CT_CS, CT_ES, CT_CS, CT_ES, /*20-2f*/
 CT_EN, CT_EN, CT_EN, CT_EN, CT_EN, CT_EN, CT_AN, CT_AN, CT_AN, CT_AN, CT_CS, CT_ON, CT_ON, CT_ON, CT_ON, CT_ON, /*30-3f*/
 CT_ON, CT_AL, CT_AL, CT_AL, CT_AL, CT_AL, CT_AL,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R, /*40-4f*/
  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,  CT_R,CT_LRE, CT_ON,CT_RLE,CT_PDF,  CT_S, /*50-5f*/
CT_NSM,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L, /*60-6f*/
  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,  CT_L,CT_LRO,  CT_B,CT_RLO, CT_BN, CT_ON, /*70-7f*/
};


/***************************************
	Reverse, human readable reference:
	
	LRM:	0x4
	RLM:	0x5
	  L:	0x16,a-z
	LRE:	0x11,[
	LRO:	0x10,{
	  R:	0x17,G-Z
	 AL:	A-F
	RLE:	0x14,]
	RLO:	0x13,}
	PDF:	0x12,^
	 EN:	0-5
	 ES:	/,+,[hyphen]
	 ET:	#,$,%
	 AN:	6-9
	 CS:	[comma],.,:
	NSM:	`
	 BN:	0x0-0x8,0xe,0xf,0x18-0x1b,~
	  B:	0xa,0xd,0x1c-0x1e,|
	  S:	0x9,0xb,0x1f,_
	 WS:	0xc,0x15,[space]
	 ON:	!,",&,',(,),*,;,<,=,>,?,@,\,0x7f
****************************************/

// WS, LS and S are not explicitly needed except for L1. Therefore this
// table conflates ON, S, WS, and LS to N, all others unchanged
int NTypes[] = {
	CT_N ,		// ON,
	CT_L,		// L,
	CT_R,		// R,
	CT_AN, 	// AN,
	CT_EN, 	// EN,
	CT_AL, 	// AL
	CT_NSM,	// NSM
	CT_CS, 	// CS
	CT_ES, 	// ES
	CT_ET, 	// ET
	CT_BN, 	// BN
	CT_N ,		// S
	CT_N ,		// WS
	CT_B,		// B
	CT_RLO,	// RLO
	CT_RLE,	// RLE
	CT_LRO,	// LRO
	CT_LRE,	// LRE
	CT_PDF,	// PDF
	CT_ON,		// LS
};

int ClassFromChN(TCHAR ch)
{
	ASSERT(ch < 0x7f && ch >= 0);
	return NTypes[TypesFromChar[ch & 0x7f]];
}

int ClassFromChWS(TCHAR ch)
{
	ASSERT(ch < 0x7f && ch >= 0);
	return TypesFromChar[ch & 0x7f];
}

// === DISPLAY SUPPORT =================================================

#if BIDI_REFERENCE_WINDOWS_UI < 1 || defined(SELFTEST)
	enum display_symbol	// Display character codes
	{
		RIGHT = '<',			// rtl arrow
		LEFT = '>',				// ltr arrow
		PUSH = '+',				// dn arrow
		POP = '-',				// up arrow
		LSEP =	'=',			// double dagger
		NEUTRAL = ' ',			// rtl/ltr dbl headed arrow
		ALPHA = 'a',
	};
#else
	enum display_symbol	// Display character codes
	{
		RIGHT = 0x2190, 		 // rtl arrow
		LEFT = 0x2192,			 // rtl arrow
		PUSH = 0x2193,			 // dn arrow
		POP = 0x2191,			 // up arrow
		LSEP =	0x2021,			 // double dagger
		NEUTRAL = 0x2194,		 // rtl/ltr dbl headed arrow
		ALPHA = 0x03B1,			 // greek alpha
	};
#endif

// display support:
TCHAR CharFromTypes[] =
{
	NEUTRAL,	// ON,
	LEFT,		// L,
	RIGHT,		// R,
	'9',		// AN,
	'1',		// EN,
	ALPHA,		// AL
	'@',		// NSM
	'.',		// CS
	',',		// ES
	'$',		// ET
	':',		// BN
	'X',		// S
	'_',		// WS
	'B',		// B
	PUSH,		// RLO
	PUSH,		// RLE
	PUSH,		// LRO
	PUSH,		// LRE
	POP,		// PDF
	LSEP,		// LS

};


// This works only for testing
// a full implementation would need 61 levels....
TCHAR CharFromLevel[] =
{
	'0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E',
	'F', 'X', 'Y', 'Z'		// overhang levels
};

// === HELPER FUNCTIONS ================================================

// reverse cch characters
void reverse(LPTSTR psz, int cch)
{
	TCHAR chTemp;

	for (int ich = 0; ich < --cch; ich++)
	{
		chTemp = psz[ich];
		psz[ich] = psz[cch];
		psz[cch] = chTemp;
	}
}

// Set a run of cval values at locations all prior to, but not including
// iStart, to the new value nval.
void SetDeferredRun(int *pval, int cval, int iStart, int nval)
{
	for (int i = iStart - 1; i >= iStart - cval; i--)
	{
		pval[i] = nval;
	}
}

// === ASSIGNING BIDI CLASSES ============================================

/*------------------------------------------------------------------------
	Function: classify

	Determines the character classes for all following
	passes of the algorithm

	Input: Text string
		   Character count
		   Whether to report types as CT_WS, CT_ON, CT_S or as CT_N  (false)

	Output: Array of directional classes
------------------------------------------------------------------------*/
int classify(const LPTSTR pszText, int * pcls,	int cch, bool fWS = false)
{
	if (fWS)
	{
		int ich;
		for (ich = 0; ich < cch; ich++)
		{
			pcls[ich] = ClassFromChWS(pszText[ich]);
		}
		return ich;
	}
	else
	{
		int ich;
		for (ich = 0; ich < cch; ich++)
		{
			pcls[ich] = ClassFromChN(pszText[ich]);
		}
		return ich;
	}
}

// === THE PARAGRAPH LEVEL ===============================================

/*------------------------------------------------------------------------
	Function: resolveParagraphs

	Resolves the input strings into blocks over which the algorithm
	is then applied.

	Implements Rule P1 of the Unicode Bidi Algorithm

	Input: Text string
		   Character count

	Output: revised character count

	Note:	This is a very simplistic function. In effect it restricts
			the action of the algorithm to the first paragraph in the input
			where a paragraph ends at the end of the first block separator
			or at the end of the input text.

------------------------------------------------------------------------*/

int resolveParagraphs(int * types, int cch)
{
	// skip characters not of type B
	int ich;
	for(ich = 0; ich < cch && types[ich] != CT_B; ich++)
		;
	// stop after first B, make it a BN for use in the next steps
	if (ich < cch && types[ich] == CT_B)
		types[ich++] = CT_BN;
	return ich;
}

/*------------------------------------------------------------------------
	Function: baseLevel

	Determines the base level

	Implements rule P2 of the Unicode Bidi Algorithm.

	Input: Array of directional classes
		   Character count

	Note: Ignores explicit embeddings
------------------------------------------------------------------------*/
int baseLevel(const int * pcls,  int cch)
{
	for (int ich = 0; ich < cch; ich++)
	{
		switch (pcls[ich])
		{
		// strong left
		case CT_L:
			return 0;
			break;

		// strong right
		case CT_R:
		case CT_AL:
			return 1;
			break;
		}
	}
	return 0;
}

//====== RESOLVE EXPLICIT ================================================

int GreaterEven(int i)
{
	return odd(i) ? i + 1 : i + 2;
}

int GreaterOdd(int i)
{
	return odd(i) ? i + 2 : i + 1;
}

int EmbeddingDirection(int level)
{
	return odd(level) ? CT_R : CT_L;
}


/*------------------------------------------------------------------------
	Function: resolveExplicit

	Recursively resolves explicit embedding levels and overrides.
	Implements rules X1-X9, of the Unicode Bidirectional Algorithm.

	Input: Base embedding level and direction
		   Character count

	Output: Array of embedding levels
		  Caller must allocate (one level per input character)

	In/Out: Array of direction classes


	Note: The function uses two simple counters to keep track of
		  matching explicit codes and PDF. Use the default argument for
		  the outermost call. The nesting counter counts the recursion
		  depth and not the embedding level.
------------------------------------------------------------------------*/
#if BIDI_REFERENCE_DEMO
const int MAX_LEVEL = 15; // leave at the smaller level so we can test hitting
					  // the limit more easily in interactive mode
#else
const int MAX_LEVEL = 61; // the real value
#endif

int resolveExplicit(int level, int dir, int * pcls, int * plevel, int cch,
					int nNest = 0)
{
	// always called with a valid nesting level
	// nesting levels are != embedding levels
	int nLastValid = nNest;

	// check input values
	ASSERT(nNest >= 0 && level >= 0 && level <= MAX_LEVEL);

	// process the text
	int ich;
	for (ich = 0; ich < cch; ich++)
	{
		int cls = pcls[ich];
		switch (cls)
		{
		case CT_LRO:
		case CT_LRE:
			nNest++;
			if (GreaterEven(level) <= MAX_LEVEL)
			{
				plevel[ich] = GreaterEven(level);
				pcls[ich] = CT_BN;
				ich += resolveExplicit(plevel[ich], (cls == CT_LRE ? CT_N  : CT_L),
							&pcls[ich+1], &plevel[ich+1],
							 cch - (ich+1), nNest);
				nNest--;
				continue;
			}
			cls = pcls[ich] = CT_BN;
			break;

		case CT_RLO:
		case CT_RLE:
			nNest++;
			if (GreaterOdd(level) <= MAX_LEVEL)
			{
				plevel[ich] = GreaterOdd(level);
				pcls[ich] = CT_BN;
				ich += resolveExplicit(plevel[ich], (cls == CT_RLE ? CT_N  : CT_R),
								&pcls[ich+1], &plevel[ich+1],
								 cch - (ich+1), nNest);
				nNest--;
				continue;
			}
			cls = pcls[ich] = CT_BN;
			break;

		case CT_PDF:
			cls = pcls[ich] = CT_BN;
			if (nNest)
			{
				if (nLastValid < nNest)
				{
					nNest--;
				}
				else
				{
					cch = ich; // break the loop, but complete body
				}
			}
			break;
		}

		// Apply the override
		if (dir != CT_N )
		{
			cls = dir;
		}
		plevel[ich] = level;
		if (pcls[ich] != CT_BN)
			pcls[ich] = cls;
	}

	return ich;
}

// === RESOLVE WEAK TYPES ================================================

enum bidi_state // possible states
{
	xa,		//	arabic letter
	xr,		//	right leter
	xl,		//	left letter

	ao,		//	arabic lett. foll by ON
	ro,		//	right lett. foll by ON
	lo,		//	left lett. foll by ON

	rt,		//	ET following R
	lt,		//	ET following L

	cn,		//	EN, AN following AL
	ra,		//	arabic number foll R
	re,		//	european number foll R
	la,		//	arabic number foll L
	le,		//	european number foll L

	ac,		//	CS following cn
	rc,		//	CS following ra
	rs,		//	CS,ES following re
	lc,		//	CS following la
	ls,		//	CS,ES following le

	ret,	//	ET following re
	let,	//	ET following le
} ;

int stateWeak[][10] =
{
	//	N ,  L,  R,  AN, EN, AL,NSM, CS, ES, ET,
{/*xa*/	ao, xl, xr, cn, cn, xa, xa, ao, ao, ao, /* arabic letter		  */},
{/*xr*/	ro, xl, xr, ra, re, xa, xr, ro, ro, rt, /* right letter 		  */},
{/*xl*/	lo, xl, xr, la, le, xa, xl, lo, lo, lt, /* left letter			  */},

{/*ao*/	ao, xl, xr, cn, cn, xa, ao, ao, ao, ao, /* arabic lett. foll by ON*/},
{/*ro*/	ro, xl, xr, ra, re, xa, ro, ro, ro, rt, /* right lett. foll by ON */},
{/*lo*/	lo, xl, xr, la, le, xa, lo, lo, lo, lt, /* left lett. foll by ON  */},

{/*rt*/	ro, xl, xr, ra, re, xa, rt, ro, ro, rt, /* ET following R		  */},
{/*lt*/	lo, xl, xr, la, le, xa, lt, lo, lo, lt, /* ET following L		  */},

{/*cn*/	ao, xl, xr, cn, cn, xa, cn, ac, ao, ao, /* EN, AN following AL	  */},
{/*ra*/	ro, xl, xr, ra, re, xa, ra, rc, ro, rt, /* arabic number foll R   */},
{/*re*/	ro, xl, xr, ra, re, xa, re, rs, rs,ret, /* european number foll R */},
{/*la*/	lo, xl, xr, la, le, xa, la, lc, lo, lt, /* arabic number foll L   */},
{/*le*/	lo, xl, xr, la, le, xa, le, ls, ls,let, /* european number foll L */},

{/*ac*/	ao, xl, xr, cn, cn, xa, ao, ao, ao, ao, /* CS following cn		  */},
{/*rc*/	ro, xl, xr, ra, re, xa, ro, ro, ro, rt, /* CS following ra		  */},
{/*rs*/	ro, xl, xr, ra, re, xa, ro, ro, ro, rt, /* CS,ES following re	  */},
{/*lc*/	lo, xl, xr, la, le, xa, lo, lo, lo, lt, /* CS following la		  */},
{/*ls*/	lo, xl, xr, la, le, xa, lo, lo, lo, lt, /* CS,ES following le	  */},

{/*ret*/ ro, xl, xr, ra, re, xa,ret, ro, ro,ret, /* ET following re		  */},
{/*let*/ lo, xl, xr, la, le, xa,let, lo, lo,let, /* ET following le		  */}


};

enum bidi_action // possible actions
{
	// primitives
	IX = 0x100,					// increment
	XX = 0xF,					// no-op

	// actions
	xxx = (XX << 4) + XX,		// no-op
	xIx = IX + xxx,				// increment run
	xxN = (XX << 4) + CT_ON,		// set current to N 
	xxE = (XX << 4) + CT_EN,		// set current to EN
	xxA = (XX << 4) + CT_AN,		// set current to AN
	xxR = (XX << 4) + CT_R,		// set current to R
	xxL = (XX << 4) + CT_L,		// set current to L
	Nxx = (CT_ON << 4) + 0xF,		// set run to neutral
	Axx = (CT_AN << 4) + 0xF,		// set run to AN
	ExE = (CT_EN << 4) + CT_EN,		// set run to EN, set current to EN
	NIx = (CT_ON << 4) + 0xF + IX,	// set run to N , increment
	NxN = (CT_ON << 4) + CT_ON,		// set run to N , set current to N 
	NxR = (CT_ON << 4) + CT_R,		// set run to N , set current to R
	NxE = (CT_ON << 4) + CT_EN,		// set run to N , set current to EN

	AxA = (CT_AN << 4) + CT_AN,		// set run to AN, set current to AN
	NxL = (CT_ON << 4) + CT_L,		// set run to N , set current to L
	LxL = (CT_L << 4) + CT_L,			// set run to L, set current to L
};


int actionWeak[][10] =
{
	//   N ,.. L,   R,  AN,  EN,  AL, NSM,  CS,..ES,  ET,
{/*xa*/ xxx, xxx, xxx, xxx, xxA, xxR, xxR, xxN, xxN, xxN, /* arabic letter			*/},
{/*xr*/ xxx, xxx, xxx, xxx, xxE, xxR, xxR, xxN, xxN, xIx, /* right leter 			*/},
{/*xl*/ xxx, xxx, xxx, xxx, xxL, xxR, xxL, xxN, xxN, xIx, /* left letter 			*/},

{/*ao*/ xxx, xxx, xxx, xxx, xxA, xxR, xxN, xxN, xxN, xxN, /* arabic lett. foll by ON	*/},
{/*ro*/ xxx, xxx, xxx, xxx, xxE, xxR, xxN, xxN, xxN, xIx, /* right lett. foll by ON	*/},
{/*lo*/ xxx, xxx, xxx, xxx, xxL, xxR, xxN, xxN, xxN, xIx, /* left lett. foll by ON	*/},

{/*rt*/ Nxx, Nxx, Nxx, Nxx, ExE, NxR, xIx, NxN, NxN, xIx, /* ET following R			*/},
{/*lt*/ Nxx, Nxx, Nxx, Nxx, LxL, NxR, xIx, NxN, NxN, xIx, /* ET following L			*/},

{/*cn*/ xxx, xxx, xxx, xxx, xxA, xxR, xxA, xIx, xxN, xxN, /* EN, CT_AN following  AL	*/},
{/*ra*/ xxx, xxx, xxx, xxx, xxE, xxR, xxA, xIx, xxN, xIx, /* arabic number foll R	*/},
{/*re*/ xxx, xxx, xxx, xxx, xxE, xxR, xxE, xIx, xIx, xxE, /* european number foll R	*/},
{/*la*/ xxx, xxx, xxx, xxx, xxL, xxR, xxA, xIx, xxN, xIx, /* arabic number foll L	*/},
{/*le*/ xxx, xxx, xxx, xxx, xxL, xxR, xxL, xIx, xIx, xxL, /* european number foll L	*/},

{/*ac*/ Nxx, Nxx, Nxx, Axx, AxA, NxR, NxN, NxN, NxN, NxN, /* CS following cn 		*/},
{/*rc*/ Nxx, Nxx, Nxx, Axx, NxE, NxR, NxN, NxN, NxN, NIx, /* CS following ra 		*/},
{/*rs*/ Nxx, Nxx, Nxx, Nxx, ExE, NxR, NxN, NxN, NxN, NIx, /* CS,ES following re		*/},
{/*lc*/ Nxx, Nxx, Nxx, Axx, NxL, NxR, NxN, NxN, NxN, NIx, /* CS following la 		*/},
{/*ls*/ Nxx, Nxx, Nxx, Nxx, LxL, NxR, NxN, NxN, NxN, NIx, /* CS,ES following le		*/},

{/*ret*/xxx, xxx, xxx, xxx, xxE, xxR, xxE, xxN, xxN, xxE, /* ET following re			*/},
{/*let*/xxx, xxx, xxx, xxx, xxL, xxR, xxL, xxN, xxN, xxL, /* ET following le			*/},
};

int GetDeferredType(int action)
{
	return (action >> 4) & 0xF;
}

int GetResolvedType(int action)
{
	return action & 0xF;
}

/* Note on action table:

	States can be of two kinds:
	 - Immediate Resolution State, where each input token
	   is resolved as soon as it is seen. These states havve
	   only single action codes (xxN) or the no-op (xxx)
	   for static input tokens.
	 - Deferred Resolution State, where input tokens either
	   either extend the run (xIx) or resolve its Type (e.g. Nxx).

	Input classes are of three kinds
	 - Static Input Token, where the class of the token remains
	   unchanged on output (CT_AN, CT_L, CT_N , CT_R)
	 - Replaced Input Token, where the class of the token is
	   always replaced on output (CT_AL, CT_BN, CT_NSM, CT_CS, CT_ES, CT_ET)
	 - Conditional Input Token, where the class of the token is
	   changed on output in some but not all cases (CT_EN)

	 Where tokens are subject to change, a double action
	 (e.g. NxA, or NxN) is _required_ after deferred states,
	 resolving both the deferred state and changing the current token.

	These properties of the table are verified by assertions below.
	This code is needed only during debugging and maintenance
*/
#if ASSERT_ENABLED

bool IsDeferredState(int state)
{
	switch(state)
	{
	case rt: // this needs to be a deferred
	case lt:
	case ac:
	case rc:
	case rs:
	case lc:
	case ls:
		return true;
	}
	return false;
}

bool IsModifiedClass(int cls)
{
	switch(cls)
	{
	case CT_AL:
	case CT_NSM:
	case CT_ES:
	case CT_CS:
	case CT_ET:
	case CT_EN: // sometimes 'modified' to EN
		return true;
	}
	return false;
}

const int state_first = xa;
const int state_last = let;

const int cls_first =	CT_N ;
const int cls_last =   CT_ET;


// Verify these properties of the tables
int VerifyTables()
{
	int done = 1;
	
	for (int cls = cls_first; cls <= cls_last; cls++)
	{
		for (int state = state_first; state <= state_last; state++)
		{
			int action= actionWeak[state][cls];
			int nextstate = stateWeak[state][cls];

			if (IX & action)
			{
				// make sure when we defer we get to a
				// deferred state
				ASSERT(IsDeferredState(nextstate));

				// Make sure permanent classes are not deferred
				ASSERT(IsModifiedClass(cls));
			}
			else
			{
				// make sure we are not deferring without
				// incrementing a run
				ASSERT(!IsDeferredState(nextstate));

				// make sure modified classes are modified
				if (IsModifiedClass(cls))
				{
					ASSERT(GetResolvedType(action) != XX);
				}
				else
				{
					ASSERT(GetResolvedType(action) == XX);
				}
			}

			// if we are deferring, make sure things are resolved
			if (IsDeferredState(state))
			{
				// Deferred states must increment or have deferred type
				ASSERT(action == xIx || GetDeferredType(action) != XX);
			}
			else
			{
				ASSERT(GetDeferredType(action) == XX);
			}
		}
	};
	return done;
}
#endif

/*------------------------------------------------------------------------
	Function: resolveWeak

	Resolves the directionality of numeric and other weak character types

	Implements rules X10 and W1-W6 of the Unicode Bidirectional Algorithm.

	Input: Array of embedding levels
		   Character count

	In/Out: Array of directional classes

	Note: On input only these directional classes are expected
		  CT_AL, HL, CT_R, CT_L,  CT_ON, CT_BN, CT_NSM, CT_AN, CT_EN, CT_ES, CT_ET, CT_CS,
------------------------------------------------------------------------*/
void resolveWeak(int baselevel, int *pcls, int *plevel, int cch)
{
	int state = odd(baselevel) ? xr : xl;
	int cls;

	int level = baselevel;

	int cchRun = 0;

	int ich;
	for (ich = 0; ich < cch; ich++)
	{
#if BIDI_REFERENCE_WINDOWS_UI < 1 && !defined SELFTEST
#ifdef BIDI_REFERENCE_DEBUGGING
		if (pcls[ich] > CT_BN) {
			fprintf(stdout, "error: pcls[%d] > CT_BN (%d)\n", ich, pcls[ich]);
		}
#endif
#endif

		// ignore boundary neutrals
		if (pcls[ich] == CT_BN)
		{
			// must flatten levels unless at a level change;
			plevel[ich] = level;

			// lookahead for level changes
			if (ich + 1 == cch && level != baselevel)
			{
				// have to fixup last BN before end of the loop, since
				// its fix-upped value will be needed below the assert
				pcls[ich] = EmbeddingDirection(level);
			}
			else if (ich + 1 < cch && level != plevel[ich+1] && pcls[ich+1] != CT_BN)
			{
				// fixup LAST BN in front / after a level run to make
				// it act like the SOR/EOR in rule X10
				int newlevel = plevel[ich+1];
				if (level > newlevel) {
					newlevel = level;
				}
				plevel[ich] = newlevel;

				// must match assigned level
				pcls[ich] = EmbeddingDirection(newlevel);
				level = plevel[ich+1];
			}
			else
			{
				// don't interrupt runs
				if (cchRun)
				{
					cchRun++;
				}
				continue;
			}
		}

		ASSERT(pcls[ich] <= CT_BN);
		cls = pcls[ich];

		int action = actionWeak[state][cls];

		// resolve the directionality for deferred runs
		int clsRun = GetDeferredType(action);
		if (clsRun != XX)
		{
			SetDeferredRun(pcls, cchRun, ich, clsRun);
			cchRun = 0;
		}

		// resolve the directionality class at the current location
		int clsNew = GetResolvedType(action);
		if (clsNew != XX)
			pcls[ich] = clsNew;

		// increment a deferred run
		if (IX & action)
			cchRun++;

		state = stateWeak[state][cls];
	}

	// resolve any deferred runs
	// use the direction of the current level to emulate PDF
	cls = EmbeddingDirection(level);

	// resolve the directionality for deferred runs
	int clsRun = GetDeferredType(actionWeak[state][cls]);
	if (clsRun != XX)
		SetDeferredRun(pcls, cchRun, ich, clsRun);
}

// === RESOLVE NEUTAL TYPES ==============================================

// action values
enum neutral_action
{
	// action to resolve previous input
	nL = CT_L, 		// resolve EN to L
	En = 3 << 4,	// resolve neutrals run to embedding level direction
	Rn = CT_R << 4,	// resolve neutrals run to strong right
	Ln = CT_L << 4,	// resolved neutrals run to strong left
	In = (1<<8),	// increment count of deferred neutrals
	LnL = (1<<4)+CT_L, // set run and EN to L
};

int GetDeferredNeutrals(int action, int level)
{
	action = (action >> 4) & 0xF;
	if (action == (En >> 4))
		return EmbeddingDirection(level);
	else
		return action;
}

int GetResolvedNeutrals(int action)
{
	action = action & 0xF;
	if (action == In)
		return 0;
	else
		return action;
}

// state values
enum neutral_state
{
	// new temporary class
	r,	// R and characters resolved to R
	l,	// L and characters resolved to L
	rn, // N  preceded by right
	ln, // N  preceded by left
	a,	// AN preceded by left (the abbrev 'la' is used up above)
	na, // N  preceeded by a
} ;


/*------------------------------------------------------------------------
	Notes:

	By rule W7, whenever a CT_EN is 'dominated' by an CT_L (including start of
	run with embedding direction = CT_L) it is resolved to, and further treated
	as CT_L.

	This leads to the need for 'a' and 'na' states.
------------------------------------------------------------------------*/

int actionNeutrals[][5] =
{
//	N ,	L,	R, AN, EN, = cls
							// state =
	{In,  0,  0,  0,  0, 	},// r	right
	{In,  0,  0,  0,  CT_L, 	},// l	left

	{In, En, Rn, Rn, Rn, 	},// rn	N  preceded by right
	{In, Ln, En, En, LnL,	},// ln	N  preceded by left

	{In,  0,  0,  0,  CT_L, 	},// a   AN preceded by left
	{In, En, Rn, Rn, En, 	},// na	N   preceded by a
} ;

int stateNeutrals[][5] =
{
//	 N , L,	R,	AN, EN = cls
							// state =
	{rn, l,	r,	r,	r,		},// r   right
	{ln, l,	r,	a,	l,		},// l   left

	{rn, l,	r,	r,	r,		},// rn  _N  preceded by right
	{ln, l,	r,	a,	l,		},// ln  N  preceded by left

	{na, l,	r,	a,	l,		},// a  AN preceded by left
	{na, l,	r,	a,	l,		},// na  N  preceded by la
} ;

/*------------------------------------------------------------------------
	Function: resolveNeutrals

	Resolves the directionality of neutral character types.

	Implements rules W7, N1 and N2 of the Unicode Bidi Algorithm.

	Input: Array of embedding levels
		   Character count
		   Baselevel

	In/Out: Array of directional classes

	Note: On input only these directional classes are expected
		  CT_R,  CT_L,  CT_N , CT_AN, CT_EN and CT_BN

		  W8 resolves a number of ENs to CT_L
------------------------------------------------------------------------*/
void resolveNeutrals(int baselevel, int *pcls, const int *plevel, int cch)
{
	// the state at the start of text depends on the base level
	int state = odd(baselevel) ? r : l;
	int cls;

	int cchRun = 0;
	int level = baselevel;

	int ich;
	for (ich = 0; ich < cch; ich++)
	{
		// ignore boundary neutrals
		if (pcls[ich] == CT_BN)
		{
			// include in the count for a deferred run
			if (cchRun)
				cchRun++;

			// skip any further processing
			continue;
		}

		ASSERT(pcls[ich] < 5); // "Only N , L, R,  AN, EN are allowed"
		cls = pcls[ich];

		int action = actionNeutrals[state][cls];

		// resolve the directionality for deferred runs
		int clsRun = GetDeferredNeutrals(action, level);
		if (clsRun != CT_N )
		{
			SetDeferredRun(pcls, cchRun, ich, clsRun);
			cchRun = 0;
		}

		// resolve the directionality class at the current location
		int clsNew = GetResolvedNeutrals(action);
		if (clsNew != CT_N )
			pcls[ich] = clsNew;

		if (In & action)
			cchRun++;

		state = stateNeutrals[state][cls];
		level = plevel[ich];
	}

	// resolve any deferred runs
	cls = EmbeddingDirection(level);	// eor has type of current level

	// resolve the directionality for deferred runs
	int clsRun = GetDeferredNeutrals(actionNeutrals[state][cls], level);
	if (clsRun != CT_N )
		SetDeferredRun(pcls, cchRun, ich, clsRun);
}

// === RESOLVE IMPLLICIT =================================================

/*------------------------------------------------------------------------
	Function: resolveImplicit

	Recursively resolves implicit embedding levels.
	Implements rules I1 and I2 of the Unicode Bidirectional Algorithm.

	Input: Array of direction classes
		   Character count
		   Base level

	In/Out: Array of embedding levels

	Note: levels may exceed 15 on output.
		  Accepted subset of direction classes
		  CT_R, CT_L, CT_AN, CT_EN
------------------------------------------------------------------------*/
int addLevel[][4] =
{
		// L,  R,	AN, EN = cls
							// level =
{/* even */	0,	1,	2,	2,	},// EVEN
{/* odd	*/	1,	0,	1,	1,	},// ODD

};

void resolveImplicit(const int * pcls, int * plevel, int cch)
{
	for (int ich = 0; ich < cch; ich++)
	{
		// cannot resolve bn here, since some bn were resolved to strong
		// types in resolveWeak. To remove these we need the original
		// types, which are available again in resolveWhiteSpace
		if (pcls[ich] == CT_BN)
		{
			continue;
		}
		ASSERT(pcls[ich] > 0); // "No Neutrals allowed to survive here."
		ASSERT(pcls[ich] < 5); // "Out of range."
		plevel[ich] += addLevel[odd(plevel[ich])][pcls[ich] - 1];
	}
}

// === REORDER ===========================================================
/*------------------------------------------------------------------------
	Function: resolveLines

	Breaks a paragraph into lines

	Input:	Character count
			Array of line break flags
	In/Out:	Array of characters

	Returns the count of characters on the first line

	Note: This function only breaks lines at hard line breaks. Other
	line breaks can be passed in. If pbrk[n] is true, then a break
	occurs after the character in pszInput[n]. Breaks before the first
	character are not allowed.
------------------------------------------------------------------------*/
int resolveLines(TCHAR * pszInput, bool * pbrk, int cch)
{
	// skip characters not of type LS
	int ich;
	for(ich = 0; ich < cch; ich++)
	{
		if (pszInput[ich] == chLS || (pbrk && pbrk[ich]))
		{
			ich++;
			break;
		}
	}

	return ich;
}

/*------------------------------------------------------------------------
	Function: resolveWhiteSpace

	Resolves levels for CT_WS and CT_S
	Implements rule L1 of the Unicode bidi Algorithm.

	Input:	Base embedding level
			Character count
			Array of direction classes (for one line of text)

	In/Out: Array of embedding levels (for one line of text)

	Note: this should be applied a line at a time. The default driver
		  code supplied in this file assumes a single line of text; for
		  a real implementation, cch and the initial pointer values
		  would have to be adjusted.
------------------------------------------------------------------------*/
void resolveWhitespace(int baselevel, const int *pcls, int *plevel,
					   int cch)
{
	int cchrun = 0;
	int oldlevel = baselevel;

	int ich;
	for (ich = 0; ich < cch; ich++)
	{
		switch(pcls[ich])
		{
		default:
			cchrun = 0; // any other character breaks the run
			break;
		case CT_WS:
			cchrun++;
			break;

		case CT_RLE:
		case CT_LRE:
		case CT_LRO:
		case CT_RLO:
		case CT_PDF:
		case CT_BN:
			plevel[ich] = oldlevel;
			cchrun++;
			break;

		case CT_S:
		case CT_B:
			// reset levels for WS before eot
			SetDeferredRun(plevel, cchrun, ich, baselevel);
			cchrun = 0;
			plevel[ich] = baselevel;
			break;
		}
		oldlevel = plevel[ich];
	}
	// reset level before eot
	SetDeferredRun(plevel, cchrun, ich, baselevel);
}


/*------------------------------------------------------------------------
	Functions: reorder/reorderLevel

	Recursively reorders the display string
	"From the highest level down, reverse all characters at that level and
	higher, down to the lowest odd level"

	Implements rule L2 of the Unicode bidi Algorithm.

	Input: Array of embedding levels
		   Character count
		   Flag enabling reversal (set to false by initial caller)

	In/Out: Text to reorder

	Note: levels may exceed 15 resp. 61 on input.

	Rule L3 - reorder combining marks is not implemented here
	Rule L4 - glyph mirroring is implemented as a display option below

	Note: this should be applied a line at a time
-------------------------------------------------------------------------*/
int reorderLevel(int level, LPTSTR pszText, const int * plevel, int cch,
				 bool fReverse = false)
{
	// true as soon as first odd level encountered
	fReverse = fReverse || odd(level);

	int ich;
	for (ich = 0; ich < cch; ich++)
	{
		if (plevel[ich] < level)
		{
			break;
		}
		else if (plevel[ich] > level)
		{
			ich += reorderLevel(level + 1, pszText + ich, plevel + ich,
				cch - ich, fReverse) - 1;
		}
	}
	if (fReverse)
	{
		reverse(pszText, ich);
	}
	return ich;
}

int reorder(int baselevel, LPTSTR pszText, const int * plevel, int cch)
{
	int ich = 0;

	while (ich < cch)
	{
		ich += reorderLevel(baselevel, pszText + ich, plevel + ich,
			cch - ich);
	}
	return ich;
}

// === DISPLAY OPTIONS ================================================
/*-----------------------------------------------------------------------
   Function:	mirror

	Crudely implements rule L4 of the Unicode Bidirectional Algorithm
	Demonstrate mirrored brackets, braces and parens


	Input:	Array of levels
			Count of characters

	In/Out:	Array of characters (should be array of glyph ids)

	Note;
	A full implementation would need to substitute mirrored glyphs even
	for characters that are not paired (e.g. integral sign).
-----------------------------------------------------------------------*/
void mirror(LPTSTR pszInput, const int * plevel, int cch)
{
	for (int ich = 0; ich < cch; ich ++)
	{
		if (!odd(plevel[ich]))
			continue;

		if (pszInput[ich] == '<')
		{
			pszInput[ich] = '>';
		}
		else if (pszInput[ich] == '>')
		{
			pszInput[ich] = '<';
		}
		else if (pszInput[ich] == ')')
		{
			pszInput[ich] = '(';
		}
		else if (pszInput[ich] == '(')
		{
			pszInput[ich] = ')';
		}
	}
}

/*-----------------------------------------------------------------------
	Function: clean

	remove formatting codes

	In/Out:	Array of characters
			Count of characters

	Note;

	This function can be used to remove formatting codes so the
	ordering of the string can be compared to implementations that
	remove formatting codes. This implementation is limited to the
	pseudo alphabet used for the demo version.

-----------------------------------------------------------------------*/
int clean(LPTSTR pszInput, int cch)
{
	int cchMove = 0;
	int ich;
	for (ich = 0; ich < cch; ich ++)
	{
		int ch = pszInput[ich];
		switch (ch)
		{
		default:
			if (pszInput[ich] < 0x20)
			{
				cchMove++;
			}
			else
			{
				pszInput[ich - cchMove] = pszInput[ich];
			}
			break;

		case chRLO:
		case chLRO:
		case chRLE:
		case chLRE:
		case chPDF:
		case chBN:
			cchMove++;
			break;
		}
	}
	pszInput[ich - cchMove] = 0;

	return ich - cchMove;
}

// === BIDI INTERFACE FUNCTIONS ========================================


/*------------------------------------------------------------------------
	Function: BidiLines

	Implements the Line-by-Line phases of the Unicode Bidi Algorithm

	Input:	 Count of characters
			 Flag (Mirror output if true)
			 Optional: Array of flags, true for last character on each line 

	Inp/Out: Input text
			 Array of character directions
			 Array of levels

	Note:	 See resolveLines for information how this function deals with line breaks
------------------------------------------------------------------------*/
void BidiLines(int baselevel, TCHAR * pszLine, int * pclsLine,
			   int * plevelLine, int cchPara, int fMirror, bool * pbrk)
{
	int cchLine = 0;

	do
	{
		// break lines at LS
		cchLine = resolveLines(pszLine, pbrk, cchPara);

		// resolve whitespace
		resolveWhitespace(baselevel, pclsLine, plevelLine, cchLine);


		if (fMirror)
		{
			mirror(pszLine, plevelLine, cchLine);
		}

		// reorder each line in place
		reorder(baselevel, pszLine, plevelLine, cchLine);

		pszLine += cchLine;
		plevelLine += cchLine;
		pbrk += pbrk ? cchLine : 0;
		pclsLine += cchLine;
		cchPara -= cchLine;

	} while (cchPara);
}

/*------------------------------------------------------------------------
	Function: BidiParagraph

	Implements the per paragraph phases of the Unicode Bidi Algorithm

	Input:	
			 Count of characters

	Inp/Out: Input text
			 Base paragraph level (negative value on input means implicit)
			 Array of character directions
			 Array of levels

	Returns: The number of input characters processed for this paragraph

	Note:	 This function is not called by the demo code in this file, but 
			 provided here for completeness. It has been tested by being
			 used in the verfication code.
------------------------------------------------------------------------*/
int BidiParagraph(int &baselevel,  int * types, int * levels, int cch)
{
	// set baselevel
	if (baselevel < 0)
		baselevel = baseLevel(types, cch);
	
	// change B into BN and return length including
	int cchPara = resolveParagraphs(types, cch);
	
	// resolve explicit
	resolveExplicit(baselevel, CT_N , types, levels, cchPara);

	// resolve weak
	resolveWeak(baselevel, types, levels, cchPara);

	// resolve neutrals
	resolveNeutrals(baselevel,types, levels, cchPara);

	// resolveImplicit
	resolveImplicit(types, levels, cchPara);

	// return the part of the input processed so far
	return cchPara;
}

#if BIDI_REFERENCE_WINDOWS_UI > 0 && BIDI_REFERENCE_WINDOWS_UI < 3

// === BIDI MAIN FUNCTION ================================================

#define MAX_CCH 256
void ShowInputTypes(HWND hwndDlg, int idc, LPTSTR pszInput, int cch)
{
	TCHAR pszTypes[MAX_CCH];
	for (int ich = 0; ich < cch; ich++)
	{
		pszTypes[ich] = CharFromTypes[ClassFromChWS(pszInput[ich])];
	}
	pszTypes[ich] = 0;
	SetDlgItemText(hwndDlg, idc, pszTypes);
}

void ShowTypes(HWND hwndDlg, int idc, int * types, int cch)
{
	TCHAR pszTypes[MAX_CCH];
	for (int ich = 0; ich < cch; ich++)
	{
		pszTypes[ich] = CharFromTypes[types[ich]];
	}
	pszTypes[ich] = 0;
	SetDlgItemText(hwndDlg, idc, pszTypes);
}

void ShowLevels(HWND hwndDlg, int idc, int * levels, int cch)
{
	#if BIDI_REFERENCE_DEMO
	// do nothing if levels are not limited to 15 as for debugging
	// since we can't show 0-61 in a single character

	TCHAR pszLevel[MAX_CCH];
	for (int ich = 0; ich < cch; ich++)
	{
		pszLevel[ich] = CharFromLevel[levels[ich]];
	}
	pszLevel[ich] = 0;
	SetDlgItemText(hwndDlg, idc, pszLevel);

	#else
		// squelch compiler warnings
		idc; hwndDlg; levels; cch;
	#endif
}

/*------------------------------------------------------------------------
	Function: BidiDemo

	Implements the Unicode Bidi Algorithm and drives display of results

	Input: Handle to dialog

	Note: directly reads/writes to fields in the dialog, limit 256 chars
------------------------------------------------------------------------*/
void BidiDemo(HWND hwndDlg)
{
	// verify the tables once
	#if BIDI_REFERENCE_DEBUGGING
	#if BIDI_REFERENCE_WINDOWS_UI ==2
	static int check = VerifyTables(); // ASSERT must be defind to enable this
	#endif
	#endif

	TCHAR pszInput[MAX_CCH];

	int types[MAX_CCH];
	int levels[MAX_CCH];

	// read input string
	int cch = GetDlgItemText(hwndDlg, IDC_INPUT, pszInput, MAX_CCH);

	// assign directional types
	classify(pszInput, types, cch);

	ShowInputTypes(hwndDlg, IDC_TYPES, pszInput, cch);

	// limit text to first paragraph
	cch = resolveParagraphs(types, cch);

	// set base level and compute character types
	int baselevel = GetDlgItemInt(hwndDlg, IDC_BASELEVEL, 0, 0);

	if (IsDlgButtonChecked(hwndDlg, IDC_IMPLICIT))
	{
		baselevel = baseLevel(types, cch);
		SetDlgItemInt(hwndDlg, IDC_BASELEVEL, baselevel, 0);
	}

	// resolve explicit
	resolveExplicit(baselevel, CT_N , types, levels, cch);

	ShowLevels(hwndDlg, IDC_EX_LEVEL, levels, cch);

	ShowTypes(hwndDlg, IDC_X_TYPES, types, cch);

	// resolve weak
	resolveWeak(baselevel, types, levels, cch);

	ShowTypes(hwndDlg, IDC_W_TYPES, types, cch);

	// resolve neutrals
	resolveNeutrals(baselevel,types, levels, cch);

	ShowTypes(hwndDlg, IDC_N_TYPES, types, cch);

	// resolveImplicit
	resolveImplicit(types, levels, cch);

	// assign directional types to whitespace
	classify(pszInput, types, cch, true);

	// At this point, the paragraph is broken into lines
	// This sample only supports hard line breaks (LS)
	int fMirror = IsDlgButtonChecked(hwndDlg, IDC_MIRROR);
	BidiLines(baselevel, pszInput, types, levels, cch, fMirror);

	// report results
	ShowLevels(hwndDlg, IDC_IM_LEVEL, levels, cch);

	if (IsDlgButtonChecked(hwndDlg, IDC_CLEAN))
	{
		cch = clean(pszInput, cch);
	}

	// write display string
	SetDlgItemText(hwndDlg, IDC_DISPL, pszInput);
}

// insert a special code into the edit field at the selection
void InsertAtSelection(HWND hwndDlg, TCHAR chFormat, int ichStart,
					   int ichEnd)
{
	TCHAR pszInput[MAX_CCH];
	TCHAR pszNew[MAX_CCH];

	// read input string
	int cch = GetDlgItemText(hwndDlg, IDC_INPUT, pszInput, MAX_CCH);

	// no selection
	if (ichEnd < ichStart || ichStart > cch)
		return;

	// insert RLM or LRM
	lstrcpyn(pszNew, pszInput, ichStart + 1);
	pszNew[ichStart] = chFormat;
	lstrcpyn(pszNew + ichStart + 1, pszInput + ichStart,
		cch - ichStart + 1);

	// write formatted string
	SetDlgItemText(hwndDlg, IDC_INPUT, pszNew);

	// get ready to accept more typed input
	SetFocus(GetDlgItem(hwndDlg, IDC_INPUT));
	ichStart++;
	SendDlgItemMessage(hwndDlg, IDC_INPUT, EM_SETSEL,
						(LPARAM) ichStart, (WPARAM) ichStart);
}

// embed/override the selection by bracketing with explicit controls
void FormatSelection(HWND hwndDlg, TCHAR chFormat, int ichStart,
					 int ichEnd)
{
	TCHAR pszInput[MAX_CCH];
	TCHAR pszNew[MAX_CCH];

	// read input string
	int cch = GetDlgItemText(hwndDlg, IDC_INPUT, pszInput, MAX_CCH);

	// no selection
	if (ichEnd < ichStart || ichStart > cch)
		return;

	// embed or override the selection by bracketing with format
	// character and PDF
	lstrcpyn(pszNew, pszInput, ichStart + 1);
	pszNew[ichStart] = chFormat;
	lstrcpyn(pszNew + ichStart + 1, pszInput + ichStart,
		ichEnd - ichStart + 1);
	pszNew[ichEnd + 1] = chPDF;
	lstrcpyn(pszNew + ichEnd + 2, pszInput + ichEnd, cch - ichEnd + 1);

	// write formatted string
	SetDlgItemText(hwndDlg, IDC_INPUT, pszNew);

	// get ready to accept more typed input
	SetFocus(GetDlgItem(hwndDlg, IDC_INPUT));
	ichEnd+=2;
	SendDlgItemMessage(hwndDlg, IDC_INPUT, EM_SETSEL,
						(LPARAM) ichStart, (WPARAM) ichEnd);
}

#if BIDI_REFERENCE_WINDOWS_UI == 2
// For private build, this is an ordinary modeless dialog

BOOL CALLBACK BidiDlgProc(HWND hwndDlg, UINT message, WPARAM wParam,
						  LPARAM lParam)
{
	static HFONT hfontDlg;

	static int ichStart =0;
	static int ichEnd = 0;
	static PDWORD pcwndBidi = 0;
	switch (message)
	{
	   case WM_INITDIALOG:
		{
			// initialize dialog
			SetDlgItemText(hwndDlg, IDC_LEGEND, legend);
			CheckDlgButton(hwndDlg, IDC_MIRROR, TRUE);
			CheckDlgButton(hwndDlg, IDC_IMPLICIT, TRUE);
			#ifdef _WINDOW_H_
			CWindow winDlg(hwndDlg);
			winDlg.CenterAbove( GetWindow(hwndDlg,GW_OWNER));
			#endif
			hfontDlg = CreateFont(-14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						FIXED_PITCH | FF_MODERN, TEXT("Lucida Console"));
			SendMessage (GetDlgItem (hwndDlg, IDC_LEGEND), WM_SETFONT, (UINT)hfontDlg, TRUE);

			pcwndBidi = (PDWORD) lParam;
			if (pcwndBidi)
				(*pcwndBidi)++;
			return TRUE;
		}
		// ... continued after #endif
#else
// For standalone (BIDI_REFERENCE_WINDOWS_UI == 1) the dialog is run as a main window
// requiring some difference in initialization code and message handling

// helper function to initialize the explanation window
BOOL CALLBACK SetLegendProc(HWND hwndChild, LPARAM lParam)
{
	LONG id = GetWindowLong(hwndChild, GWL_ID);
	if (id == IDC_LEGEND)
	{
		SendMessage(hwndChild, (UINT) WM_SETTEXT,  (WPARAM) 0, (LPARAM) lParam);
		return FALSE; // done
	}
	return TRUE; // continue looking
}

#pragma message("compiling standalone bidi dialog")
LRESULT CALLBACK BidiWndProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HFONT hfontDlg;

	static int ichStart =0;
	static int ichEnd = 0;

	switch (message)
	{
	case WM_SHOWWINDOW:
		hfontDlg = CreateFont(-14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					FIXED_PITCH | FF_MODERN, TEXT("Lucida Console"));
		SendMessage (GetDlgItem (hwndDlg, IDC_LEGEND), WM_SETFONT, (UINT)hfontDlg, TRUE);

		CheckDlgButton(hwndDlg, IDC_MIRROR, TRUE);
		CheckDlgButton(hwndDlg, IDC_IMPLICIT, TRUE);
		
		// initialize explanation window
		EnumChildWindows(hwndDlg, SetLegendProc,  (LPARAM) legend);
		return 0;
		break;
	case WM_DESTROY:
		DeleteObject (hfontDlg);
		PostQuitMessage(0);
	return 0;
#endif


	case WM_COMMAND:
		{
			int cmd = GET_WM_COMMAND_CMD(wParam, lParam);
			int idc =  GET_WM_COMMAND_ID(wParam, lParam);
			switch (idc) //Command ID
			{
			case IDC_BASELEVEL:
				if (!IsDlgButtonChecked(hwndDlg,IDC_IMPLICIT))
				{
					SendDlgItemMessage(hwndDlg, IDC_INPUT, EM_GETSEL,
						(LPARAM) &ichStart, (WPARAM) &ichEnd);
					BidiDemo(hwndDlg);
				}
				break;

				// fall through causes display to update for these controls
			case IDC_IMPLICIT:
				SendDlgItemMessage(hwndDlg, IDC_BASELEVEL, EM_SETREADONLY,
					IsDlgButtonChecked(hwndDlg,IDC_IMPLICIT), 0);
				// FALL THROUGH
			case IDC_INPUT:
				if (idc == IDC_INPUT && cmd != EN_CHANGE)
					break;
				// FALL THROUGH
			case IDC_CLEAN:
			case IDC_MIRROR:
				SendDlgItemMessage(hwndDlg, IDC_INPUT, EM_GETSEL,
						(LPARAM) &ichStart, (WPARAM) &ichEnd);
				BidiDemo(hwndDlg);
				break;

			case IDC_RLE:
				FormatSelection(hwndDlg, chRLE, ichStart, ichEnd);
				break;
			case IDC_LRE:
				FormatSelection(hwndDlg, chLRE, ichStart, ichEnd);
				break;
			case IDC_RLO:
				FormatSelection(hwndDlg, chRLO, ichStart, ichEnd);
				break;
			case IDC_LRO:
				FormatSelection(hwndDlg, chLRO, ichStart, ichEnd);
				break;

			case IDC_RLM:
				InsertAtSelection(hwndDlg, chRLM, ichStart, ichEnd);
				break;
			case IDC_LRM:
				InsertAtSelection(hwndDlg, chLRM, ichStart, ichEnd);
				break;

			case IDC_LS:
				InsertAtSelection(hwndDlg, chLS, ichStart, ichEnd);
				break;

#if BIDI_REFERENCE_WINDOWS_UI == 2
			case IDOK: // "Close"
			case IDCANCEL:
				// pass either IDOK or IDCANCEL to ENDDIALOG
				EndDialog(hwndDlg, GET_WM_COMMAND_ID(wParam, lParam));
				DeleteObject (hfontDlg);
				CWindow::SetModelessDlg(0);
				if (pcwndBidi)
					(*pcwndBidi)--;
				return TRUE;
#endif
			}
		}
		break;
	}
#if BIDI_REFERENCE_WINDOWS_UI == 1
	return DefWindowProc(hwndDlg, message, wParam, lParam);
#else
	return FALSE ;
#endif

	// squelch compiler warnings
	lParam;
}
#elif defined SELFTEST

int ResolvePhonyString(int baselevel, const char* phony_str, int* levels, int max_chars)
{
	int len = op_strlen(phony_str);

	if (len > max_chars)
		return -1;

	int* types = OP_NEWA(int, len);

	if (!types)
		return -1;

	classify(phony_str, types, len);

	int old_len = len;

	len = resolveParagraphs(types, len);

	if (old_len != len)
	{
		// This function only support strings with one paragraph.
		OP_DELETEA(types);
		return -1;
	}

	resolveExplicit(baselevel, CT_N, types, levels, len);

	resolveWeak(baselevel, types, levels, len);

	resolveNeutrals(baselevel,types, levels, len);

	resolveImplicit(types, levels, len);

	// Strip off levels caused by RLE, RLO, LRE, LRO, PDF.

	int level_array_pointer =-1;

	for (int i = 0; i < len; i++)
	{
		int cat = ClassFromChWS(phony_str[i]);

		if (cat != CT_RLE && cat != CT_RLO && cat != CT_LRE && cat != CT_LRO && cat != CT_PDF)
		{
			level_array_pointer++;
			levels[level_array_pointer] = levels[i];
		}
	}

	OP_DELETEA(types);

	return 0;
}

BidiCategory PhonyCharToBidiCategory(char ch)
{
	int cl = ClassFromChWS(ch);

	switch (cl)
	{
		
	case CT_ON:
		return BIDI_ON;
    case CT_L:
		return BIDI_L;
    case CT_R:
		return BIDI_R;
    case CT_AN:
		return BIDI_AN;
    case CT_EN:
		return BIDI_EN;
    case CT_AL:
		return BIDI_AL;
    case CT_NSM:
		return BIDI_NSM;
    case CT_CS:
		return BIDI_CS;
    case CT_ES:
		return BIDI_ES;
    case CT_ET:
		return BIDI_ET;
    case CT_BN:
		return BIDI_BN;
    case CT_S:
		return BIDI_S;
    case CT_WS:
		return BIDI_WS;
	case CT_B:
		return BIDI_B;
    case CT_RLO:
		return BIDI_RLO;
    case CT_RLE:
		return BIDI_RLE;
    case CT_LRO:
		return BIDI_LRO;
    case CT_LRE:
		return BIDI_LRE;
    case CT_PDF:
		return BIDI_PDF;
	}
	return BIDI_UNDEFINED;
}

BOOL VerifyLevelsVersusBidiSegments(int* levels, Head& bidi_segments)
{
	ParagraphBidiSegment* s = (ParagraphBidiSegment*)bidi_segments.First();

	int count = 0;

	while (s)
	{
		int seg_len = s->width;

		for (int i = 0; i < seg_len; i++)
		{
			if (levels[count + i] != s->level)
				return FALSE;
		}
		count += seg_len;

		s = (ParagraphBidiSegment*)s->Suc();
	}
	return TRUE;
}
#define BIDI_REFERENCE_MAX_CHARS 500

BOOL VerifyReferenceVersusCalculation(const char* str, BOOL ltr_paragraph)
{
	int levels[BIDI_REFERENCE_MAX_CHARS];

	if (ResolvePhonyString(ltr_paragraph ? 0 : 1, str, levels, BIDI_REFERENCE_MAX_CHARS) != 0)
		return FALSE;

	Head bidi_segments;
	BidiCalculation calc;
	calc.Reset();
	calc.SetParagraphLevel(ltr_paragraph ? BIDI_L : BIDI_R, FALSE);
	calc.SetSegments(&bidi_segments);

	const char* count = str;

	while (*count)
	{
		char c = *count;
		BidiCategory cat = PhonyCharToBidiCategory(c);
		calc.AppendStretch(cat, 1, NULL, 0);
		count++;
	}

	calc.HandleParagraphEnd();

	BOOL res = VerifyLevelsVersusBidiSegments(levels, bidi_segments);
	bidi_segments.Clear();
	return res;
}


#else
#pragma message("compiling  functions for commandline version")
// ===== FUNCTIONS FOR COMMAND LINE VERSION ==============================

#include <stdlib.h>
#include <string.h>

// An alternate CharFromTypes array may be needed to use with the command
// line version


#define MAX_CCH 256
void ShowInputTypes(FILE* f, LPTSTR pszInput, int cch)
{
	TCHAR pszTypes[MAX_CCH+1];
	for (int ich = 0; ich < cch; ich++)
	{
		pszTypes[ich] = CharFromTypes[ClassFromChWS(pszInput[ich])];
	}
	pszTypes[ich] = 0;

		fprintf(f, pszTypes);
}

void ShowTypes(FILE* f, int * types, int cch)
{
	TCHAR pszTypes[MAX_CCH+1];
	for (int ich = 0; ich < cch; ich++)
	{
		 pszTypes[ich] = CharFromTypes[types[ich]];
	}
	pszTypes[ich] = 0;

		fprintf(f, pszTypes);
}

void ShowLevels(FILE* f, int * levels, int cch)
{

	#if BIDI_REFERENCE_DEMO
	// do nothing if levels are not limited to 15 as for debugging
	// since we can't show 0-61 in a single character

	TCHAR pszLevel[MAX_CCH+1];
	for (int ich = 0; ich < cch; ich++)
	{
		pszLevel[ich] = CharFromLevel[levels[ich]];
	}
	pszLevel[ich] = 0;

		fprintf(f, pszLevel);

	#else
		// squelch compiler warnings
		f; levels; cch;
	#endif
}

void usage(char *s)
{
	printf("Usage: %s [-verbose] [-nomirror] [-level #] [-clean] strings...\n", s);
	printf("\t-verbose = verbose debugging output.\n");
	printf("\t-level # = specify # as the base level.\n");
	printf("\t-nomirror = refrain from glyph mirroring.\n");
	printf("\t-clean = clean up the result.\n");
	printf("\tOptions affect all subsequent arguments.\n");
	printf("\tAll other arguments are interpreted as strings to process.\n");
}

int main(int argc, char** argv)
{
	int realArg = 0;
	int doMirror = 1;
	int doClean = 0;
	int doLevel = 1;
	int baselevel = 0;
	int beVerbose = 0;

	FILE* f = stdout;

	if (argc == 1)
	{
		usage(argv[0]); exit(0);
	}
	for (int i = 1; i < argc; ++i)
	{
		if (doLevel == -1)
		{
			baselevel = atoi(argv[i]);
			doLevel = 0;
			continue;
		}
		else if (strcmp(argv[i], "-verbose") == 0)
		{
			beVerbose = 1;
			continue;
		}
		else if (strcmp(argv[i], "-nomirror") == 0)
		{
			doMirror = 0;
			continue;
		}
		else if (strcmp(argv[i], "-clean") == 0)
		{
			doClean = 1;
			continue;
		}
		else if (strcmp(argv[i], "-level") == 0)
		{
			if (argc - 1 == i)
			{
				usage(argv[0]); exit(0);
			}
			doLevel = -1;
			continue;
		}
		else
		{
			++realArg;
		}

		TCHAR pszInput[MAX_CCH+1];

		int cch = strlen(argv[i]);
		if (cch > MAX_CCH) cch = MAX_CCH;
		strncpy(pszInput, argv[i], cch);

		pszInput[cch] = 0;
		fprintf(f, "Input	 %2d: %s\n", realArg, pszInput);

		int types[MAX_CCH];
		int levels[MAX_CCH];

		// assign directional types
		classify(pszInput, types, cch);

		if (beVerbose)
		{
			fprintf(f, "Input Types: ");
			ShowInputTypes(f, pszInput, cch); fprintf(f, "\n");
		}

		// limit text to first block
		cch = resolveParagraphs(types, cch);

		// set base level
		if (doLevel)
			baselevel = baseLevel(types, cch);

		if (beVerbose)
		{
			fprintf(f, "Base Level : %d\n", baselevel);
		}

		// resolve explicit
		resolveExplicit(baselevel, CT_N , types, levels, cch);

		if (beVerbose)
		{
			fprintf(f, "Levels (A) : ");
			ShowLevels(f, levels, cch); fprintf(f, "\n");
		}

		// resolve weak
		resolveWeak(baselevel, types, levels, cch);

		if (beVerbose)
		{
			fprintf(f, "Types (A)  : ");
			ShowTypes(f, types, cch); fprintf(f, "\n");
		}

		// resolve neutrals
		resolveNeutrals(baselevel,types, levels, cch);

		if (beVerbose)
		{
			fprintf(f, "Types (B)  : ");
			ShowTypes(f, types, cch); fprintf(f, "\n");
		}

		// resolveImplicit
		resolveImplicit(types, levels, cch);

		if (beVerbose)
		{
			fprintf(f, "Levels (B) : ");
			ShowLevels(f, levels, cch); fprintf(f, "\n");
		}

		// assign directional types again, but for WS, S this time
		classify(pszInput, types, cch, true);

		BidiLines(baselevel, pszInput, types, levels, cch, doMirror);

		if (doClean)
		{
			cch = clean(pszInput, cch);
		}

			fprintf(f, "Output %2d: %s\n\n", realArg, pszInput);
	}

	return 0;
}
#endif // BIDI_REFERENCE_WINDOWS_UI

#endif // defined(SELFTEST) && defined(SUPPORT_TEXT_DIRECTION)
//[EOF]
