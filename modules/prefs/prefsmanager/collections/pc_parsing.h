/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright 2002-2012 Opera Software ASA.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
*/

#ifndef PC_PARSING
#define PC_PARSING

#include "modules/prefs/prefsmanager/opprefscollection_default.h"

/** Global PrefsCollectionJS object (singleton). */
#define g_pcparsing (g_opera->prefs_module.PrefsCollectionParsing())

class PrefsCollectionParsing : public OpPrefsCollectionDefault
{
public:
	/**
	  * Create method.
	  *
	  * This method preforms all actions required to construct the object.
	  * PrefsManager calls this method to initialize the object, and will
	  * not call the normal constructor directly.
	  *
	  * @param reader Pointer to the PrefsFile object.
	  * @return Pointer to the created object.
	  */
	static PrefsCollectionParsing *CreateL(PrefsFile *reader);

	virtual ~PrefsCollectionParsing();

#include "modules/prefs/prefsmanager/collections/pc_parsing_h.inl"

	// Read ------
	/**
	 * Read an integer preference.
	 *
	 * @param which Selects the preference to retrieve.
	 */
	inline int GetIntegerPref(integerpref which) const
	{
		return OpPrefsCollectionDefault::GetIntegerPref(int(which));
	};

	/**
	 * Read a string preference.
	 *
	 * @param which Selects the preference to retrieve.
	 * @param result Variable where the value will be stored.
	 */
	inline void GetStringPrefL(stringpref which, OpString &result) const
	{
		result.SetL(GetStringPref(which));
	}

	/**
	 * Read a string preference. This method will return a pointer to internal
	 * data. The object is only guaranteed to live until the next call to any
	 * Write method.
	 *
	 * @param which Selects the preference to retrieve.
	 */
	inline const OpStringC GetStringPref(stringpref which) const
	{
		RETURN_OPSTRINGC(OpPrefsCollectionDefault::GetStringPref(int(which)));
	}

#ifdef PREFS_HAVE_STRING_API
	virtual BOOL GetPreferenceL(IniSection section, const char *key, OpString &target,
		BOOL defval, const uni_char *host)
	{
		return OpPrefsCollectionDefault::GetPreferenceInternalL(
			section, key, target, defval,
			m_stringprefdefault, PCPARSING_NUMBEROFSTRINGPREFS,
			m_integerprefdefault, PCPARSING_NUMBEROFINTEGERPREFS);
	}
#endif

	// Defaults ------
	/**
	 * Get default value for an integer preference.
	 *
	 * @param which Selects the preference to retrieve.
	 * @return The default value.
	 */
	inline int GetDefaultIntegerPref(integerpref which) const
	{
		return m_integerprefdefault[which].defval;
	}

	/**
	 * Get default value for a string preference.
	 *
	 * @param which Selects the preference to retrieve.
	 * @return The default value.
	 */
	inline const uni_char *GetDefaultStringPref(stringpref which) const
	{
		return m_stringprefdefault[which].defval;
	}

#ifdef PREFS_WRITE
	// Write ------
	/** Write a string preference.
	  *
	  * @param which The preference to write.
	  * @param value Value for the write.
	  * @return ERR_NO_ACCESS if override is not allowed, OK otherwise.
	  */
	inline OP_STATUS WriteStringL(stringpref which, const OpStringC &value)
	{
		return OpPrefsCollection::WriteStringL(&m_stringprefdefault[which], int(which), value);
	}

	/** Write an integer preference.
	  *
	  * @param which The preference to write.
	  * @param value Value for the write.
	  * @return ERR_NO_ACCESS if override is not allowed, OK otherwise.
	  */
	inline OP_STATUS WriteIntegerL(integerpref which, int value)
	{
		return OpPrefsCollection::WriteIntegerL(&m_integerprefdefault[which], int(which), value);
	}

# ifdef PREFS_HAVE_STRING_API
	virtual BOOL WritePreferenceL(IniSection section, const char *key, const OpStringC &value)
	{
		return OpPrefsCollection::WritePreferenceInternalL(
			section, key, value,
			m_stringprefdefault, PCPARSING_NUMBEROFSTRINGPREFS,
			m_integerprefdefault, PCPARSING_NUMBEROFINTEGERPREFS);
	}
# endif

	// Reset ------
	/** Reset a string preference. Resets the preference to default by
	  * removing the set value from the preference storage.
	  *
	  * @param which The preference to reset.
	  * @return TRUE if the delete succeeded.
	  */
	inline BOOL ResetStringL(stringpref which)
	{
		return OpPrefsCollection::ResetStringL(&m_stringprefdefault[which], int(which));
	}

	/** Reset an integer preference. Resets the preference to default by
	  * removing the set value from the preference storage.
	  *
	  * @param which The preference to reset.
	  * @return TRUE if the delete succeeded.
	  */
	inline BOOL ResetIntegerL(integerpref which)
	{
		return OpPrefsCollection::ResetIntegerL(&m_integerprefdefault[which], int(which));
	}
#endif // PREFS_WRITE

	// Fetch preferences from file ------
	virtual void ReadAllPrefsL(PrefsModule::PrefsInitInfo *info);

#ifdef PREFS_ENUMERATE
	// Enumeration helpers ------
	virtual unsigned int GetNumberOfPreferences() const
	{
		return PCPARSING_NUMBEROFSTRINGPREFS + PCPARSING_NUMBEROFINTEGERPREFS;
	}

	virtual unsigned int GetPreferencesL(struct prefssetting *settings) const
	{
		return OpPrefsCollection::GetPreferencesInternalL(settings,
			m_stringprefdefault, PCPARSING_NUMBEROFSTRINGPREFS,
			m_integerprefdefault, PCPARSING_NUMBEROFINTEGERPREFS);
	}
#endif

private:
	/** Single-phase constructor.
	  *
	  * @param reader Pointer to the PrefsFile object.
	  */
	PrefsCollectionParsing(PrefsFile *reader)
		: OpPrefsCollectionDefault(Parsing, reader)
		{
#ifndef HAS_COMPLEX_GLOBALS
			InitStrings();
			InitInts();
#endif
		}

	/** String preference information and default values */
	PREFS_STATIC struct stringprefdefault
		m_stringprefdefault[PCPARSING_NUMBEROFSTRINGPREFS + 1];
	/** Integer preference information and default values */
	PREFS_STATIC struct integerprefdefault
		m_integerprefdefault[PCPARSING_NUMBEROFINTEGERPREFS + 1];

#ifdef PREFS_VALIDATE
	virtual void CheckConditionsL(int which, int *value, const uni_char *host);
	virtual BOOL CheckConditionsL(int which, const OpStringC &invalue,
	                              OpString **outvalue, const uni_char *host);
#endif

#ifndef HAS_COMPLEX_GLOBALS
	void InitStrings();
	void InitInts();
#endif
};

#endif // !PC_PARSING
