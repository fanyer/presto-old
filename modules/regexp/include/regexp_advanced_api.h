/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
 *
 * Copyright (C) Opera Software ASA  2002-2007
 */

/**
\file regexp_advanced_api.h

\brief "Advanced" API to the ECMAScript regular expression matcher.

A regular expression is created and compiled by calling RegExp::RegExp()
and then RegExp::Init().  After compilation the regexp can be used
any number of times by calling RegExp::Exec().  See comments below for
details.  */

#ifndef REGEX_ADVANCED_API_H
#define REGEX_ADVANCED_API_H

#undef Yield

class RegExpMatch
{
public:
	unsigned start;        // index of first character
	unsigned length;       // number of included characters
};

/** A structure that holds flags passed to RegExp::Init */
struct RegExpFlags
{
	RegExpFlags();

	BOOL3 ignore_case;
		/**< This is the "i" flag in ECMAScript.

			 If YES or NO, then the matcher is specialized at compile
			 time, leading to a (slightly) faster matcher at run-time.  If
			 MAYBE, then the matcher may have to do extra work at run-time. */

	BOOL3 multi_line;
		/**< This is the "m" flag in ECMAScript.

			 As for ignore_case.  */

	BOOL ignore_whitespace;
		/**< This is the "x" flag in ECMAScript 4.

			 If TRUE, then the regexp may contain newlines and line comments,
			 and all comments and whitespace (including Unicode format control
			 characters) are stripped from the regexp during compilation.  */

	BOOL searching;
		/**< This is the "y" flag in ECMAScript 4. */
};

class RE_Matcher;

#undef Yield

class RegExpSuspension
{
public:
	virtual void Yield() = 0;
	virtual void *AllocateL(unsigned nbytes) = 0;

protected:
	virtual ~RegExpSuspension() {}
};

class RE_Object;

/** A class that represents a compiled regular expression.  */

typedef BOOL (RegExpNativeMatcher)(RegExpMatch *result, const uni_char *source, unsigned index, unsigned length);

class RegExp
{
#ifdef __GNUC__
friend class PreventGCCWarningAboutPrivateDestructorAndNoFriends;
#endif // __GNUC__

public:
	/** Syntax errors generated by Init() */
	enum ErrorCode
	{
		NO_REGEXP_ERROR=0,		// Windows header files #defines NO_ERROR.  Foo!

		// Syntax errors in alphabetical order.

		BACKREFERENCE_OUT_OF_RANGE,
		BRACKET_IN_CHARSET_IN_ILLEGAL_CONTEXT,
		CHARSET_NOT_TERMINATED_BY_BRACKET,
		CONTROL_CHAR_IS_NOT_LETTER,
		DASH_IN_CHARSET_IN_ILLEGAL_CONTEXT,
		END_OF_INPUT_AFTER_BACKSLASH,
		EXPECTED_RIGHTPAREN,
		INTERNAL_COMPILER_ERROR,
		JUNK_AT_END_OF_EXPRESSION,
		ONE_OR_MORE_DIGITS_EXPECTED,
		QUANTIFIER_MAX_IS_LESS_THAN_MIN,
		QUANTIFIER_NOT_TERMINATED_BY_BRACE,
		QUANTIFIER_OVERFLOW,
		QUESTION_SUBPATTERN_BAD_SYNTAX,
		RANGE_ENDPOINTS_NOT_ATOMIC_OR_RANGE_EMPTY,
		SLASH_NOT_FOUND,
		SYMBOLIC_BACKREFERENCE_BAD_SYNTAX,
		SYMBOLIC_BACKREFERENCE_MULTIPLY_DEFINED,
		SYMBOLIC_BACKREFERENCE_UNDEFINED
	};

	RegExp();
		/**< Initialize a regular expression matcher object.  Increment
			 the reference count.  */

	void IncRef();
		/**< Increment the reference count */

	void DecRef();
		/**< Decrement the reference count and delete the object if the count
			 reaches zero. */

	OP_STATUS Init( const uni_char *pattern, unsigned length, const uni_char **slashpoint, RegExpFlags *flags );
		/**< Construct a regular expression matcher.

			 \param pattern		 The regular expression, NUL-terminated.
			 \param slashpoint	 If NULL, this parameter has no effect.
								 If not NULL, the parsing of the regex will terminate at the
								 first toplevel "/" encountered in "pattern", and a pointer to the
								 location of this "/" will be stored in *slashpoint.  If a "/" is
								 not found and no syntax error occurs before the end of the input
								 is reached, then an error is returned and *slashpoint is set to
								 point to the terminating NUL in "pattern".  If a syntax error occurs
								 before the end of the pattern is reached, an error is returned but
								 *slashpoint will be NULL.
			 \param flags        A pointer to a flags structure, controlling both compilation and
								 execution
			 \return             OpStatus::ERR if syntax error in pattern or if slash is not found,
								 setting a value to be retrieved by SyntaxError() (or if Init is called
								 on an inited object). OpStatus::ERR_NO_MEMORY on OOM.
			 \remarks            If compiled with REGEXP_SUBSET, ignore_case and multi_line must be
								 either YES or NO on input, MAYBE is treated as NO.
			 */

	void SetIgnoreCaseFlag(BOOL3 v);
		/**< If the ignore_case flag set by Init is still MAYBE, then set it to v. */

	void SetMultiLineFlag(BOOL3 v);
		/**< If the multi_line flag set by Init is still MAYBE, then set it to v. */

	int GetNumberOfCaptures() const;
		/**< \return the number of capture groups defined by the expression */

#if !defined REGEXP_SUBSET && !defined REGEXP_STRICT

	int GetNumberOfSymbols() const;
		/**< \return the number of symbolic capture names defined by the expression */

	const uni_char* GetSymbol(int i, int* index) const;
		/**< Retrieve information about a symbolic capture name defined by the expression.

			 \param i     The ordinal of the symbol we're retrieving.
			 \param index (out) The capture index of that symbol
			 \return      The symbol.  This string will be alive while the regexp is a live.
			 */

#endif

	BOOL ExecL( const uni_char *input, unsigned int length, unsigned int last_index, RegExpMatch** results, RegExpSuspension* suspend=NULL, BOOL searching=TRUE ) const;

	BOOL ExecL( const uni_char *input, unsigned int length, unsigned int last_index, RegExpMatch* results, RegExpSuspension* suspend=NULL, BOOL searching=TRUE ) const;
		/**< Run the matcher on a string and generate match results.

			 Matching will start at last_index but will try subsequent starting points if it
			 fails at last_index.  If a flag is still MAYBE, it is taken to be NO.

			 Exec() is reentrant and thread-safe.

			 Exec() allows the matching to be timesliced.  This is normally only important
			 if you do not control the pattern, because patterns can be constructed that
			 take an arbitrary amount of time to finish.  The timeslicing is not supported
			 if REGEXP_SUBSET is defined.

			 \param input		The input string to match against; may contain NULs
			 \param length		The length of the input string
			 \param last_index	The index in input to start matching at
			 \param results		A location that will be given a pointer to an array of match
								results, when they have been generated.  The match
								results are allocated on the standard heap with new[]
			 \param suspend		If not NULL this is either a suspension structure in its
								initial state or the structure created by a previous call
								on this method on *exactly* the same value for input.  If
								the engine suspends before matching (returning -1) then
								this structure will be updated with values that allows the
								matching to be restarted where it left off.  If the engine
								returns in any other manner, including by throwing an
								exception, then this structure is invalid and must not be
								reused.
			 \param searching	If TRUE then try for a match at last_index, and if that
								did not work then try again at last_index+1, and so on.
								Otherwise return the result of trying the match at
								last_index only.
			 \return			TRUE if the expression matched, FALSE otherwise.
			 \exception			OpStatus::ERR_NO_MEMORY on OOM.
			 \remarks			If compiled with REGEXP_SUBSET, the input string may not
								contain NULs and must in fact be NUL-terminated; length
								is ignored.
			 */

#ifdef ECMASCRIPT_NATIVE_SUPPORT
	OP_STATUS CreateNativeMatcher(OpExecMemoryManager *executable_memory);
		/**< Create a machine code matcher for the expression, if the expression is one
		     the JIT compiler supports, otherwise do nothing.

		     @return OpStatus::OK on success, OpStatus::ERR if not supported and
		             OpStatus::ERR_NO_MEMORY on OOM. */

	RegExpNativeMatcher *GetNativeMatcher();
#endif // ECMASCRIPT_NATIVE_SUPPORT

	RegExpMatch *GetMatchArray();

#ifdef REGEXP_UNPARSER
	void Unparse( FILE *out );
		/**< Print the representation of the regexp on stdout.

			 The printout uses Cambridge Polish (fully parenthesized prefix) syntax
			 and prints the compiled regexp as it is represented in the engine.  This
			 is useful for debugging the regexp engine.
			 */
#endif

	RegExp::ErrorCode SyntaxError() const;
		/**< Return any syntax error code, following a return of OpStatus::ERR from Init() */

private:
	~RegExp();
		/**< Delete the matcher object and all its storage.
		     */

private:
	int					refcount;			///< Reference count
	RegExp::ErrorCode	syntax_error;		///< Set by Init() on syntax errors
	RE_Object			*re_cs, *re_ci;
	BOOL3				ignore_case;		///< Current value of the ignore-case flag
	BOOL3				multi_line;			///< Current value of the multi-line flag
	RegExpMatch			*matches;
};

inline RegExp::ErrorCode
RegExp::SyntaxError() const
{
	return syntax_error;
}

#endif // REGEX_ADVANCED_API_H

/* eof */
