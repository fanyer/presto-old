//2011-04-07 15:18:20.090000
//Generated by modules/probetools/scripts/preprocess_probes.py
//Don't modify unless you know what you do. Better to run script.

#ifndef _PROBEDEFINES_H
#define _PROBEDEFINES_H

enum
{

	//First probe is the root probe which is the parent of all top probes
	OP_PROBE_ROOT = 0x1,

	//---------------------
	//autoproxy
	URL_AUTOPROXYCONFIG_LOADHANDLER_EXECUTESCRIPT = 0x2,
	//1 probes

	//---------------------
	//display
	OP_PROBE_VISUALDEVICE_DISPLAY = 0x3,
	OP_PROBE_PAINTLISTENER_ONPAINT = 0x4,
	//2 probes

	//---------------------
	//doc
	OP_PROBE_FRAMESDOCUMENT_REFLOW = 0x5,
	OP_PROBE_FRAMESDOCUMENT_HANDLELOADING = 0x6,
	OP_PROBE_FRAMESDOCUMENT_LOADDATA = 0x7,
	OP_PROBE_FRAMESDOCUMENT_DISPLAY = 0x8,
	OP_PROBE_HTML_DOCUMENT_DISPLAY = 0x9,
	OP_PROBE_FRAMESDOCUMENT_GETNEWIFRAME = 0xa,
	//6 probes

	//---------------------
	//dochand
	OP_PROBE_DOCUMENTMANAGER_HANDLELOADING = 0xb,
	OP_PROBE_DOCUMENTMANAGER_HANDLEDATALOADED = 0xc,
	OP_PROBE_FDELM_GETHTMLELEMENT = 0xd,
	//3 probes

	//---------------------
	//dom
	OP_PROBE_DOM_FREEELEMENTTREE = 0xe,
	OP_PROBE_DOM_ENVIRONMENTIMPL_ELEMENTINSERTEDINTODOCUMENT = 0xf,
	//2 probes

	//---------------------
	//ecmascript
	ES_EXECUTECONTEXT = 0x10,
	ES_COMPILEPROGRAM = 0x11,
	ES_COMPILEPROGRAM_L = 0x12,
	ESMM_COLLECT = 0x13,
	ES_FOREIGN_OBJECT_FOREIGNGET = 0x14,
	ES_FOREIGN_OBJECT_FOREIGNPUT = 0x15,
	ES_FOREIGN_FUNCTION_CALLORCONSTRUCT = 0x16,
	ES_FOREIGN_FUNCTION_RESTARTCALLORCONSTRUCT = 0x17,
	//8 probes

	//---------------------
	//hardcore
	OP_PROBE_HC_MSG = 0x18,
	//1 probes

	//---------------------
	//img
	OP_PROBE_IMG_LZWCODEDECODER_DECODECODE = 0x19,
	OP_PROBE_IMG_LZWSTRINGTABLE_OUTPUTSTRING = 0x1a,
	OP_PROBE_IMG_GIF_DECODE_DATA = 0x1b,
	OP_PROBE_IMG_JPG_DECODE_DATA = 0x1c,
	OP_PROBE_IMG_PNG_DECODE_DATA = 0x1d,
	OP_PROBE_IMG_COPYTO = 0x1e,
	OP_PROBE_IMG_COPYTO2 = 0x1f,
	OP_PROBE_IMG_COPYTOTRANSPARENT = 0x20,
	//8 probes

	//---------------------
	//layout
	OP_PROBE_DOC_LAYOUTPROPERTIES_INHERIT = 0x21,
	OP_PROBE_HTML_LAYOUT_SETDISPLAYPROPERTIES = 0x22,
	OP_PROBE_CONTAINER_TRAVERSE = 0x23,
	OP_PROBE_BLOCKBOX_TRAVERSE = 0x24,
	OP_PROBE_FLOATINGBOX_TRAVERSE = 0x25,
	OP_PROBE_ABSOLUTEPOSITIONEDBOX_TRAVERSE = 0x26,
	OP_PROBE_TABLECONTENT_TRAVERSE = 0x27,
	OP_PROBE_TABLEROWGROUPBOX_TRAVERSE = 0x28,
	OP_PROBE_TABLEROWBOX_TRAVERSEROW = 0x29,
	OP_PROBE_TABLECELLBOX_TRAVERSECELL = 0x2a,
	OP_PROBE_DOC_AREATRAVERSALOBJECT_ENTERVERTICALBOX = 0x2b,
	OP_PROBE_HTMLAYOUTPROPERTIES_SETCSSPROPERTIESFROMHTML = 0x2c,
	OP_PROBE_HTMLAYOUTPROPERTIES_GETCSSPROPERTIES = 0x2d,
	OP_PROBE_TRAVERSALOBJECT_TRAVERSE = 0x2e,
	OP_PROBE_TABLECELLBOX_COMPUTECELLY = 0x2f,
	OP_PROBE_TABLECELLBOX_GETCELLYOFFSET = 0x30,
	OP_PROBE_TABLECELLBOX_GETBOUNDINGBOX = 0x31,
	OP_PROBE_VERTICALBOX_GETBOUNDINGBOX = 0x32,
	OP_PROBE_TABLECELLBOX_GETHEIGHT = 0x33,
	OP_PROBE_TABLEROWGROUPBOX_GETROWSPANNEDHEIGHT = 0x34,
	OP_PROBE_LAYOUTPROPERTIES_CREATECHILDLAYOUTBOX = 0x35,
	//21 probes

	//---------------------
	//logdoc
	OP_PROBE_HLDOCPROFILE_INSERTELEMENT = 0x36,
	OP_PROBE_HTML_ELEMENT_SUCACTUAL = 0x37,
	OP_PROBE_DOCTREE_NEXTSIBLING = 0x38,
	OP_PROBE_CSSPROPERTYITEM_LOADCSSPROPERTIES = 0x39,
	OP_PROBE_HTML_ELEMENT_CLEAN = 0x3a,
	OP_PROBE_HTML_ELEMENT_CLEANLOCAL = 0x3b,
	OP_PROBE_HTML_ELEMENT_CONSTRUCTATTRVAL = 0x3c,
	OP_PROBE_HTML_ELEMENT_CONSTRUCTL = 0x3d,
	OP_PROBE_HTML_ELEMENT_CONSTRUCTL_1 = 0x3e,
	OP_PROBE_HTML_ELEMENT_CONSTRUCTL_2 = 0x3f,
	OP_PROBE_HTML_ELEMENT_LOADALLCSS = 0x40,
	OP_PROBE_HTML_ELEMENT_LOADTOENDTAG = 0x41,
	OP_PROBE_HTML_ELEMENT_LOAD = 0x42,
	OP_PROBE_HTML_ELEMENT_LOADSTYLE = 0x43,
	OP_PROBE_HTML_ELEMENT_LOADSCRIPT1 = 0x44,
	OP_PROBE_HTML_ELEMENT_LOADSCRIPT2 = 0x45,
	OP_PROBE_HTML_ELEMENT_LOADEXTERNALSCRIPT1 = 0x46,
	OP_PROBE_HTML_ELEMENT_LOADEXTERNALSCRIPT2 = 0x47,
	OP_PROBE_HTML_ELEMENT_FINDATTR = 0x48,
	OP_PROBE_HTML_ELEMENT_FREE = 0x49,
	OP_PROBE_HTML_ELEMENT_GETATTR = 0x4a,
	OP_PROBE_HTML_ELEMENT_GETCELLROWSPAN = 0x4b,
	OP_PROBE_HTML_ELEMENT_GETCONTAININGELEMENT = 0x4c,
	OP_PROBE_HTML_ELEMENT_GETCLASSATTRIBUTE = 0x4d,
	OP_PROBE_HTML_ELEMENT_SETINNERHTML = 0x4e,
	OP_PROBE_HTML5BUFFER_GETLINEANDPOS = 0x4f,
	OP_PROBE_HTML5BUFFER_INCCURRENTPOS = 0x50,
	OP_PROBE_HTML5PARSER_APPENDDATA = 0x51,
	OP_PROBE_HTML5PARSER_PARSEL = 0x52,
	OP_PROBE_HTML5TOKENIZER_GETNEXTTOKENL = 0x53,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEDATAL = 0x54,
	OP_PROBE_HTML5TOKENIZER_TOKENIZETAGOPENL = 0x55,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEENDTAGOPENL = 0x56,
	OP_PROBE_HTML5TOKENIZER_TOKENIZETAGNAMEL = 0x57,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEBEFOREATTRNAMEL = 0x58,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEATTRNAMEL = 0x59,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEAFTERATTRNAMEL = 0x5a,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEBEFOREATTRVALL = 0x5b,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEATTRVALQUOTEDL = 0x5c,
	OP_PROBE_HTML5TOKENIZER_TOKENIZEAFTERATTRVALQUOTEDL = 0x5d,
	OP_PROBE_HTML5TOKENWRAPPER_GETATTRIBUTEL = 0x5e,
	OP_PROBE_HTML5TREEBUILDER_ADDTEXTFROMTOKENL = 0x5f,
	OP_PROBE_HTML5TREEBUILDER_BUILDTREE = 0x60,
	OP_PROBE_HTML5TREEBUILDER_BUILDTREEFRAGMENTL = 0x61,
	OP_PROBE_HTML5TREEBUILDER_CREATEELEMENTL1 = 0x62,
	OP_PROBE_HTML5TREEBUILDER_HANDLESPECIALENDTAG = 0x63,
	OP_PROBE_HTML5TREEBUILDER_INSERTNODEL = 0x64,
	OP_PROBE_HTML5TREEBUILDER_INSERTSTARTTAGL = 0x65,
	OP_PROBE_HTML5TREEBUILDER_INSERTTEXTL = 0x66,
	OP_PROBE_HTML5TREEBUILDER_PUSHOPENELML = 0x67,
	OP_PROBE_LOGDOC_ESFLUSH = 0x68,
	OP_PROBE_LOGDOC_LOADHTML = 0x69,
	OP_PROBE_LOGDOC_LOAD = 0x6a,
	OP_PROBE_LOGDOC_REFLOW = 0x6b,
	OP_PROBE_LOGDOC_GETURLATTR = 0x6c,
	OP_PROBE_LOGDOC_RESOLVEURL = 0x6d,
	OP_PROBE_LOGDOC_DERIVEBASEURL = 0x6e,
	OP_PROBE_LOGDOC_CREATEURLFROMSTRING = 0x6f,
	OP_PROBE_LOGDOC_CREATEURLFROMSTRING2 = 0x70,
	OP_PROBE_LOGDOC_PARSEFRAGMENT = 0x71,
	//60 probes

	//---------------------
	//mdefont
	OP_PROBE_MDEFONT_DRAWSTRING = 0x72,
	OP_PROBE_MDEFONT_STRINGWIDTH = 0x73,
	OP_PROBE_MDEFONT_PROCESS_STRING = 0x74,
	//3 probes

	//---------------------
	//memory
	OP_PROBE_OPMEMPOOLS_FREE = 0x75,
	//1 probes

	//---------------------
	//ns4plugins
	OP_PROBE_PLUGIN_LOADDATA = 0x76,
	//1 probes

	//---------------------
	//search_engine
	OP_PROBE_SEARCH_ENGINE_STRINGTABLE_INSERT = 0x77,
	OP_PROBE_SEARCH_ENGINE_STRINGTABLE_DELETE = 0x78,
	OP_PROBE_SEARCH_ENGINE_STRINGTABLE_PREFLUSH = 0x79,
	OP_PROBE_SEARCH_ENGINE_STRINGTABLE_FLUSH = 0x7a,
	OP_PROBE_SEARCH_ENGINE_STRINGTABLE_COMMIT = 0x7b,
	OP_PROBE_SEARCH_ENGINE_STRINGTABLE_SEARCH = 0x7c,
	//6 probes

	//---------------------
	//style
	OP_PROBE_CSSCOLLECTION_GETPROPERTIES = 0x7d,
	OP_PROBE_CSS_SIMPLESELECTOR_MATCH = 0x7e,
	OP_PROBE_CSS_SIMPLESELECTOR_MATCHTYPE = 0x7f,
	OP_PROBE_CSS_SIMPLESELECTOR_MATCHATTRS = 0x80,
	OP_PROBE_CSS_SELECTOR_MATCH1 = 0x81,
	OP_PROBE_CSS_SELECTOR_MATCH2 = 0x82,
	OP_PROBE_CSS_GETPROPERTIES = 0x83,
	OP_PROBE_CSSCOLLECTION_GETDEFAULTSTYLE = 0x84,
	OP_PROBE_CSS_STYLERULE_MATCH = 0x85,
	OP_PROBE_CSS_SELECTPROPERTY = 0x86,
	OP_PROBE_CSS_SELECTSELECTIONPROPERTY = 0x87,
	OP_PROBE_CSS_RULEITERATOR_PREV = 0x88,
	OP_PROBE_CSS_MATCHATTRS_NTH_CHILD = 0x89,
	OP_PROBE_CSS_MATCHATTRS_ID = 0x8a,
	//14 probes

	//---------------------
	//svg
	OP_PROBE_SVG_DRAW_TEXT = 0x8b,
	OP_PROBE_SVG_RENDER = 0x8c,
	OP_PROBE_SVG_FPS = 0x8d,
	//3 probes

	//---------------------
	//url
	OP_PROBE_URL_MANAGER_AUTOSAVECACHE_L = 0x8e,
	OP_PROBE_URL_REP_WRITECACHEDATA_L = 0x8f,
	OP_PROBE_URL_DATASTORAGE_WRITECACHEDATA_L = 0x90,
	OP_PROBE_URL_MANAGER_WRITEFILES = 0x91,
	//4 probes

	//---------------------
	//util
	OP_PROBE_UTIL_OP_FILE_CONSTRUCT = 0x92,
	OP_PROBE_UTIL_OP_FILE_CONSTRUCTENCRYPTED = 0x93,
	OP_PROBE_UTIL_OP_FILE_CONSTRUCTPATH = 0x94,
	OP_PROBE_UTIL_OP_FILE_TYPE = 0x95,
	OP_PROBE_UTIL_OP_FILE_ISWRITABLE = 0x96,
	OP_PROBE_UTIL_OP_FILE_OPEN = 0x97,
	OP_PROBE_UTIL_OP_FILE_ISOPEN = 0x98,
	OP_PROBE_UTIL_OP_FILE_CLOSE = 0x99,
	OP_PROBE_UTIL_OP_FILE_EOF = 0x9a,
	OP_PROBE_UTIL_OP_FILE_EXISTS = 0x9b,
	OP_PROBE_UTIL_OP_FILE_GETFILEPOS = 0x9c,
	OP_PROBE_UTIL_OP_FILE_SETFILEPOS = 0x9d,
	OP_PROBE_UTIL_OP_FILE_GETFILELENGTH = 0x9e,
	OP_PROBE_UTIL_OP_FILE_SETFILELENGTH = 0x9f,
	OP_PROBE_UTIL_OP_FILE_WRITE = 0xa0,
	OP_PROBE_UTIL_OP_FILE_READ = 0xa1,
	OP_PROBE_UTIL_OP_FILE_READLINE = 0xa2,
	OP_PROBE_UTIL_OP_FILE_CREATECOPY = 0xa3,
	OP_PROBE_UTIL_OP_FILE_SAFECLOSE = 0xa4,
	OP_PROBE_UTIL_OP_FILE_SAFEREPLACE = 0xa5,
	OP_PROBE_UTIL_OP_FILE_COPY = 0xa6,
	OP_PROBE_UTIL_OP_FILE_DELETE = 0xa7,
	OP_PROBE_UTIL_OP_FILE_DELETEFOLDER = 0xa8,
	OP_PROBE_UTIL_OP_FILE_COPYCONTENTS = 0xa9,
	OP_PROBE_UTIL_OP_FILE_GETFOLDERLIST = 0xaa,
	OP_PROBE_UTIL_OP_FILE_GETFULLPATH = 0xab,
	OP_PROBE_UTIL_OP_FILE_GETSERIALIZEDNAME = 0xac,
	OP_PROBE_UTIL_OP_FILE_GETLOCALIZEDPATH = 0xad,
	OP_PROBE_UTIL_OP_FILE_MAKEDIRECTORY = 0xae,
	OP_PROBE_UTIL_OP_FILE_GETNAME = 0xaf,
	OP_PROBE_UTIL_OP_FILE_GETDIRECTORY = 0xb0,
	OP_PROBE_UTIL_OP_FILE_GETLASTMODIFIED = 0xb1,
	OP_PROBE_UTIL_OP_FILE_GETMODE1 = 0xb2,
	OP_PROBE_UTIL_OP_FILE_GETMODE2 = 0xb3,
	OP_PROBE_UTIL_OP_FILE_FLUSH = 0xb4,
	OP_PROBE_UTIL_OP_FILE_PRINT = 0xb5,
	OP_PROBE_UTIL_OP_FILE_SETLISTENER = 0xb6,
	OP_PROBE_UTIL_OP_FILE_READASYNC = 0xb7,
	OP_PROBE_UTIL_OP_FILE_WRITEASYNC = 0xb8,
	OP_PROBE_UTIL_OP_FILE_DELETEASYNC = 0xb9,
	OP_PROBE_UTIL_OP_FILE_FLUSHASYNC = 0xba,
	OP_PROBE_UTIL_OP_FILE_SYNC = 0xbb,
	OP_PROBE_UTIL_OP_FILE_ISASYNCINPROGRESS = 0xbc,
	OP_PROBE_UTIL_OP_FILE_ONDATAREAD = 0xbd,
	OP_PROBE_UTIL_OP_FILE_ONDATAWRITTEN = 0xbe,
	OP_PROBE_UTIL_OP_FILE_ONDELETE = 0xbf,
	OP_PROBE_UTIL_OP_FILE_ONFLUSHED = 0xc0,
	//47 probes

	//---------------------
	//gogi
	OP_PROBE_GOGI_UPDATE_SCREEN = 0xc1,
	OP_PROBE_OP_RUN_SLICE = 0xc2,
	OP_PROBE_GOGI_MOUSE_EVT = 0xc3,
	OP_PROBE_OP_CLOSE_OPERA_WINDOW = 0xc4,
	//4 probes

	//Totally 197 probes in 19 modules
	OP_PROBE_COUNT = 0xc5

};

#endif //_PROBEDEFINES_H