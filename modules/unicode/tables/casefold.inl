/** @file casefold.inl
 * This file is auto-generated by modules/unicode/scripts/make_casefold.py.
 * DO NOT EDIT THIS FILE MANUALLY.
 */

#ifdef USE_UNICODE_INC_DATA
enum CaseFoldSimpleCompressionType {CFC_NO_COMPRESSION,CFC_DELTA,CFC_SET_BIT0,CFC_CLEAR_BIT0,CFC_DELTA_FOR_EVEN,CFC_DELTA_FOR_ODD};

static const CaseFoldFullMapping casefold_full_data[] = {
	{0x00df, {0x0073, 0x0073, 0x0000}}, // LATIN SMALL LETTER SHARP S
	{0x0130, {0x0069, 0x0307, 0x0000}}, // LATIN CAPITAL LETTER I WITH DOT ABOVE
	{0x0149, {0x02bc, 0x006e, 0x0000}}, // LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
	{0x01f0, {0x006a, 0x030c, 0x0000}}, // LATIN SMALL LETTER J WITH CARON
	{0x0390, {0x03b9, 0x0308, 0x0301}}, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
	{0x03b0, {0x03c5, 0x0308, 0x0301}}, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS
	{0x0587, {0x0565, 0x0582, 0x0000}}, // ARMENIAN SMALL LIGATURE ECH YIWN
	{0x1e96, {0x0068, 0x0331, 0x0000}}, // LATIN SMALL LETTER H WITH LINE BELOW
	{0x1e97, {0x0074, 0x0308, 0x0000}}, // LATIN SMALL LETTER T WITH DIAERESIS
	{0x1e98, {0x0077, 0x030a, 0x0000}}, // LATIN SMALL LETTER W WITH RING ABOVE
	{0x1e99, {0x0079, 0x030a, 0x0000}}, // LATIN SMALL LETTER Y WITH RING ABOVE
	{0x1e9a, {0x0061, 0x02be, 0x0000}}, // LATIN SMALL LETTER A WITH RIGHT HALF RING
	{0x1e9e, {0x0073, 0x0073, 0x0000}}, // LATIN CAPITAL LETTER SHARP S
	{0x1f50, {0x03c5, 0x0313, 0x0000}}, // GREEK SMALL LETTER UPSILON WITH PSILI
	{0x1f52, {0x03c5, 0x0313, 0x0300}}, // GREEK SMALL LETTER UPSILON WITH PSILI AND VARIA
	{0x1f54, {0x03c5, 0x0313, 0x0301}}, // GREEK SMALL LETTER UPSILON WITH PSILI AND OXIA
	{0x1f56, {0x03c5, 0x0313, 0x0342}}, // GREEK SMALL LETTER UPSILON WITH PSILI AND PERISPOMENI
	{0x1f80, {0x1f00, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH PSILI AND YPOGEGRAMMENI
	{0x1f81, {0x1f01, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH DASIA AND YPOGEGRAMMENI
	{0x1f82, {0x1f02, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
	{0x1f83, {0x1f03, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH DASIA AND VARIA AND YPOGEGRAMMENI
	{0x1f84, {0x1f04, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
	{0x1f85, {0x1f05, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH DASIA AND OXIA AND YPOGEGRAMMENI
	{0x1f86, {0x1f06, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
	{0x1f87, {0x1f07, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
	{0x1f88, {0x1f00, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PROSGEGRAMMENI
	{0x1f89, {0x1f01, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PROSGEGRAMMENI
	{0x1f8a, {0x1f02, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND VARIA AND PROSGEGRAMMENI
	{0x1f8b, {0x1f03, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND VARIA AND PROSGEGRAMMENI
	{0x1f8c, {0x1f04, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND OXIA AND PROSGEGRAMMENI
	{0x1f8d, {0x1f05, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND OXIA AND PROSGEGRAMMENI
	{0x1f8e, {0x1f06, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
	{0x1f8f, {0x1f07, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
	{0x1f90, {0x1f20, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI
	{0x1f91, {0x1f21, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH DASIA AND YPOGEGRAMMENI
	{0x1f92, {0x1f22, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH PSILI AND VARIA AND YPOGEGRAMMENI
	{0x1f93, {0x1f23, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
	{0x1f94, {0x1f24, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH PSILI AND OXIA AND YPOGEGRAMMENI
	{0x1f95, {0x1f25, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH DASIA AND OXIA AND YPOGEGRAMMENI
	{0x1f96, {0x1f26, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
	{0x1f97, {0x1f27, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
	{0x1f98, {0x1f20, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH PSILI AND PROSGEGRAMMENI
	{0x1f99, {0x1f21, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH DASIA AND PROSGEGRAMMENI
	{0x1f9a, {0x1f22, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH PSILI AND VARIA AND PROSGEGRAMMENI
	{0x1f9b, {0x1f23, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH DASIA AND VARIA AND PROSGEGRAMMENI
	{0x1f9c, {0x1f24, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH PSILI AND OXIA AND PROSGEGRAMMENI
	{0x1f9d, {0x1f25, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH DASIA AND OXIA AND PROSGEGRAMMENI
	{0x1f9e, {0x1f26, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
	{0x1f9f, {0x1f27, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
	{0x1fa0, {0x1f60, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH PSILI AND YPOGEGRAMMENI
	{0x1fa1, {0x1f61, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
	{0x1fa2, {0x1f62, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA AND YPOGEGRAMMENI
	{0x1fa3, {0x1f63, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA AND YPOGEGRAMMENI
	{0x1fa4, {0x1f64, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA AND YPOGEGRAMMENI
	{0x1fa5, {0x1f65, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
	{0x1fa6, {0x1f66, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
	{0x1fa7, {0x1f67, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
	{0x1fa8, {0x1f60, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI
	{0x1fa9, {0x1f61, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PROSGEGRAMMENI
	{0x1faa, {0x1f62, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA AND PROSGEGRAMMENI
	{0x1fab, {0x1f63, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA AND PROSGEGRAMMENI
	{0x1fac, {0x1f64, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA AND PROSGEGRAMMENI
	{0x1fad, {0x1f65, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA AND PROSGEGRAMMENI
	{0x1fae, {0x1f66, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
	{0x1faf, {0x1f67, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
	{0x1fb2, {0x1f70, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH VARIA AND YPOGEGRAMMENI
	{0x1fb3, {0x03b1, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH YPOGEGRAMMENI
	{0x1fb4, {0x03ac, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH OXIA AND YPOGEGRAMMENI
	{0x1fb6, {0x03b1, 0x0342, 0x0000}}, // GREEK SMALL LETTER ALPHA WITH PERISPOMENI
	{0x1fb7, {0x03b1, 0x0342, 0x03b9}}, // GREEK SMALL LETTER ALPHA WITH PERISPOMENI AND YPOGEGRAMMENI
	{0x1fbc, {0x03b1, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ALPHA WITH PROSGEGRAMMENI
	{0x1fc2, {0x1f74, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH VARIA AND YPOGEGRAMMENI
	{0x1fc3, {0x03b7, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI
	{0x1fc4, {0x03ae, 0x03b9, 0x0000}}, // GREEK SMALL LETTER ETA WITH OXIA AND YPOGEGRAMMENI
	{0x1fc6, {0x03b7, 0x0342, 0x0000}}, // GREEK SMALL LETTER ETA WITH PERISPOMENI
	{0x1fc7, {0x03b7, 0x0342, 0x03b9}}, // GREEK SMALL LETTER ETA WITH PERISPOMENI AND YPOGEGRAMMENI
	{0x1fcc, {0x03b7, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER ETA WITH PROSGEGRAMMENI
	{0x1fd2, {0x03b9, 0x0308, 0x0300}}, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND VARIA
	{0x1fd3, {0x03b9, 0x0308, 0x0301}}, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND OXIA
	{0x1fd6, {0x03b9, 0x0342, 0x0000}}, // GREEK SMALL LETTER IOTA WITH PERISPOMENI
	{0x1fd7, {0x03b9, 0x0308, 0x0342}}, // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND PERISPOMENI
	{0x1fe2, {0x03c5, 0x0308, 0x0300}}, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND VARIA
	{0x1fe3, {0x03c5, 0x0308, 0x0301}}, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND OXIA
	{0x1fe4, {0x03c1, 0x0313, 0x0000}}, // GREEK SMALL LETTER RHO WITH PSILI
	{0x1fe6, {0x03c5, 0x0342, 0x0000}}, // GREEK SMALL LETTER UPSILON WITH PERISPOMENI
	{0x1fe7, {0x03c5, 0x0308, 0x0342}}, // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND PERISPOMENI
	{0x1ff2, {0x1f7c, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH VARIA AND YPOGEGRAMMENI
	{0x1ff3, {0x03c9, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH YPOGEGRAMMENI
	{0x1ff4, {0x03ce, 0x03b9, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
	{0x1ff6, {0x03c9, 0x0342, 0x0000}}, // GREEK SMALL LETTER OMEGA WITH PERISPOMENI
	{0x1ff7, {0x03c9, 0x0342, 0x03b9}}, // GREEK SMALL LETTER OMEGA WITH PERISPOMENI AND YPOGEGRAMMENI
	{0x1ffc, {0x03c9, 0x03b9, 0x0000}}, // GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI
	{0xfb00, {0x0066, 0x0066, 0x0000}}, // LATIN SMALL LIGATURE FF
	{0xfb01, {0x0066, 0x0069, 0x0000}}, // LATIN SMALL LIGATURE FI
	{0xfb02, {0x0066, 0x006c, 0x0000}}, // LATIN SMALL LIGATURE FL
	{0xfb03, {0x0066, 0x0066, 0x0069}}, // LATIN SMALL LIGATURE FFI
	{0xfb04, {0x0066, 0x0066, 0x006c}}, // LATIN SMALL LIGATURE FFL
	{0xfb05, {0x0073, 0x0074, 0x0000}}, // LATIN SMALL LIGATURE LONG S T
	{0xfb06, {0x0073, 0x0074, 0x0000}}, // LATIN SMALL LIGATURE ST
	{0xfb13, {0x0574, 0x0576, 0x0000}}, // ARMENIAN SMALL LIGATURE MEN NOW
	{0xfb14, {0x0574, 0x0565, 0x0000}}, // ARMENIAN SMALL LIGATURE MEN ECH
	{0xfb15, {0x0574, 0x056b, 0x0000}}, // ARMENIAN SMALL LIGATURE MEN INI
	{0xfb16, {0x057e, 0x0576, 0x0000}}, // ARMENIAN SMALL LIGATURE VEW NOW
	{0xfb17, {0x0574, 0x056d, 0x0000}}, // ARMENIAN SMALL LIGATURE MEN XEH
};
static const CaseFoldSimpleMappingBMP casefold_simple_data_bmp[] = {
	{0x0000, 0, 1}, // START BMP
	{0x0041, 32, 1}, // LATIN CAPITAL LETTER A
	{0x005b, 0, 0}, // SEPARATOR
	{0x00b5, 775, 5}, // MICRO SIGN
	{0x00b7, 0, 0}, // SEPARATOR
	{0x00c0, 32, 1}, // LATIN CAPITAL LETTER A WITH GRAVE
	{0x00d7, 0, 0}, // SEPARATOR
	{0x00d8, 32, 1}, // LATIN CAPITAL LETTER O WITH STROKE
	{0x00df, 0, 0}, // SEPARATOR
	{0x0100, 1, 2}, // LATIN CAPITAL LETTER A WITH MACRON
	{0x0130, 0, 0}, // SEPARATOR
	{0x0132, 1, 2}, // LATIN CAPITAL LIGATURE IJ
	{0x0138, 0, 0}, // SEPARATOR
	{0x0139, 1, 5}, // LATIN CAPITAL LETTER L WITH ACUTE
	{0x0149, 0, 0}, // SEPARATOR
	{0x014a, 1, 2}, // LATIN CAPITAL LETTER ENG
	{0x0178, -121, 0}, // LATIN CAPITAL LETTER Y WITH DIAERESIS
	{0x0179, 1, 5}, // LATIN CAPITAL LETTER Z WITH ACUTE
	{0x017f, -268, 5}, // LATIN SMALL LETTER LONG S
	{0x0181, 210, 0}, // LATIN CAPITAL LETTER B WITH HOOK
	{0x0182, 1, 2}, // LATIN CAPITAL LETTER B WITH TOPBAR
	{0x0186, 206, 0}, // LATIN CAPITAL LETTER OPEN O
	{0x0187, 1, 5}, // LATIN CAPITAL LETTER C WITH HOOK
	{0x0189, 205, 1}, // LATIN CAPITAL LETTER AFRICAN D
	{0x018b, 1, 5}, // LATIN CAPITAL LETTER D WITH TOPBAR
	{0x018d, 0, 0}, // SEPARATOR
	{0x018e, 79, 0}, // LATIN CAPITAL LETTER REVERSED E
	{0x018f, 202, 0}, // LATIN CAPITAL LETTER SCHWA
	{0x0190, 203, 0}, // LATIN CAPITAL LETTER OPEN E
	{0x0191, 1, 5}, // LATIN CAPITAL LETTER F WITH HOOK
	{0x0193, 205, 0}, // LATIN CAPITAL LETTER G WITH HOOK
	{0x0194, 207, 4}, // LATIN CAPITAL LETTER GAMMA
	{0x0196, 211, 0}, // LATIN CAPITAL LETTER IOTA
	{0x0197, 209, 0}, // LATIN CAPITAL LETTER I WITH STROKE
	{0x0198, 1, 2}, // LATIN CAPITAL LETTER K WITH HOOK
	{0x019a, 0, 0}, // SEPARATOR
	{0x019c, 211, 0}, // LATIN CAPITAL LETTER TURNED M
	{0x019d, 213, 5}, // LATIN CAPITAL LETTER N WITH LEFT HOOK
	{0x019f, 214, 0}, // LATIN CAPITAL LETTER O WITH MIDDLE TILDE
	{0x01a0, 1, 2}, // LATIN CAPITAL LETTER O WITH HORN
	{0x01a6, 218, 0}, // LATIN LETTER YR
	{0x01a7, 1, 5}, // LATIN CAPITAL LETTER TONE TWO
	{0x01a9, 218, 5}, // LATIN CAPITAL LETTER ESH
	{0x01ab, 0, 0}, // SEPARATOR
	{0x01ac, 1, 2}, // LATIN CAPITAL LETTER T WITH HOOK
	{0x01ae, 218, 0}, // LATIN CAPITAL LETTER T WITH RETROFLEX HOOK
	{0x01af, 1, 5}, // LATIN CAPITAL LETTER U WITH HORN
	{0x01b1, 217, 1}, // LATIN CAPITAL LETTER UPSILON
	{0x01b3, 1, 5}, // LATIN CAPITAL LETTER Y WITH HOOK
	{0x01b7, 219, 0}, // LATIN CAPITAL LETTER EZH
	{0x01b8, 1, 2}, // LATIN CAPITAL LETTER EZH REVERSED
	{0x01ba, 0, 0}, // SEPARATOR
	{0x01bc, 1, 2}, // LATIN CAPITAL LETTER TONE FIVE
	{0x01be, 0, 0}, // SEPARATOR
	{0x01c4, 2, 0}, // LATIN CAPITAL LETTER DZ WITH CARON
	{0x01c5, 1, 5}, // LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
	{0x01c7, 2, 0}, // LATIN CAPITAL LETTER LJ
	{0x01c8, 1, 2}, // LATIN CAPITAL LETTER L WITH SMALL LETTER J
	{0x01ca, 2, 0}, // LATIN CAPITAL LETTER NJ
	{0x01cb, 1, 5}, // LATIN CAPITAL LETTER N WITH SMALL LETTER J
	{0x01dd, 0, 0}, // SEPARATOR
	{0x01de, 1, 2}, // LATIN CAPITAL LETTER A WITH DIAERESIS AND MACRON
	{0x01f0, 0, 0}, // SEPARATOR
	{0x01f1, 2, 0}, // LATIN CAPITAL LETTER DZ
	{0x01f2, 1, 2}, // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
	{0x01f6, -97, 0}, // LATIN CAPITAL LETTER HWAIR
	{0x01f7, -56, 0}, // LATIN CAPITAL LETTER WYNN
	{0x01f8, 1, 2}, // LATIN CAPITAL LETTER N WITH GRAVE
	{0x0220, -130, 4}, // LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
	{0x0222, 1, 2}, // LATIN CAPITAL LETTER OU
	{0x0234, 0, 0}, // SEPARATOR
	{0x023a, 10795, 0}, // LATIN CAPITAL LETTER A WITH STROKE
	{0x023b, 1, 5}, // LATIN CAPITAL LETTER C WITH STROKE
	{0x023d, -163, 0}, // LATIN CAPITAL LETTER L WITH BAR
	{0x023e, 10792, 4}, // LATIN CAPITAL LETTER T WITH DIAGONAL STROKE
	{0x0240, 0, 0}, // SEPARATOR
	{0x0241, 1, 5}, // LATIN CAPITAL LETTER GLOTTAL STOP
	{0x0243, -195, 0}, // LATIN CAPITAL LETTER B WITH STROKE
	{0x0244, 69, 0}, // LATIN CAPITAL LETTER U BAR
	{0x0245, 71, 0}, // LATIN CAPITAL LETTER TURNED V
	{0x0246, 1, 2}, // LATIN CAPITAL LETTER E WITH STROKE
	{0x0250, 0, 0}, // SEPARATOR
	{0x0345, 116, 5}, // COMBINING GREEK YPOGEGRAMMENI
	{0x0347, 0, 0}, // SEPARATOR
	{0x0370, 1, 2}, // GREEK CAPITAL LETTER HETA
	{0x0374, 0, 0}, // SEPARATOR
	{0x0376, 1, 2}, // GREEK CAPITAL LETTER PAMPHYLIAN DIGAMMA
	{0x0378, 0, 0}, // SEPARATOR
	{0x0386, 38, 4}, // GREEK CAPITAL LETTER ALPHA WITH TONOS
	{0x0388, 37, 1}, // GREEK CAPITAL LETTER EPSILON WITH TONOS
	{0x038b, 0, 0}, // SEPARATOR
	{0x038c, 64, 4}, // GREEK CAPITAL LETTER OMICRON WITH TONOS
	{0x038e, 63, 1}, // GREEK CAPITAL LETTER UPSILON WITH TONOS
	{0x0390, 0, 0}, // SEPARATOR
	{0x0391, 32, 1}, // GREEK CAPITAL LETTER ALPHA
	{0x03a2, 0, 0}, // SEPARATOR
	{0x03a3, 32, 1}, // GREEK CAPITAL LETTER SIGMA
	{0x03ac, 0, 0}, // SEPARATOR
	{0x03c2, 1, 2}, // GREEK SMALL LETTER FINAL SIGMA
	{0x03c4, 0, 0}, // SEPARATOR
	{0x03cf, 8, 0}, // GREEK CAPITAL KAI SYMBOL
	{0x03d0, -30, 0}, // GREEK BETA SYMBOL
	{0x03d1, -25, 5}, // GREEK THETA SYMBOL
	{0x03d3, 0, 0}, // SEPARATOR
	{0x03d5, -15, 0}, // GREEK PHI SYMBOL
	{0x03d6, -22, 4}, // GREEK PI SYMBOL
	{0x03d8, 1, 2}, // GREEK LETTER ARCHAIC KOPPA
	{0x03f0, -54, 0}, // GREEK KAPPA SYMBOL
	{0x03f1, -48, 5}, // GREEK RHO SYMBOL
	{0x03f3, 0, 0}, // SEPARATOR
	{0x03f4, -60, 0}, // GREEK CAPITAL THETA SYMBOL
	{0x03f5, -64, 5}, // GREEK LUNATE EPSILON SYMBOL
	{0x03f7, 1, 5}, // GREEK CAPITAL LETTER SHO
	{0x03f9, -7, 0}, // GREEK CAPITAL LUNATE SIGMA SYMBOL
	{0x03fa, 1, 2}, // GREEK CAPITAL LETTER SAN
	{0x03fc, 0, 0}, // SEPARATOR
	{0x03fd, -130, 1}, // GREEK CAPITAL REVERSED LUNATE SIGMA SYMBOL
	{0x0400, 80, 1}, // CYRILLIC CAPITAL LETTER IE WITH GRAVE
	{0x0410, 32, 1}, // CYRILLIC CAPITAL LETTER A
	{0x0430, 0, 0}, // SEPARATOR
	{0x0460, 1, 2}, // CYRILLIC CAPITAL LETTER OMEGA
	{0x0482, 0, 0}, // SEPARATOR
	{0x048a, 1, 2}, // CYRILLIC CAPITAL LETTER SHORT I WITH TAIL
	{0x04c0, 15, 0}, // CYRILLIC LETTER PALOCHKA
	{0x04c1, 1, 5}, // CYRILLIC CAPITAL LETTER ZHE WITH BREVE
	{0x04cf, 0, 0}, // SEPARATOR
	{0x04d0, 1, 2}, // CYRILLIC CAPITAL LETTER A WITH BREVE
	{0x0528, 0, 0}, // SEPARATOR
	{0x0531, 48, 1}, // ARMENIAN CAPITAL LETTER AYB
	{0x0557, 0, 0}, // SEPARATOR
	{0x10a0, 7264, 1}, // GEORGIAN CAPITAL LETTER AN
	{0x10c6, 0, 0}, // SEPARATOR
	{0x10c7, 7264, 5}, // GEORGIAN CAPITAL LETTER YN
	{0x10c9, 0, 0}, // SEPARATOR
	{0x10cd, 7264, 5}, // GEORGIAN CAPITAL LETTER AEN
	{0x10cf, 0, 0}, // SEPARATOR
	{0x1e00, 1, 2}, // LATIN CAPITAL LETTER A WITH RING BELOW
	{0x1e96, 0, 0}, // SEPARATOR
	{0x1e9b, -58, 5}, // LATIN SMALL LETTER LONG S WITH DOT ABOVE
	{0x1e9d, 0, 0}, // SEPARATOR
	{0x1e9e, -7615, 4}, // LATIN CAPITAL LETTER SHARP S
	{0x1ea0, 1, 2}, // LATIN CAPITAL LETTER A WITH DOT BELOW
	{0x1f00, 0, 0}, // SEPARATOR
	{0x1f08, -8, 1}, // GREEK CAPITAL LETTER ALPHA WITH PSILI
	{0x1f10, 0, 0}, // SEPARATOR
	{0x1f18, -8, 1}, // GREEK CAPITAL LETTER EPSILON WITH PSILI
	{0x1f1e, 0, 0}, // SEPARATOR
	{0x1f28, -8, 1}, // GREEK CAPITAL LETTER ETA WITH PSILI
	{0x1f30, 0, 0}, // SEPARATOR
	{0x1f38, -8, 1}, // GREEK CAPITAL LETTER IOTA WITH PSILI
	{0x1f40, 0, 0}, // SEPARATOR
	{0x1f48, -8, 1}, // GREEK CAPITAL LETTER OMICRON WITH PSILI
	{0x1f4e, 0, 0}, // SEPARATOR
	{0x1f59, -8, 5}, // GREEK CAPITAL LETTER UPSILON WITH DASIA
	{0x1f61, 0, 0}, // SEPARATOR
	{0x1f68, -8, 1}, // GREEK CAPITAL LETTER OMEGA WITH PSILI
	{0x1f70, 0, 0}, // SEPARATOR
	{0x1f88, -8, 1}, // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PROSGEGRAMMENI
	{0x1f90, 0, 0}, // SEPARATOR
	{0x1f98, -8, 1}, // GREEK CAPITAL LETTER ETA WITH PSILI AND PROSGEGRAMMENI
	{0x1fa0, 0, 0}, // SEPARATOR
	{0x1fa8, -8, 1}, // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI
	{0x1fb0, 0, 0}, // SEPARATOR
	{0x1fb8, -8, 1}, // GREEK CAPITAL LETTER ALPHA WITH VRACHY
	{0x1fba, -74, 1}, // GREEK CAPITAL LETTER ALPHA WITH VARIA
	{0x1fbc, -9, 4}, // GREEK CAPITAL LETTER ALPHA WITH PROSGEGRAMMENI
	{0x1fbe, -7173, 4}, // GREEK PROSGEGRAMMENI
	{0x1fc0, 0, 0}, // SEPARATOR
	{0x1fc8, -86, 1}, // GREEK CAPITAL LETTER EPSILON WITH VARIA
	{0x1fcc, -9, 4}, // GREEK CAPITAL LETTER ETA WITH PROSGEGRAMMENI
	{0x1fce, 0, 0}, // SEPARATOR
	{0x1fd8, -8, 1}, // GREEK CAPITAL LETTER IOTA WITH VRACHY
	{0x1fda, -100, 1}, // GREEK CAPITAL LETTER IOTA WITH VARIA
	{0x1fdc, 0, 0}, // SEPARATOR
	{0x1fe8, -8, 1}, // GREEK CAPITAL LETTER UPSILON WITH VRACHY
	{0x1fea, -112, 1}, // GREEK CAPITAL LETTER UPSILON WITH VARIA
	{0x1fec, -7, 4}, // GREEK CAPITAL LETTER RHO WITH DASIA
	{0x1fee, 0, 0}, // SEPARATOR
	{0x1ff8, -128, 1}, // GREEK CAPITAL LETTER OMICRON WITH VARIA
	{0x1ffa, -126, 1}, // GREEK CAPITAL LETTER OMEGA WITH VARIA
	{0x1ffc, -9, 4}, // GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI
	{0x1ffe, 0, 0}, // SEPARATOR
	{0x2126, -7517, 4}, // OHM SIGN
	{0x2128, 0, 0}, // SEPARATOR
	{0x212a, -8383, 0}, // KELVIN SIGN
	{0x212b, -8262, 5}, // ANGSTROM SIGN
	{0x212d, 0, 0}, // SEPARATOR
	{0x2132, 28, 4}, // TURNED CAPITAL F
	{0x2134, 0, 0}, // SEPARATOR
	{0x2160, 16, 1}, // ROMAN NUMERAL ONE
	{0x2170, 0, 0}, // SEPARATOR
	{0x2183, 1, 5}, // ROMAN NUMERAL REVERSED ONE HUNDRED
	{0x2185, 0, 0}, // SEPARATOR
	{0x24b6, 26, 1}, // CIRCLED LATIN CAPITAL LETTER A
	{0x24d0, 0, 0}, // SEPARATOR
	{0x2c00, 48, 1}, // GLAGOLITIC CAPITAL LETTER AZU
	{0x2c2f, 0, 0}, // SEPARATOR
	{0x2c60, 1, 2}, // LATIN CAPITAL LETTER L WITH DOUBLE BAR
	{0x2c62, -10743, 0}, // LATIN CAPITAL LETTER L WITH MIDDLE TILDE
	{0x2c63, -3814, 0}, // LATIN CAPITAL LETTER P WITH STROKE
	{0x2c64, -10727, 4}, // LATIN CAPITAL LETTER R WITH TAIL
	{0x2c66, 0, 0}, // SEPARATOR
	{0x2c67, 1, 5}, // LATIN CAPITAL LETTER H WITH DESCENDER
	{0x2c6d, -10780, 0}, // LATIN CAPITAL LETTER ALPHA
	{0x2c6e, -10749, 0}, // LATIN CAPITAL LETTER M WITH HOOK
	{0x2c6f, -10783, 0}, // LATIN CAPITAL LETTER TURNED A
	{0x2c70, -10782, 4}, // LATIN CAPITAL LETTER TURNED ALPHA
	{0x2c72, 1, 2}, // LATIN CAPITAL LETTER W WITH HOOK
	{0x2c74, 0, 0}, // SEPARATOR
	{0x2c75, 1, 5}, // LATIN CAPITAL LETTER HALF H
	{0x2c77, 0, 0}, // SEPARATOR
	{0x2c7e, -10815, 1}, // LATIN CAPITAL LETTER S WITH SWASH TAIL
	{0x2c80, 1, 2}, // COPTIC CAPITAL LETTER ALFA
	{0x2ce4, 0, 0}, // SEPARATOR
	{0x2ceb, 1, 5}, // COPTIC CAPITAL LETTER CRYPTOGRAMMIC SHEI
	{0x2cef, 0, 0}, // SEPARATOR
	{0x2cf2, 1, 2}, // COPTIC CAPITAL LETTER BOHAIRIC KHEI
	{0x2cf4, 0, 0}, // SEPARATOR
	{0xa640, 1, 2}, // CYRILLIC CAPITAL LETTER ZEMLYA
	{0xa66e, 0, 0}, // SEPARATOR
	{0xa680, 1, 2}, // CYRILLIC CAPITAL LETTER DWE
	{0xa698, 0, 0}, // SEPARATOR
	{0xa722, 1, 2}, // LATIN CAPITAL LETTER EGYPTOLOGICAL ALEF
	{0xa730, 0, 0}, // SEPARATOR
	{0xa732, 1, 2}, // LATIN CAPITAL LETTER AA
	{0xa770, 0, 0}, // SEPARATOR
	{0xa779, 1, 5}, // LATIN CAPITAL LETTER INSULAR D
	{0xa77d, -35332, 0}, // LATIN CAPITAL LETTER INSULAR G
	{0xa77e, 1, 2}, // LATIN CAPITAL LETTER TURNED INSULAR G
	{0xa788, 0, 0}, // SEPARATOR
	{0xa78b, 1, 5}, // LATIN CAPITAL LETTER SALTILLO
	{0xa78d, -42280, 5}, // LATIN CAPITAL LETTER TURNED H
	{0xa78f, 0, 0}, // SEPARATOR
	{0xa790, 1, 2}, // LATIN CAPITAL LETTER N WITH DESCENDER
	{0xa794, 0, 0}, // SEPARATOR
	{0xa7a0, 1, 2}, // LATIN CAPITAL LETTER G WITH OBLIQUE STROKE
	{0xa7aa, -42308, 4}, // LATIN CAPITAL LETTER H WITH HOOK
	{0xa7ac, 0, 0}, // SEPARATOR
	{0xff21, 32, 1}, // FULLWIDTH LATIN CAPITAL LETTER A
	{0xff3b, 0, 0}, // SEPARATOR
	{0xffff, 0, 0}, // BMP Sentinel
};
static const CaseFoldSimpleMappingNonBMP casefold_simple_data_nonbmp[] = {
	{0x10000, 0, 1}, // NonBMP Start
	{0x10400, 40, 1}, // DESERET CAPITAL LETTER LONG I
	{0x10428, 0, 0}, // SEPARATOR
	{0xffffff, 0, 0}, // END
};
#endif // USE_UNICODE_INC_DATA
