/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright (C) 1995-2011 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
*/

#include "core/pch.h"

#ifdef DESKTOP_UTIL_SEARCH_ENGINES

#include "adjunct/desktop_util/search/search_protection.h"
#include "adjunct/desktop_util/search/search_net.h"
#include "adjunct/desktop_util/string/stringutils.h"
#include "adjunct/desktop_util/datastructures/ZlibStream.h"
#include "adjunct/desktop_pi/DesktopOpSystemInfo.h"
#include "modules/util/opfile/opmemfile.h"
#include "modules/libssl/sslopt.h"
#include "modules/libcrypto/include/CryptoBlob.h"

namespace SearchProtection
{

// -------------------------
// Getters/Setters for prefs
// -------------------------

#ifdef SELFTEST
ProtectionDataStore* g_protection_data_store = NULL; // owned by selftest (search_protection.ot)

void SetProtectionDataStore(ProtectionDataStore* store)
{
	g_protection_data_store = store;
}
#endif // SELFTEST

// Read Data[1-4] preference and break it into index and hash part.
OP_STATUS ReadPref(PrefsCollectionUI::stringpref pref, size_t& index, OpString8& value)
{
	index = UINT_MAX;
	value.Empty();
	OpStringC index_and_value;
#ifdef SELFTEST
	if (g_protection_data_store)
	{
		index_and_value = g_protection_data_store->ReadPref(pref);
	}
	else
#endif // SELFTEST
	{
		index_and_value = g_pcui->GetStringPref(pref);
	}
	if (index_and_value.Length() < 3 + 32) // too short or missing -> ignore
	{
		return OpStatus::OK;
	}
	unsigned int x;
	if (uni_sscanf(index_and_value.CStr(), UNI_L("%3x"), &x) != 1)
	{
		return OpStatus::OK;
	}
	RETURN_IF_ERROR(value.Set(index_and_value.CStr() + 3));
	index = x;
	return OpStatus::OK;
}

// Write index + value into Data[1-4] preference.
OP_STATUS WritePref(PrefsCollectionUI::stringpref pref, size_t index, const OpStringC8& value)
{
	OpString index_and_value;
	if (value.HasContent())
	{
		RETURN_IF_ERROR(index_and_value.AppendFormat("%03x", static_cast<unsigned int>(index)));
		OP_ASSERT(index_and_value.Length() == 3);
		OP_ASSERT(value.Length() == 32);
		RETURN_IF_ERROR(index_and_value.Append(value));
	}
#ifdef SELFTEST
	if (g_protection_data_store)
	{
		return g_protection_data_store->WritePref(pref, index_and_value);
	}
#endif // SELFTEST
	OP_STATUS status;
	RETURN_IF_LEAVE(status = g_pcui->WriteStringL(pref, index_and_value));
	return status;
}


inline PrefsCollectionUI::stringpref HardcodedEngineIdPref(SearchType type)
{
	OP_ASSERT(type == DEFAULT_SEARCH || type == SPEED_DIAL_SEARCH);
	if (type == SPEED_DIAL_SEARCH)
		return PrefsCollectionUI::IdOfHardcodedSpeedDialSearch;
	else
		return PrefsCollectionUI::IdOfHardcodedDefaultSearch;
}

inline OP_STATUS ReadHardcodedEngineId(SearchType type, size_t& index, OpString8& hash)
{
	return ReadPref(HardcodedEngineIdPref(type), index, hash);
}

inline OP_STATUS WriteHardcodedEngineId(SearchType type, size_t index, const OpStringC8& hash)
{
	return WritePref(HardcodedEngineIdPref(type), index, hash);
}


inline PrefsCollectionUI::stringpref ProtectionDataPref(SearchType type)
{
	OP_ASSERT(type == DEFAULT_SEARCH || type == SPEED_DIAL_SEARCH);
	if (type == SPEED_DIAL_SEARCH)
		return PrefsCollectionUI::HashOfSpeedDialSearch;
	else
		return PrefsCollectionUI::HashOfDefaultSearch;
}

inline OP_STATUS ReadProtectionData(SearchType type, OpString8& value)
{
	size_t index = 0;
	return ReadPref(ProtectionDataPref(type), index, value);
}

inline OP_STATUS WriteProtectionData(SearchType type, const OpStringC8& value)
{
	// index is not really used for protection data and will be stripped
	// off by ReadProtectionData
	size_t index = op_rand() % 100;
	return WritePref(ProtectionDataPref(type), index, value);
}


// --------------------------------------------------------------------------------
// Hardcoded search engines and hardcoded search configurations generated by script
// --------------------------------------------------------------------------------

// g_hardcoded_engines: byte array that contains compressed INI string with hardcoded search engines
// g_hardcoded_engines_count: number of hardcoded search engines
// g_hardcoded_engines_uncompressed_size: size of uncompressed g_hardcoded_engines
// g_hardcoded_configurations: array of SearchConfiguration structs
// g_hardcoded_configurations_count: number of structs in g_hardcoded_configurations
// g_global_default_search_index: index of default search engine for regions/languages not in g_hardcoded_configurations
// g_global_speeddial_search_index: index of speed dial search engine for regions/languages not in g_hardcoded_configurations
#include "adjunct/desktop_util/search/hardcoded_searches.inl"

const size_t g_hardcoded_engines_compressed_size = ARRAY_SIZE(g_hardcoded_engines);


// -----------------
// Utility functions
// -----------------

// Calculate MD5 checksum of str + salt.
OP_STATUS CalculateChecksum(OpString8& checksum, const OpStringC& str, const OpStringC8& salt)
{
	OpString8 data8;
	RETURN_IF_ERROR(data8.SetUTF8FromUTF16(str));
	RETURN_IF_ERROR(data8.Append(salt));
	OP_ASSERT(data8.HasContent());
	return StringUtils::CalculateMD5Checksum(data8, checksum);
}

OP_STATUS CalculateProtectionData(OpString8& protection_data, const OpStringC& str, const OpStringC8& salt)
{
	static UINT8 s_key[16] = { 0x8b, 0x4d, 0x14, 0x8b, 0x49, 0x0c, 0x0f, 0xaf, 0x4d, 0xf0, 0x8b, 0xc1, 0xd3, 0xe0, 0x40, 0x50 };
	static UINT8 s_fixed_salt[8] = { 0x56, 0xFF, 0x15, 0x28, 0x01, 0xc6, 0x7d, 0xa1 };
	OpAutoPtr<CryptoBlobEncryption> blob_encryptor(CryptoBlobEncryption::Create(16));
	RETURN_OOM_IF_NULL(blob_encryptor.get());
	RETURN_IF_ERROR(blob_encryptor->SetKey(s_key));
	RETURN_IF_ERROR(blob_encryptor->SetFixedSalt(s_fixed_salt, TRUE));

	OpString8 fingerprint;
	RETURN_IF_ERROR(g_desktop_op_system_info->GetHardwareFingerprint(fingerprint));

	OpString8 str8;
	RETURN_IF_ERROR(str8.SetUTF8FromUTF16(str));
	RETURN_IF_ERROR(str8.Append(fingerprint));
	RETURN_IF_ERROR(str8.Append(salt));

	OpString8 encrypted_str8;
	RETURN_IF_ERROR(blob_encryptor->EncryptBase64(str8.CStr(), encrypted_str8));

	// MD5 it to get smaller string
	return StringUtils::CalculateMD5Checksum(encrypted_str8, protection_data);
}

int search_configuration_cmpf(const void* a, const void* b)
{
	const SearchConfiguration* search_a = static_cast<const SearchConfiguration*>(a);
	const SearchConfiguration* search_b = static_cast<const SearchConfiguration*>(b);
	int result = OpStringC8(search_a->m_region).CompareI(search_b->m_region);
	if (result == 0)
	{
		result = OpStringC8(search_a->m_language).CompareI(search_b->m_language);
	}
	return result;
}

// Find search configuration for specified region and/or language.
// It is assumed that search configurations in configs are sorted first by m_region, then by m_language.
const SearchConfiguration* FindSearchConfiguration(OpStringC8 region,
												   OpStringC8 default_language, // default language for region (DSK-352090)
												   OpStringC8 ui_language,      // current UI language
												   const SearchConfiguration* configs,
												   size_t configs_count)
{
	void* result = NULL;
	if (configs)
	{
		if (region.HasContent() && ui_language.HasContent())
		{
			SearchConfiguration key = { region, ui_language, 0, 0 };
			result = op_bsearch(&key, configs, configs_count, sizeof(SearchConfiguration), search_configuration_cmpf);
		}
		if (!result && region.HasContent())
		{
			SearchConfiguration key = { region, "", 0, 0 };
			result = op_bsearch(&key, configs, configs_count, sizeof(SearchConfiguration), search_configuration_cmpf);
		}
		// if there is default language for current region then it is checked before UI language (DSK-352090)
		if (!result && default_language.HasContent())
		{
			SearchConfiguration key = { "", default_language, 0, 0 };
			result = op_bsearch(&key, configs, configs_count, sizeof(SearchConfiguration), search_configuration_cmpf);
		}
		if (!result && ui_language.HasContent())
		{
			SearchConfiguration key = { "", ui_language, 0, 0 };
			result = op_bsearch(&key, configs, configs_count, sizeof(SearchConfiguration), search_configuration_cmpf);
		}
	}
	return static_cast<SearchConfiguration*>(result);
}


// ---------------------------------------
// Implementation of SearchEngine
// ---------------------------------------

SearchEngine::SearchEngine()
: m_is_valid(FALSE)
, m_prefs(NULL)
, m_suggest_url_inited(FALSE)
{}

#ifdef SELFTEST
void SearchEngine::Reset()
{
	m_prefs = NULL;
	m_is_valid = FALSE;
	m_section_name.Empty();
	m_search.reset(NULL);
	m_suggest_url.Empty();
	m_suggest_url_inited = FALSE;
}
#endif // SELFTEST

OP_STATUS SearchEngine::Init(PrefsFile* prefs, size_t index)
{
	if (prefs)
	{
		m_prefs = prefs;
		RETURN_IF_ERROR(m_section_name.AppendFormat("Search Engine %d", index));
		m_is_valid = m_prefs->IsSection(m_section_name.CStr());
	}
	return m_is_valid ? OpStatus::OK : OpStatus::ERR;
}

OP_BOOLEAN SearchEngine::IsMatch(const SearchTemplate* other_search) const
{
	if (!other_search)
	{
		return OpBoolean::IS_FALSE;
	}
	if (!IsValid())
	{
		return OpStatus::ERR;
	}

	// 1. Compare search templates using UI matching. It is not enough to
	//    match only GUIDs, because GUIDs are not unique for hardcoded
	//    searches. For example variants of Google search for different
	//    languages usually have the same GUID and differ by suggest URL.

	if (! m_search.get())
	{
		SearchTemplate* search;
		RETURN_IF_ERROR(CreateSearchTemplate(search));
		m_search.reset(search);
	}
	// ignore position on personal bar and search key
	m_search->SetPersonalbarPos(other_search->GetPersonalbarPos());
	RETURN_IF_ERROR(m_search->SetKey(other_search->GetKey()));
	if (!m_search->IsMatch(other_search, TRUE))
	{
		return OpBoolean::IS_FALSE;
	}

	// 2. Compare suggest URLs (SearchTemplate::IsMatch ignores them).
	if (m_search->GetSuggestProtocol() != other_search->GetSuggestProtocol())
	{
		return OpBoolean::IS_FALSE;
	}
	OpStringC search_term = UNI_L("{SearchTerm}");
	if (!m_suggest_url_inited)
	{
		OP_STATUS status = m_search->MakeSuggestQuery(search_term, m_suggest_url, SearchTemplate::SEARCH_BAR);
		if (OpStatus::IsError(status) && status != OpStatus::ERR_NOT_SUPPORTED)
		{
			return status;
		}
		m_suggest_url_inited = TRUE;
	}
	OpString other_suggest_url;
	OP_STATUS status = other_search->MakeSuggestQuery(search_term, other_suggest_url, SearchTemplate::SEARCH_BAR);
	if (OpStatus::IsError(status) && status != OpStatus::ERR_NOT_SUPPORTED)
	{
		return status;
	}
	return (m_suggest_url == other_suggest_url) ? OpBoolean::IS_TRUE : OpBoolean::IS_FALSE;
}

OP_STATUS SearchEngine::InitSearchTemplate(SearchTemplate& search) const
{
	if (IsValid())
	{
		TRAPD(status, search.ReadL(m_section_name, m_prefs, SearchTemplate::PACKAGE));
		return status;
	}
	return OpStatus::ERR;
}

OP_STATUS SearchEngine::CreateSearchTemplate(SearchTemplate*& search) const
{
	if (IsValid())
	{
		SearchTemplate* new_search = OP_NEW(SearchTemplate, ());
		RETURN_OOM_IF_NULL(new_search);
		OP_STATUS status = InitSearchTemplate(*new_search);
		if (OpStatus::IsError(status))
		{
			OP_DELETE(new_search);
		}
		else
		{
			search = new_search;
		}
		return status;
	}
	return OpStatus::ERR;
}

// -------------------------------------------------------
// Forced initialization of IDs of fallback search engines
// -------------------------------------------------------

static BOOL g_force_new_ids_of_hardcoded_engines = FALSE;

void ClearIdsOfHardcodedSearches()
{
	// this function can be called during startup, before g_pcui
	// is initialized, so just set the flag for later
	g_force_new_ids_of_hardcoded_engines = TRUE;
}

OP_STATUS InitIdsOfHardcodedSearches(const SearchTemplate* package_default_search,
									 const SearchTemplate* package_speeddial_search)
{
	HardcodedSearchEngines hardcoded_engines;
	return hardcoded_engines.Init(package_default_search, package_speeddial_search);
}


// ----------------------------------------
// Implementation of HardcodedSearchEngines
// ----------------------------------------

OP_STATUS HardcodedSearchEngines::Init(const SearchTemplate* package_default_search,
									   const SearchTemplate* package_speeddial_search)
{
	DecompressZlibStream decompressor;
	StreamBuffer<char> decompressed_stream;
	OP_STATUS deflate_status =
		decompressor.AddData(reinterpret_cast<const char*>(g_hardcoded_engines), g_hardcoded_engines_compressed_size);
	// g_hardcoded_engines is created by script adjunct/desktop_util/search/generate_hardcoded_searches.py
	// and contains search.ini string compressed with Python's zlib module
	// if decompression failed then either there is a problem in the script or zlib module in Opera is in
	// some way incompatible with Python's zlib module
	OP_ASSERT(OpStatus::IsSuccess(deflate_status) || deflate_status == OpStatus::ERR_NO_MEMORY);
	RETURN_IF_ERROR(deflate_status);
	RETURN_IF_ERROR(decompressed_stream.Reserve(g_hardcoded_engines_uncompressed_size));
	RETURN_IF_ERROR(decompressor.Flush(decompressed_stream));
	size_t inflated_size = decompressed_stream.GetFilled();
	OP_ASSERT(inflated_size == g_hardcoded_engines_uncompressed_size);
	unsigned char* decompressed_data = reinterpret_cast<unsigned char*>(decompressed_stream.Release());
	// takes ownership of decompressed_data
	OpMemFile* decompressed_file = OpMemFile::Create(decompressed_data, inflated_size, TRUE);
	if (decompressed_file == NULL)
	{
		OP_DELETE(decompressed_data);
		return OpStatus::ERR_NO_MEMORY;
	}
	OpAutoPtr<OpMemFile> decompressed_file_aptr(decompressed_file);
	RETURN_IF_ERROR(LoadSearchEngines(decompressed_file, g_hardcoded_engines_count));
	return InitSearchEngines(package_default_search, package_speeddial_search,
							 g_global_default_search_index, g_global_speeddial_search_index,
							 g_hardcoded_configurations, g_hardcoded_configurations_count);
}

OP_STATUS HardcodedSearchEngines::LoadSearchEngines(OpFileDescriptor* ini_file, size_t count)
{
#ifdef SELFTEST
	// can be called several times from selftests
	if (m_search_engines.get())
	{
		m_search_engines.reset(NULL);
		m_search_engines_count = 0;
	}
#endif // SELFTEST

	OP_ASSERT(ini_file);
	OpAutoPtr<PrefsFile> prefs(OP_NEW(PrefsFile, (PREFS_STD)));
	RETURN_OOM_IF_NULL(prefs.get());
	RETURN_IF_LEAVE(prefs->ConstructL());
	RETURN_IF_LEAVE(prefs->SetFileL(ini_file)); // creates copy of ini_file
	RETURN_IF_LEAVE(prefs->LoadAllL());
	m_search_engines = prefs;
	m_search_engines_count = count;

#ifdef _DEBUG
	for (size_t i = 0; i < m_search_engines_count; ++i)
	{
		SearchEngine engine;
		OP_STATUS status = engine.Init(m_search_engines.get(), i);
		OP_ASSERT(OpStatus::IsSuccess(status) || OpStatus::IsMemoryError(status));
		if (OpStatus::IsSuccess(status))
		{
			OpStringC hash;
			TRAP(status, hash = engine.GetHashL());
			OP_ASSERT(OpStatus::IsSuccess(status) || OpStatus::IsMemoryError(status));
		}
		else
		{
			break;
		}
	}
#endif // _DEBUG

	return OpStatus::OK;
}

OP_STATUS HardcodedSearchEngines::InitSearchEngines(const SearchTemplate* package_default_search,
													const SearchTemplate* package_speeddial_search,
													size_t global_default_search_index,
													size_t global_speeddial_search_index,
													const SearchConfiguration* configurations,
													size_t configurations_count)
{
	RETURN_VALUE_IF_NULL(m_search_engines.get(), OpStatus::ERR);

#ifdef _DEBUG
	for (size_t i = 0; i < configurations_count; ++i)
	{
		OP_ASSERT(configurations[i].m_default_engine_index < m_search_engines_count);
		OP_ASSERT(configurations[i].m_speeddial_engine_index < m_search_engines_count);
		OpStringC8 region = configurations[i].m_region;
		OpStringC8 language = configurations[i].m_language;
		OP_ASSERT(region.HasContent() || language.HasContent());
		// Search configurations must be sorted by region and language
		if (i > 0)
		{
			int region_cmp = region.CompareI(configurations[i-1].m_region);
			int language_cmp = language.CompareI(configurations[i-1].m_language);
			OP_ASSERT(region_cmp > 0 || (region_cmp == 0 && language_cmp > 0));
		}
	}
#endif // _DEBUG

#ifdef SELFTEST
	// can be called several times from selftests
	m_default_engine.Reset();
	m_speeddial_engine.Reset();
#endif // SELFTEST

	size_t default_engine_index = UINT_MAX;
	size_t speeddial_engine_index = UINT_MAX;

	if (g_force_new_ids_of_hardcoded_engines)
	{
		RETURN_IF_ERROR(WriteHardcodedEngineId(DEFAULT_SEARCH, 0, ""));
		RETURN_IF_ERROR(WriteHardcodedEngineId(SPEED_DIAL_SEARCH, 0, ""));
		g_force_new_ids_of_hardcoded_engines = FALSE;
	}
	else
	{
		RETURN_IF_ERROR(FindByStoredId(DEFAULT_SEARCH, default_engine_index));
		RETURN_IF_ERROR(FindByStoredId(SPEED_DIAL_SEARCH, speeddial_engine_index));
	}

	if ((!IsValidEngineIndex(default_engine_index) || !IsValidEngineIndex(speeddial_engine_index)) &&
		package_default_search && package_speeddial_search)
	{
		RETURN_IF_ERROR(FindByPackageSearches(package_default_search, default_engine_index,
											  package_speeddial_search, speeddial_engine_index));
	}

	if (!IsValidEngineIndex(default_engine_index) || !IsValidEngineIndex(speeddial_engine_index))
	{
		OpString8 region, default_language, ui_language;
		RETURN_IF_ERROR(GetRegion(region));
		RETURN_IF_ERROR(GetDefaultLanguage(default_language));
		RETURN_IF_ERROR(GetLanguage(ui_language));
		const SearchConfiguration* search_config = FindSearchConfiguration(region, default_language, ui_language, configurations, configurations_count);
		if (search_config)
		{
			default_engine_index = search_config->m_default_engine_index;
			speeddial_engine_index = search_config->m_speeddial_engine_index;
		}
	}

	if (!IsValidEngineIndex(default_engine_index) || !IsValidEngineIndex(speeddial_engine_index))
	{
		default_engine_index = global_default_search_index;
		speeddial_engine_index = global_speeddial_search_index;
	}

	if (IsValidEngineIndex(default_engine_index))
	{
		RETURN_IF_ERROR(InitFromEngineIndex(DEFAULT_SEARCH, default_engine_index, m_default_engine));
	}
	if (IsValidEngineIndex(speeddial_engine_index))
	{
		RETURN_IF_ERROR(InitFromEngineIndex(SPEED_DIAL_SEARCH, speeddial_engine_index, m_speeddial_engine));
	}

	return IsValid() ? OpStatus::OK : OpStatus::ERR;
}

OP_STATUS HardcodedSearchEngines::FindByStoredId(SearchType type, size_t& index) const
{
	index = UINT_MAX;
	size_t stored_index;
	OpString8 stored_hash;
	if (OpStatus::IsSuccess(ReadHardcodedEngineId(type, stored_index, stored_hash)) &&
		IsValidEngineIndex(stored_index))
	{
		SearchEngine engine;
		RETURN_IF_ERROR(engine.Init(m_search_engines.get(), stored_index));
		// check that engine has the same checksum
		OpStringC engine_hash;
		RETURN_IF_LEAVE(engine_hash = engine.GetHashL());

		OpString8 region_and_language;
		RETURN_IF_ERROR(GetRegionAndLanguage(region_and_language));

		OpString8 hash_with_lang;
		RETURN_IF_ERROR(CalculateChecksum(hash_with_lang, engine_hash, region_and_language));
		if (hash_with_lang == stored_hash)
		{
			index = stored_index;
		}
	}
	return OpStatus::OK;
}

OP_STATUS HardcodedSearchEngines::FindByPackageSearches(const SearchTemplate* package_default_search,
														size_t& default_engine_index,
														const SearchTemplate* package_speeddial_search,
														size_t& speeddial_engine_index) const
{
	OP_ASSERT(package_default_search && package_speeddial_search);
	default_engine_index = UINT_MAX;
	speeddial_engine_index = UINT_MAX;
	for (size_t i = 0; IsValidEngineIndex(i); ++i)
	{
		SearchEngine hardcoded_engine;
		RETURN_IF_ERROR(hardcoded_engine.Init(m_search_engines.get(), i));
		if (!IsValidEngineIndex(default_engine_index))
		{
			OP_BOOLEAN is_match = hardcoded_engine.IsMatch(package_default_search);
			RETURN_IF_ERROR(is_match);
			if (is_match == OpBoolean::IS_TRUE)
			{
				default_engine_index = i;
			}
		}
		if (!IsValidEngineIndex(speeddial_engine_index))
		{
			OP_BOOLEAN is_match = hardcoded_engine.IsMatch(package_speeddial_search);
			RETURN_IF_ERROR(is_match);
			if (is_match == OpBoolean::IS_TRUE)
			{
				speeddial_engine_index = i;
			}
		}
		if (IsValidEngineIndex(default_engine_index) && IsValidEngineIndex(speeddial_engine_index))
		{
			break;
		}
	}
	return OpStatus::OK;
}

OP_STATUS HardcodedSearchEngines::InitFromEngineIndex(SearchType type, size_t index, SearchEngine& engine)
{
	OP_ASSERT(IsValidEngineIndex(index));
	OP_ASSERT(!engine.IsValid());
	RETURN_IF_ERROR(engine.Init(m_search_engines.get(), index));

	// store ID in prefs; it consists of three parts:
	// - index of hardcoded search
	// - hash of hardcoded search (so ID becomes invalid if hardcoded searches change after upgrade)
	// - current region (so ID becomes invalid if region changes)
	// - current language (so ID becomes invalid if user runs Opera with different LANG)
	// errors here are not fatal, so just ignore them
	OpStringC hash;
	TRAPD(status, hash = engine.GetHashL());
	if (OpStatus::IsSuccess(status))
	{
		OpString8 region_and_language;
		OpString8 hash_with_lang;
		if (OpStatus::IsSuccess(GetRegionAndLanguage(region_and_language)) &&
			OpStatus::IsSuccess(CalculateChecksum(hash_with_lang, hash, region_and_language)))
		{
			OpStatus::Ignore(WriteHardcodedEngineId(type, index, hash_with_lang));
		}
	}
	return OpStatus::OK;
}

const SearchEngine* HardcodedSearchEngines::GetSearchEngine(SearchType type) const
{
	OP_ASSERT(type == DEFAULT_SEARCH || type == SPEED_DIAL_SEARCH);
	const SearchEngine* engine;
	if (type == DEFAULT_SEARCH)
		engine = &m_default_engine;
	else if (type == SPEED_DIAL_SEARCH)
		engine = &m_speeddial_engine;
	else
		return NULL;
	return engine->IsValid() ? engine : NULL;
}

/*static*/
BOOL HardcodedSearchEngines::HasLocalizedSearches()
{
	OpString8 region, default_language, ui_language;
	RETURN_VALUE_IF_ERROR(GetRegionNoOverride(region), FALSE);
	RETURN_VALUE_IF_ERROR(GetDefaultLanguageNoOverride(default_language), FALSE);
	RETURN_VALUE_IF_ERROR(GetLanguageNoOverride(ui_language), FALSE);
	return FindSearchConfiguration(region, default_language, ui_language, g_hardcoded_configurations, g_hardcoded_configurations_count) != NULL;
}

// --------------------------------
// Implementation of SignatureStore
// --------------------------------

OP_STATUS SignatureStore::Init(OpStringC path)
{
	if (path.HasContent())
	{
		OpFile file;
		RETURN_IF_ERROR(file.Construct(path));
		BOOL exists;
		RETURN_IF_ERROR(file.Exists(exists));
		if (exists)
		{
			RETURN_IF_ERROR(file.Open(OPFILE_READ));
			OpFileLength length;
			RETURN_IF_ERROR(file.GetFileLength(length));
			if (length > 0)
			{
				char* strings = OP_NEWA(char, length + 1);
				RETURN_OOM_IF_NULL(strings);
				OpFileLength bytes_read;
				OP_STATUS status = file.Read(strings, length, &bytes_read);
				if (OpStatus::IsError(status) || bytes_read != length)
				{
					OP_DELETEA(strings);
					RETURN_IF_ERROR(status);
					return OpStatus::ERR;
				}
				strings[length] = 0;
				m_strings.reset(strings);
				return InitSignatures();
			}
		}
	}
	return OpStatus::OK;
}

#ifdef SELFTEST
OP_STATUS SignatureStore::Init(const char* signatures, size_t length)
{
	if (signatures && length > 0)
	{
		m_strings.reset(OP_NEWA(char, length + 1));
		RETURN_OOM_IF_NULL(m_strings.get());
		op_memcpy(m_strings.get(), signatures, length);
		m_strings[length] = 0;
		return InitSignatures();
	}
	return OpStatus::OK;
}
#endif // SELFTEST

OP_BOOLEAN SignatureStore::GetByDigest(const OpStringC8& digest, OpString8& signature)
{
	const char* data = NULL;
	RETURN_VALUE_IF_ERROR(m_signatures.GetData(digest.CStr(), &data), OpBoolean::IS_FALSE);
	RETURN_IF_ERROR(signature.Set(data));
	return OpBoolean::IS_TRUE;
}

OP_BOOLEAN SignatureStore::GetByPath(const OpStringC& path, OpString8& signature)
{
	OpString8 path8;
	RETURN_IF_ERROR(path8.Set(path));
	if (path8.HasContent())
	{
		for (char* p = path8.CStr(); *p; ++p)
		{
			if (*p == '\\')
				*p = '/';
		}
	}
	return GetByDigest(path8, signature);
}

inline BOOL next_word(char*& p, char*& start, BOOL norm_pathsep)
{
	while (op_isspace(*p))
		++ p;
	if (!*p)
		return FALSE;
	start = p;
	while (*p && !op_isspace(*p))
	{
		if (norm_pathsep && *p == '\\')
			*p = '/';
		++p;
	}
	if (*p)
		*p++ = 0;
	return TRUE;
}

OP_STATUS SignatureStore::InitSignatures()
{
	char* p = m_strings.get();
	while (*p)
	{
		char* key = NULL;
		char* value = NULL;
		if (!next_word(p, key, TRUE) || !next_word(p, value, FALSE))
		{
			break;
		}
		if (!m_signatures.Contains(key))
		{
			RETURN_IF_ERROR(m_signatures.Add(key, value));
		}
	}
	return OpStatus::OK;
}


// ------------------------
// Implementation of Digest
// ------------------------

/**
 * SHA digest of a file.
 * Object of this class is passed around so that digest is computed only if necessary.
 */
class Digest
{
public:
	// pointer passed in name argument must remain valid at least until Compute() is called
	Digest(const uni_char* name, OpFileFolder folder) : m_name(name), m_folder(folder) {}

	const SSL_varvector32& Get() { OP_ASSERT(m_digest.GetLength() != 0); return m_digest; }

	/**
	 * Load contents of m_folder/m_name file and compute digest. Must be called
	 * at least once before first call to Get. If digest is already computed this
	 * function does nothing.
	 *
	 * @return
	 *  - OK on success
	 *  - ERR_NO_MEMORY on OOM
	 *  - ERR on other errors
	 */
	OP_STATUS Compute();

private:
	const uni_char* m_name;
	OpFileFolder m_folder;
	SSL_varvector32 m_digest; // digest of m_folder/m_name
};

inline size_t RemoveEolns(byte* buffer, size_t length_in)
{
	size_t pos_in = 0, pos_out = 0;
	while (pos_in < length_in)
	{
		if (buffer[pos_in] != '\r' && buffer[pos_in] != '\n')
		{
			if (pos_in != pos_out)
				buffer[pos_out] = buffer[pos_in];
			++ pos_out;
		}
		++ pos_in;
	}
	return pos_out;
}

OP_STATUS Digest::Compute()
{
	if (m_digest.GetLength() == 0)
	{
		OpFile file;
		RETURN_IF_ERROR(file.Construct(m_name, m_folder));
		RETURN_IF_ERROR(file.Open(OPFILE_READ));
		OpFileLength length;
		RETURN_IF_ERROR(file.GetFileLength(length));
		if (length > 0)
		{
			OpAutoArray<byte> buffer(OP_NEWA(byte, length));
			RETURN_OOM_IF_NULL(buffer.get());
			OpFileLength bytes_read;
			RETURN_IF_ERROR(file.Read(buffer.get(), length, &bytes_read));
			OpStatus::Ignore(file.Close());
			if (bytes_read != length)
			{
				return OpStatus::ERR;
			}
			// strip eolns before computing digest to avoid problems with different eoln conventions
			bytes_read = RemoveEolns(buffer.get(), bytes_read);
			SSL_Hash_Pointer digester(SSL_SHA);
			if (digester.Error())
			{
				return OpStatus::ERR;
			}
			digester->CompleteHash(buffer.get(), bytes_read, m_digest);
			if (digester->Error() || m_digest.Error())
			{
				return OpStatus::ERR;
			}
		}
	}
	return OpStatus::OK;
}

#ifdef SELFTEST

OP_STATUS ComputeDigest(const uni_char* name, OpFileFolder folder, OpString8& hex_digest)
{
	Digest digester(name, folder);
	RETURN_IF_ERROR(digester.Compute());
	const SSL_varvector32& digest = digester.Get();
	const BYTE* srcb = reinterpret_cast<const BYTE*>(digest.GetDirect());
	OP_STATUS result = ByteToHexStr(srcb, digest.GetLength(), hex_digest);
	return result;
}

#endif // SELFTEST


// ---------------------------------------------------
// Implementation of SignatureChecker
// ---------------------------------------------------

OP_BOOLEAN SignatureChecker::VerifyFile(const uni_char* name, OpFileFolder folder)
{
#if defined _DEBUG && defined SEARCH_PROTECTION_DISABLE_SIGNATURES
	return OpBoolean::IS_TRUE;
#endif // _DEBUG && SEARCH_PROTECTION_DISABLE_SIGNATURES

	bool custom = false;
	if (folder == OPFILE_REGION_LANGUAGE_CUSTOM_FOLDER || folder == OPFILE_REGION_CUSTOM_FOLDER ||
		folder == OPFILE_LANGUAGE_CUSTOM_FOLDER || folder == OPFILE_INI_CUSTOM_FOLDER)
	{
		custom = true;
	}
	OpFileFolder base_folder = custom ? OPFILE_RESOURCES_CUSTOM_FOLDER : OPFILE_RESOURCES_FOLDER;

	OpString rel_path;
	RETURN_IF_ERROR(GetRelativePath(name, folder, base_folder, rel_path));

	Digest digest(name, folder);

	if (custom)
	{
		// Signatures for search.ini files from [profile]/custom/* folders.
		if (m_custom_signatures.get() == NULL)
		{
			RETURN_IF_ERROR(LoadSignatures(UNI_L("files.sig"), OPFILE_RESOURCES_CUSTOM_FOLDER, m_custom_signatures));
		}
		if (VerifyDigest(digest, m_custom_signatures.get(), TRUE, rel_path) == OpBoolean::IS_TRUE)
		{
			return OpBoolean::IS_TRUE;
		}
		// Files in [profile]/custom folder are not updated and users may still have custom folders from repacks
		// released before Opera got search protection. File files_old.sig contains signatures for search.ini
		// files from old repacks, so they can be still verified.
		if (m_legacy_signatures.get() == NULL)
		{
			RETURN_IF_ERROR(LoadSignatures(UNI_L("files_old.sig"), OPFILE_RESOURCES_FOLDER, m_legacy_signatures));
		}
		if (VerifyDigest(digest, m_legacy_signatures.get(), FALSE, rel_path) == OpBoolean::IS_TRUE)
		{
			return OpBoolean::IS_TRUE;
		}
	}
	else
	{
		// Signatures for search.ini files from [installdir]/region, [installdir]/locale, and [installdir]/defaults folders.
		if (m_regular_signatures.get() == NULL)
		{
			RETURN_IF_ERROR(LoadSignatures(UNI_L("files.sig"), OPFILE_RESOURCES_FOLDER, m_regular_signatures));
		}
		if (VerifyDigest(digest, m_regular_signatures.get(), TRUE, rel_path) == OpBoolean::IS_TRUE)
		{
			return OpBoolean::IS_TRUE;
		}
	}
	return OpBoolean::IS_FALSE;
}

/*static*/
OP_STATUS SignatureChecker::GetRelativePath(const uni_char* name, OpFileFolder folder, OpFileFolder base_folder, OpString& rel_path)
{
	RETURN_IF_ERROR(g_folder_manager->GetFolderPath(folder, rel_path));
	RETURN_IF_ERROR(rel_path.Append(name));

	OpString base_path;
	RETURN_IF_ERROR(g_folder_manager->GetFolderPath(base_folder, base_path));

	if (base_path.HasContent() && rel_path.Find(base_path) == 0)
	{
		rel_path.Delete(0, base_path.Length());
	}
	return OpStatus::OK;
}

/*static*/
OP_STATUS SignatureChecker::LoadSignatures(const uni_char* name, OpFileFolder folder, OpAutoPtr<SignatureStore>& store)
{
	OpString path;
	RETURN_IF_ERROR(g_folder_manager->GetFolderPath(folder, path));
	RETURN_IF_ERROR(path.Append(name));
	SignatureStore* new_store = OP_NEW(SignatureStore, ());
	RETURN_OOM_IF_NULL(new_store);
	OP_STATUS status = new_store->Init(path);
	if (OpStatus::IsSuccess(status))
	{
		store.reset(new_store);
	}
	else
	{
		OP_DELETE(new_store);
	}
	return status;
}

/*static*/
OP_STATUS SignatureChecker::EncodeHex(const SSL_varvector32& src, OpString8& dest)
{
	const BYTE* srcb = reinterpret_cast<const BYTE*>(src.GetDirect());
	return ByteToHexStr(srcb, src.GetLength(), dest);
}

/*static*/
OP_STATUS SignatureChecker::DecodeHex(const OpStringC8& src, SSL_varvector32& dest)
{
	int src_length = src.Length();
	if (src_length == 0 || src_length % 2 != 0)
	{
		return OpStatus::ERR;
	}
	byte* aux = NULL;
	unsigned int aux_length = 0;
	RETURN_IF_ERROR(HexStrToByte(src, aux, aux_length));
	TRAPD(status, dest.SetL(aux, aux_length));
	OP_DELETEA(aux);
	return status;
}

// public key used to verify signatures of package search.ini files
// (DER format)
const byte g_public_key[] = {
	0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
	0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
	0x00, 0xb6, 0xa7, 0x2c, 0x89, 0xd0, 0x17, 0x03, 0x46, 0x8f, 0x60, 0x72, 0x22, 0x62, 0xe9, 0xb6,
	0x52, 0x4c, 0xa5, 0x1a, 0x93, 0xed, 0x97, 0x66, 0x4d, 0xea, 0x4c, 0x38, 0x9f, 0x9d, 0x60, 0xfd,
	0x0d, 0xeb, 0x50, 0x5f, 0xf7, 0x5f, 0x68, 0x20, 0xe2, 0x18, 0x46, 0x9e, 0x61, 0x83, 0x38, 0x22,
	0xad, 0x1f, 0x0b, 0xef, 0x85, 0x4f, 0x46, 0x55, 0x12, 0x9b, 0x59, 0xdb, 0x84, 0xb2, 0xaa, 0x22,
	0x65, 0x15, 0xca, 0x44, 0x7e, 0x11, 0x38, 0x82, 0x65, 0x18, 0x3b, 0x5f, 0xd3, 0xa5, 0x87, 0x12,
	0xcd, 0x52, 0xc6, 0x27, 0xa8, 0xac, 0x9a, 0x01, 0x4f, 0x58, 0x3c, 0x7d, 0x5c, 0x9b, 0xd0, 0x82,
	0x50, 0x31, 0x38, 0x0b, 0x26, 0x74, 0xaf, 0x66, 0xb9, 0xaf, 0xee, 0x94, 0x58, 0xd7, 0xf9, 0xdc,
	0x0f, 0x09, 0x51, 0xcf, 0x37, 0xc0, 0x33, 0x75, 0x6e, 0x9f, 0xe4, 0x5b, 0x1d, 0x1d, 0xaf, 0x7f,
	0x13, 0x42, 0x00, 0x1b, 0x94, 0xe6, 0x3b, 0x48, 0xe9, 0x6e, 0x2d, 0x27, 0x57, 0x42, 0xac, 0x9b,
	0xf3, 0x5e, 0x63, 0x67, 0x21, 0xf5, 0x41, 0x2b, 0x4e, 0x6f, 0xff, 0x22, 0x1f, 0xc3, 0x01, 0x00,
	0x25, 0x2a, 0x16, 0x84, 0xb1, 0x12, 0xe4, 0x47, 0xf9, 0xef, 0x69, 0xbb, 0x7f, 0xd7, 0xe6, 0x5d,
	0x6b, 0x3b, 0x23, 0xc8, 0x5b, 0x10, 0xe4, 0x50, 0xa1, 0x5a, 0xb5, 0x86, 0x7e, 0xbd, 0xce, 0x58,
	0x34, 0x7b, 0x48, 0x6a, 0x63, 0x7f, 0x69, 0xeb, 0x39, 0xdd, 0xd5, 0x18, 0x0d, 0x38, 0x62, 0x57,
	0xc3, 0x77, 0xec, 0xc3, 0x46, 0x8a, 0x96, 0xd7, 0x58, 0x4b, 0x1c, 0xa5, 0x80, 0x00, 0x0a, 0x2d,
	0x7c, 0x04, 0x93, 0xe9, 0xac, 0x17, 0xb2, 0x3d, 0x7e, 0xa5, 0x4d, 0xc0, 0xd4, 0x8f, 0xe3, 0x2f,
	0x8f, 0xaf, 0x37, 0x57, 0xfe, 0x25, 0x84, 0xcb, 0x8e, 0xfb, 0x03, 0x26, 0x15, 0x33, 0xa8, 0x5d,
	0x25, 0x02, 0x03, 0x01, 0x00, 0x01
};

OP_BOOLEAN SignatureChecker::VerifyDigest(class Digest& digest_gen, SignatureStore* signatures, BOOL by_path, const OpStringC& path)
{
	OpString8 refsig_hex;
	OP_BOOLEAN refsig_found = OpBoolean::IS_FALSE;
	if (by_path)
	{
		refsig_found = signatures->GetByPath(path, refsig_hex);
	}
	else
	{
		RETURN_IF_ERROR(digest_gen.Compute());
		OpString8 digest_hex;
		RETURN_IF_ERROR(EncodeHex(digest_gen.Get(), digest_hex));
		refsig_found = signatures->GetByDigest(digest_hex, refsig_hex);
	}
	if (refsig_found != OpBoolean::IS_TRUE)
	{
		return refsig_found;
	}
	OP_ASSERT(refsig_hex.HasContent());

	SSL_varvector32 refsig;
	RETURN_IF_ERROR(DecodeHex(refsig_hex, refsig));

	RETURN_IF_ERROR(digest_gen.Compute());
	const SSL_varvector32& digest = digest_gen.Get();

	if (!m_cipher.get())
	{
		OP_STATUS status = OpStatus::OK;
		m_cipher.reset(g_ssl_api->CreatePublicKeyCipher(SSL_RSA, status));
		RETURN_IF_ERROR(status);
		SSL_varvector32 pubkey_bin_ex;
		pubkey_bin_ex.SetExternal(const_cast<byte*>(g_public_key));
		pubkey_bin_ex.Resize(ARRAY_SIZE(g_public_key));
		m_cipher->LoadAllKeys(pubkey_bin_ex);
		if (m_cipher->Error())
		{
			m_cipher.reset(NULL);
			return OpStatus::ERR;
		}
	}
	if (m_cipher->Verify(digest.GetDirect(), digest.GetLength(), refsig.GetDirect(), refsig.GetLength()))
	{
		return OpBoolean::IS_TRUE;
	}
	return OpBoolean::IS_FALSE;
}


// ---------------------------------------------------
// Generation and validation of search protection data
// ---------------------------------------------------

// Get some noise characters for search protection data.
// New strings (for new types) can be added to this function, but
// existing strings should never be changed, because that would
// invalidate search protection data for all users.
const char* GetChecksumSalt(SearchType type)
{
	OP_ASSERT(type == DEFAULT_SEARCH || type == SPEED_DIAL_SEARCH);
	if (type == DEFAULT_SEARCH)
		return "\x28\x18\xb8\x83\x6e\x21\xe6\x5c\xd0\x45";
	else if (type == SPEED_DIAL_SEARCH)
		return "\x93\x17\x2d\x68\x29\x48\x9b\x54\x16\x40";
	return NULL;
}

OP_BOOLEAN CheckSearch(SearchType type, const SearchTemplate* search)
{
#if defined _DEBUG && defined SEARCH_PROTECTION_DISABLE_PROTECTION
	return OpBoolean::IS_TRUE;
#endif // _DEBUG && SEARCH_PROTECTION_DISABLE_PROTECTION

	OpString8 stored_checksum;
	RETURN_IF_ERROR(ReadProtectionData(type, stored_checksum));

	if (g_run_type->m_type == StartupType::RUNTYPE_FIRST ||
		g_run_type->m_type == StartupType::RUNTYPE_FIRST_NEW_BUILD_NUMBER)
	{
		if (search && search->IsFromPackage())
		{
			// DSK-339985 - URLs in package search.ini can change when Opera is upgraded
			RETURN_IF_ERROR(ProtectSearch(type, search));
			return OpBoolean::IS_TRUE;
		}
	}

	OpString search_url;
	if (search)
	{
		RETURN_IF_ERROR(search->GetUrl(search_url));
	}
	OpString8 search_checksum;
	RETURN_IF_ERROR(CalculateProtectionData(search_checksum, search_url, GetChecksumSalt(type)));
	return (stored_checksum == search_checksum) ? OpBoolean::IS_TRUE : OpBoolean::IS_FALSE;
}

OP_STATUS ProtectSearch(SearchType type, const SearchTemplate* search)
{
	OpString search_url;
	if (search)
	{
		RETURN_IF_ERROR(search->GetUrl(search_url));
	}
	OpString8 checksum;
	RETURN_IF_ERROR(CalculateProtectionData(checksum, search_url, GetChecksumSalt(type)));
	return WriteProtectionData(type, checksum);
}

} // namespace

#endif // DESKTOP_UTIL_SEARCH_ENGINES
