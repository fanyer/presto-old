/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright (C) 1995-2008 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
*/

#ifndef MODULES_LIBOPEAY_LIBOPEAY_CONSTANTS_H
#define MODULES_LIBOPEAY_LIBOPEAY_CONSTANTS_H

#if !defined HAS_COMPLEX_GLOBALS

#ifdef OPENSSL_SYS_WIN32
/* Under Win32 thes are defined in wincrypt.h */
#undef PKCS7_ISSUER_AND_SERIAL
#undef PKCS7_SIGNER_INFO
#undef X509_NAME
#undef X509_CERT_PAIR
#undef OCSP_REQUEST
#undef OCSP_RESPONSE
#endif

#include <openssl/cryptlib.h>
#include <openssl/asn1t.h>
#include <openssl/bn.h>
#ifndef OPENSSL_NO_DH
#include <openssl/dh.h>
#endif
#ifndef OPENSSL_NO_DSA
#include <openssl/dsa.h>
#endif
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#ifndef OPENSSL_NO_RSA
#include <openssl/rsa.h>
#endif
#include <openssl/x509v3.h>

#include "modules/libopeay/crypto/asn1/asn1_locl.h"
#include "modules/libopeay/crypto/evp/evp_locl.h"


class Libopeay_GlobalConst_Data
{
public:
	ASN1_ADB_SEQ_DECLARE(PKCS7);
	ASN1_ADB_SEQ_DECLARE(POLICYQUALINFO);

	ASN1_ADB_TEMPLATE_DECLARE(p7default);
	ASN1_ADB_TEMPLATE_DECLARE(policydefault);

	ASN1_CHOICE_cb_DECLARE(DIST_POINT_NAME);

	ASN1_CHOICE_DECLARE(GENERAL_NAME);

	ASN1_ITEM_TEMPLATE_DECLARE(ASN1_SEQUENCE_ANY);
	ASN1_ITEM_TEMPLATE_DECLARE(ASN1_SET_ANY);
	ASN1_ITEM_TEMPLATE_DECLARE(AUTHORITY_INFO_ACCESS);
	ASN1_ITEM_TEMPLATE_DECLARE(CERTIFICATEPOLICIES);
	ASN1_ITEM_TEMPLATE_DECLARE(CRL_DIST_POINTS);
	ASN1_ITEM_TEMPLATE_DECLARE(GENERAL_NAMES);
	ASN1_ITEM_TEMPLATE_DECLARE(EXTENDED_KEY_USAGE);
	ASN1_ITEM_TEMPLATE_DECLARE(PKCS7_ATTR_SIGN);
	ASN1_ITEM_TEMPLATE_DECLARE(POLICY_MAPPINGS);
	ASN1_ITEM_TEMPLATE_DECLARE(X509_ALGORS);
	ASN1_ITEM_TEMPLATE_DECLARE(X509_NAME_ENTRIES);
	ASN1_ITEM_TEMPLATE_DECLARE(X509_NAME_INTERNAL);
	ASN1_ITEM_TEMPLATE_DECLARE(X509_EXTENSIONS);

#if defined(_SSL_USE_OPENSSL_) && !defined(_USE_SYSTEM_LIBCRYPTO_)
	ASN1_SEQ_AUX_DECLARE(DHparams);
#endif
	ASN1_SEQ_AUX_DECLARE(PKCS7);
	ASN1_SEQ_AUX_DECLARE(PKCS7_RECIP_INFO);
	ASN1_SEQ_AUX_DECLARE(PKCS7_SIGNER_INFO);
	ASN1_SEQ_AUX_DECLARE(RSAPrivateKey);
	ASN1_SEQ_AUX_DECLARE(RSAPublicKey);
	ASN1_SEQ_AUX_DECLARE(X509);
	ASN1_SEQ_AUX_DECLARE(X509_CINF);
	ASN1_SEQ_AUX_DECLARE(X509_PUBKEY);

	ASN1_SEQUENCE_DECLARE(ACCESS_DESCRIPTION);
	ASN1_SEQUENCE_DECLARE(AUTHORITY_KEYID);
	ASN1_SEQUENCE_DECLARE(BASIC_CONSTRAINTS);
	ASN1_SEQUENCE_DECLARE(DIST_POINT);
	ASN1_SEQUENCE_DECLARE(EDIPARTYNAME);
	ASN1_SEQUENCE_DECLARE(GENERAL_SUBTREE);
	ASN1_SEQUENCE_DECLARE(ISSUING_DIST_POINT);
	ASN1_SEQUENCE_DECLARE(NAME_CONSTRAINTS);
	ASN1_SEQUENCE_DECLARE(NOTICEREF);
	ASN1_SEQUENCE_DECLARE(OTHERNAME);
#if defined(_SSL_USE_OPENSSL_) && !defined(_USE_SYSTEM_LIBCRYPTO_)
	ASN1_SEQUENCE_DECLARE(PBE2PARAM);
	ASN1_SEQUENCE_DECLARE(PBKDF2PARAM);
#endif
	ASN1_SEQUENCE_DECLARE(PKCS7_DIGEST);
	ASN1_SEQUENCE_DECLARE(PKCS7_ENC_CONTENT);
	ASN1_SEQUENCE_DECLARE(PKCS7_ENCRYPT);
	ASN1_SEQUENCE_DECLARE(PKCS7_ENVELOPE);
	ASN1_SEQUENCE_DECLARE(PKCS7_ISSUER_AND_SERIAL);
	ASN1_SEQUENCE_DECLARE(PKCS7_SIGN_ENVELOPE);
	ASN1_SEQUENCE_DECLARE(PKCS7_SIGNED);
	ASN1_SEQUENCE_DECLARE(PKEY_USAGE_PERIOD);
	ASN1_SEQUENCE_DECLARE(POLICY_CONSTRAINTS);
	ASN1_SEQUENCE_DECLARE(POLICY_MAPPING);
	ASN1_SEQUENCE_DECLARE(POLICYINFO);
	ASN1_SEQUENCE_DECLARE(POLICYQUALINFO);
	ASN1_SEQUENCE_DECLARE(PROXY_CERT_INFO_EXTENSION);
	ASN1_SEQUENCE_DECLARE(PROXY_POLICY);
	ASN1_SEQUENCE_DECLARE(SXNET);
	ASN1_SEQUENCE_DECLARE(SXNETID);
	ASN1_SEQUENCE_DECLARE(USERNOTICE) ;
	ASN1_SEQUENCE_DECLARE(X509_ALGOR);
	ASN1_SEQUENCE_DECLARE(X509_CERT_AUX);
	ASN1_SEQUENCE_DECLARE(X509_EXTENSION);
	ASN1_SEQUENCE_DECLARE(X509_NAME_ENTRY);
	ASN1_SEQUENCE_DECLARE(X509_SIG);
	ASN1_SEQUENCE_DECLARE(X509_VAL);

	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_ANY);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_BIT_STRING);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_BOOLEAN);
	//ASN1_TYPE_TEMPLATE_DECLARE(ASN1_BMPSTRING);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_ENUMERATED);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_FBOOLEAN);
	//ASN1_TYPE_TEMPLATE_DECLARE(ASN1_GENERALSTRING);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_GENERALIZEDTIME);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_IA5STRING);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_INTEGER);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_NULL);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_OBJECT);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_OCTET_STRING);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_OCTET_STRING_NDEF);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_PRINTABLE);
	//ASN1_TYPE_TEMPLATE_DECLARE(ASN1_PRINTABLESTRING);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_SEQUENCE);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_T61STRING);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_TIME);
	ASN1_TYPE_TEMPLATE_DECLARE(ASN1_UTF8STRING);
	ASN1_TYPE_TEMPLATE_DECLARE(BIGNUM);
	ASN1_TYPE_TEMPLATE_DECLARE(CBIGNUM);
	ASN1_TYPE_TEMPLATE_DECLARE(DIRECTORYSTRING);
	ASN1_TYPE_TEMPLATE_DECLARE(DISPLAYTEXT);
	ASN1_TYPE_TEMPLATE_DECLARE(LONG);
	ASN1_TYPE_TEMPLATE_DECLARE(X509_NAME);
	ASN1_TYPE_TEMPLATE_DECLARE(ZLONG);

#ifndef OPENSSL_NO_DSA
	ASN1_SEQ_AUX_DECLARE(DSA_SIG);
	ASN1_SEQ_AUX_DECLARE(DSAPrivateKey);
	ASN1_SEQ_AUX_DECLARE(DSAparams);
	ASN1_SEQUENCE_DECLARE(dsa_pub_internal);
	ASN1_CHOICE_cb_DECLARE(DSAPublicKey);
	DECLARE_EVP_MD_ITEM(dss1_md);
	DECLARE_MODULE_CONST_ITEM(DSA_METHOD, openssl_dsa_meth);
#endif

#ifndef OPENSSL_NO_OCSP
	ASN1_SEQUENCE_DECLARE(OCSP_SIGNATURE);
	ASN1_SEQUENCE_DECLARE(OCSP_CERTID);
	ASN1_SEQUENCE_DECLARE(OCSP_ONEREQ);
	ASN1_SEQUENCE_DECLARE(OCSP_REQINFO);
	ASN1_SEQUENCE_DECLARE(OCSP_REQUEST);
	ASN1_SEQUENCE_DECLARE(OCSP_RESPBYTES);
	ASN1_SEQUENCE_DECLARE(OCSP_RESPONSE);
	ASN1_CHOICE_DECLARE(OCSP_RESPID);
	ASN1_SEQUENCE_DECLARE(OCSP_REVOKEDINFO);
	ASN1_CHOICE_DECLARE(OCSP_CERTSTATUS);
	ASN1_SEQUENCE_DECLARE(OCSP_SINGLERESP);
	ASN1_SEQUENCE_DECLARE(OCSP_RESPDATA);
	ASN1_SEQUENCE_DECLARE(OCSP_BASICRESP);
	ASN1_SEQUENCE_DECLARE(OCSP_CRLID);
	ASN1_SEQUENCE_DECLARE(OCSP_SERVICELOC);
#endif

#ifdef LIBOPEAY_PKCS12_SUPPORT
	ASN1_SEQUENCE_DECLARE(PKCS12);
	ASN1_SEQUENCE_DECLARE(PKCS12_MAC_DATA);
	ASN1_ADB_TEMPLATE_DECLARE(bag_default);
	ASN1_ADB_SEQ_DECLARE(PKCS12_BAGS);
	ASN1_SEQUENCE_DECLARE(PKCS12_BAGS);
	ASN1_ADB_TEMPLATE_DECLARE(safebag_default);
	ASN1_ADB_SEQ_DECLARE(PKCS12_SAFEBAG);
	ASN1_SEQUENCE_DECLARE(PKCS12_SAFEBAG);
	ASN1_ITEM_TEMPLATE_DECLARE(PKCS12_SAFEBAGS);
	ASN1_ITEM_TEMPLATE_DECLARE(PKCS12_AUTHSAFES);
	ASN1_SEQUENCE_DECLARE(PBEPARAM);
#endif

#ifdef LIBOPEAY_ASYNCHRONOUS_KEYGENERATION
	ASN1_SEQ_AUX_DECLARE(X509_REQ_INFO);
	ASN1_SEQUENCE_DECLARE(NETSCAPE_SPKAC);
	ASN1_SEQ_AUX_DECLARE(X509_REQ);
	ASN1_SEQUENCE_DECLARE(NETSCAPE_SPKI);
#endif

#if defined LIBOPEAY_PKCS12_SUPPORT || defined LIBOPEAY_ASYNCHRONOUS_KEYGENERATION || defined USE_OPENSSL_CERTIFICATE_VERIFICATION
	ASN1_SEQ_AUX_DECLARE(PKCS8_PRIV_KEY_INFO);
#endif

#if defined _SSL_USE_OPENSSL_ || defined USE_OPENSSL_CERTIFICATE_VERIFICATION
	ASN1_SEQUENCE_DECLARE(X509_REVOKED);
	ASN1_SEQ_AUX_DECLARE(X509_CRL);
	ASN1_SEQ_AUX_DECLARE(X509_CRL_INFO);
#if defined(_SSL_USE_OPENSSL_) && !defined(_USE_SYSTEM_LIBCRYPTO_)
	ASN1_SEQ_AUX_DECLARE(NETSCAPE_CERT_SEQUENCE);
#endif
#endif // _SSL_USE_OPENSSL_ || USE_OPENSSL_CERTIFICATE_VERIFICATION

#if defined _SSL_USE_OPENSSL_ || defined USE_OPENSSL_CERTIFICATE_VERIFICATION
	ASN1_CHOICE_DECLARE(X509_ATTRIBUTE_SET);
	ASN1_SEQUENCE_DECLARE(X509_ATTRIBUTE);
#endif // _SSL_USE_OPENSSL_ || USE_OPENSSL_CERTIFICATE_VERIFICATION

	DECLARE_X509V3_EXT_METHOD(v3_akey_id);
	DECLARE_X509V3_EXT_METHOD(v3_bcons);
	DECLARE_X509V3_EXT_METHOD(v3_cpols);
	DECLARE_X509V3_EXT_METHOD(v3_crl_invdate);
	DECLARE_X509V3_EXT_METHOD(v3_crl_hold);
	DECLARE_X509V3_EXT_METHOD(v3_crl_num);
	DECLARE_X509V3_EXT_METHOD(v3_crl_reason);
	DECLARE_X509V3_EXT_METHOD(v3_crld);
	DECLARE_X509V3_EXT_METHOD(v3_delta_crl);
	DECLARE_X509V3_EXT_METHOD(v3_ext_ku);
	DECLARE_X509V3_EXT_METHOD(v3_freshest_crl);
	DECLARE_X509V3_EXT_METHOD(v3_idp);
	DECLARE_X509V3_EXT_METHOD(v3_info);
	DECLARE_X509V3_EXT_METHOD(v3_inhibit_anyp);
	DECLARE_X509V3_EXT_METHOD(v3_key_usage);
	DECLARE_X509V3_EXT_METHOD(v3_name_constraints);
	DECLARE_X509V3_EXT_METHOD(v3_nscert);
	DECLARE_X509V3_EXT_METHOD(v3_ocsp_accresp);
	DECLARE_X509V3_EXT_METHOD(v3_ocsp_acutoff);
	DECLARE_X509V3_EXT_METHOD(v3_ocsp_crlid);
	DECLARE_X509V3_EXT_METHOD(v3_ocsp_nocheck);
	DECLARE_X509V3_EXT_METHOD(v3_ocsp_nonce);
	DECLARE_X509V3_EXT_METHOD(v3_ocsp_serviceloc);
	DECLARE_X509V3_EXT_METHOD(v3_pci);
	DECLARE_X509V3_EXT_METHOD(v3_pkey_usage_period);
	DECLARE_X509V3_EXT_METHOD(v3_policy_constraints);
	DECLARE_X509V3_EXT_METHOD(v3_policy_mappings);
	DECLARE_X509V3_EXT_METHOD(v3_sinfo);
	DECLARE_X509V3_EXT_METHOD(v3_skey_id);
	DECLARE_X509V3_EXT_METHOD(v3_sxnet);

#ifndef OPENSSL_NO_RFC3779
	DECLARE_X509V3_EXT_METHOD(v3_addr);
	DECLARE_X509V3_EXT_METHOD(v3_asid);
#endif

	DECLARE_BIO_METHOD_ITEM(bio_enc__methods_enc);
	DECLARE_BIO_METHOD_ITEM(bio_md__methods_md);
	DECLARE_BIO_METHOD_ITEM(bss_mem__mem_method);
	DECLARE_BIO_METHOD_ITEM(bss_null__null_method);

#ifdef _SSL_USE_OPENSSL_
	DECLARE_BLOCK_CIPHER(aes_128);
	DECLARE_BLOCK_CIPHER(aes_256);
	DECLARE_BLOCK_CIPHER(des_ede3);
	DECLARE_EVP_CIPHER_ITEM(r4_cipher);
#endif // _SSL_USE_OPENSSL_
#ifdef LIBOPEAY_USE_RC4_256
	DECLARE_EVP_CIPHER_ITEM(r4_256_cipher);
#endif
#if defined SSL_USE_WEAK_CIPHERS
	DECLARE_BLOCK_CIPHER(des_ede);
	DECLARE_EVP_CIPHER_ITEM(r4_40_cipher);
#endif
#if defined LIBOPEAY_PKCS12_SUPPORT || defined SSL_USE_WEAK_CIPHERS
	DECLARE_EVP_CIPHER_ITEM(rc2_cbc);
	DECLARE_EVP_CIPHER_ITEM(r2_40_cbc_cipher);
#endif

#ifndef OPENSSL_NO_MD2
	DECLARE_EVP_MD_ITEM(md2_md);
#endif
	DECLARE_EVP_MD_ITEM(md5_md);
	DECLARE_EVP_MD_ITEM(sha1_md);
	DECLARE_EVP_MD_ITEM(sha224_md);
	DECLARE_EVP_MD_ITEM(sha256_md);
	DECLARE_EVP_MD_ITEM(sha384_md);
	DECLARE_EVP_MD_ITEM(sha512_md);
#ifndef OPENSSL_NO_RIPEMD
	DECLARE_EVP_MD_ITEM(ripemd160_md);
#endif

	// Const items. Sorted alphabetically by name.
	DECLARE_MODULE_CONST_ITEM(ASN1_PRIMITIVE_FUNCS,         bignum_pf);
	DECLARE_MODULE_CONST_ITEM(BIGNUM,                       const_one);
#ifndef OPENSSL_NO_DH
	DECLARE_MODULE_CONST_ITEM(DH_METHOD,                    dh_ossl);
#endif
#if (defined(_SSL_USE_OPENSSL_) || defined(USE_OPENSSL_CERTIFICATE_VERIFICATION)) && !defined(_USE_SYSTEM_LIBCRYPTO_) && !defined(OPENSSL_NO_DH)
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         dh_ameth__dh_asn1_meth);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_METHOD,              dh_pmeth__dh_pkey_meth);
#endif
#if (defined(_SSL_USE_OPENSSL_) || defined(USE_OPENSSL_CERTIFICATE_VERIFICATION)) && !defined(_USE_SYSTEM_LIBCRYPTO_) && !defined(OPENSSL_NO_DSA)
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         dsa_ameth__dsa_asn1_meth0);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         dsa_ameth__dsa_asn1_meth1);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         dsa_ameth__dsa_asn1_meth2);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         dsa_ameth__dsa_asn1_meth3);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         dsa_ameth__dsa_asn1_meth4);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_METHOD,              dsa_pmeth__dsa_pkey_meth);
#endif

	DECLARE_MODULE_CONST_ITEM(ERR_FNS,                      err__err_defaults);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         hm_ameth__hmac_asn1_meth);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_METHOD,              hm_pmeth__hmac_pkey_meth);
	DECLARE_MODULE_CONST_ITEM(ASN1_PRIMITIVE_FUNCS,         long_pf);
#if (defined(_SSL_USE_OPENSSL_) || defined(USE_OPENSSL_CERTIFICATE_VERIFICATION) || defined(EXTERNAL_SSL_OPENSSL_IMPLEMENTATION)) && !defined(_USE_SYSTEM_LIBCRYPTO_)
	DECLARE_MODULE_CONST_ITEM(RAND_METHOD,                  rand_ssleay_meth);
#endif
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         rsa_ameth__rsa_asn1_meth0);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_ASN1_METHOD,         rsa_ameth__rsa_asn1_meth1);
	DECLARE_MODULE_CONST_ITEM(RSA_METHOD,                   rsa_pkcs1_eay_meth);
	DECLARE_MODULE_CONST_ITEM(EVP_PKEY_METHOD,              rsa_pmeth__rsa_pkey_meth);
	DECLARE_MODULE_CONST_ITEM(X509_CRL_METHOD,              x_crl__int_crl_meth);
	DECLARE_MODULE_CONST_ITEM(ASN1_EXTERN_FUNCS,            x509_name_ff);

	// Const arrays. Sorted alphabetically by name.
	DECLARE_MODULE_CONST_ARRAY(const EVP_PKEY_ASN1_METHOD*, ameth_lib__standard_methods);
	DECLARE_MODULE_CONST_ARRAY(struct tag_name_st,          asn1_gen__tnst);
	DECLARE_MODULE_CONST_ARRAY(const char*,                 asn1_mon);
	DECLARE_MODULE_CONST_ARRAY(ENUMERATED_NAMES,            crl_reasons);
	DECLARE_MODULE_CONST_ARRAY(X509_VERIFY_PARAM,           default_table);
#if defined(_SSL_USE_OPENSSL_) && !defined(_USE_SYSTEM_LIBCRYPTO_) && defined(LIBOPEAY_PKCS12_SUPPORT)
	DECLARE_MODULE_CONST_ARRAY(struct evp_pbe_ctl_st,       evp_pbe__builtin_pbe);
#endif
	DECLARE_MODULE_CONST_ARRAY(const X509V3_EXT_METHOD*,    ext_dat__standard_exts);
	DECLARE_MODULE_CONST_ARRAY(BIT_STRING_BITNAME,          key_usage_type_table);
#ifndef OPERA_SMALL_VERSION
	DECLARE_MODULE_CONST_ARRAY(unsigned int,                ln_objs);
#endif
#ifdef ADS12
	DECLARE_MODULE_CONST_ARRAY(unsigned char,               lvalues);
#endif
	DECLARE_MODULE_CONST_ARRAY(ASN1_OBJECT,                 nid_objs);
	DECLARE_MODULE_CONST_ARRAY(BIT_STRING_BITNAME,          ns_cert_type_table);
	DECLARE_MODULE_CONST_ARRAY(unsigned int,                obj_objs);
	DECLARE_MODULE_CONST_ARRAY(struct nid_triple_st,        obj_xref__sigoid_srt);
	// It's important that obj_xref__sigoid_srt_xref is initialized
	// after obj_xref__sigoid_srt.
	DECLARE_MODULE_CONST_ARRAY(const struct nid_triple_st*, obj_xref__sigoid_srt_xref);
	DECLARE_MODULE_CONST_ARRAY(const EVP_PKEY_METHOD*,      pmeth_lib__standard_methods);
	DECLARE_MODULE_CONST_ARRAY(BIT_STRING_BITNAME,          v3_crld__reason_flags);
#ifndef OPERA_SMALL_VERSION
	DECLARE_MODULE_CONST_ARRAY(unsigned int,                sn_objs);
#endif
	DECLARE_MODULE_CONST_ARRAY(X509_TRUST,                  trstandard);
	DECLARE_MODULE_CONST_ARRAY(X509V3_EXT_METHOD,           v3_ns_ia5_list);
	DECLARE_MODULE_CONST_ARRAY(X509V3_EXT_METHOD,           v3_alt);
	DECLARE_MODULE_CONST_ARRAY(X509_PURPOSE,                xstandard);
};

#define libopeay_CONST_MODULE_CLASS_NAME Libopeay_GlobalConst_Data

#endif /* HAS_COMPLEX_GLOBALS */

#endif /* MODULES_LIBOPEAY_LIBOPEAY_CONSTANTS_H*/
