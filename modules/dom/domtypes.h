/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright (C) 2003-2010 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.
** It may not be distributed under any circumstances.
*/

#ifndef DOM_TYPES_H
#define DOM_TYPES_H

#include "modules/ecmascript/ecmascript.h"

/** Element groups, used in collection handling. */
enum DOM_HTMLElement_Group
{
	ALL,
	ALLELEMENTS,
	CHILDREN,
	CHILDNODES,
	OPTIONS,
	SELECTED_OPTIONS,
	IMAGES,
	FORMELEMENTS,
	APPLETS,
	LINKS,
	FORMS,
	ANCHORS,
	DOCUMENTNODES,
	EMBEDS,
	PLUGINS,
	AREAS,
	TABLE_ROWS,
	TABLE_SECTION_ROWS,
	TABLE_CELLS, // MSIEism
	TABLE_ROW_CELLS,
	TBODIES,
	NAME_IN_WINDOW,
	SCRIPTS,
	STYLESHEETS
};

/** DOM object types, used with DOM_Object::IsA. */
enum DOM_ObjectType
{
	DOM_TYPE_OBJECT = ES_HOSTOBJECT_DOM,

	DOM_TYPE_PROXY_OBJECT,
	DOM_TYPE_FUNCTION,
	DOM_TYPE_NODE,
	DOM_TYPE_NODELIST,
	DOM_TYPE_NAMEDNODEMAP,
	DOM_TYPE_ELEMENT,
	DOM_TYPE_HTML_ELEMENT,
	DOM_TYPE_ATTR,
	DOM_TYPE_CHARACTERDATA,
	DOM_TYPE_TEXT,
	DOM_TYPE_COMMENT,
	DOM_TYPE_CDATASECTION,
	DOM_TYPE_DOCUMENT,
	DOM_TYPE_XML_DOCUMENT,
	DOM_TYPE_FAKE_DOCUMENT,
	DOM_TYPE_HTML_DOCUMENT,
	DOM_TYPE_DOCUMENTFRAGMENT,
	DOM_TYPE_DOCUMENTTYPE,
	DOM_TYPE_PROCESSINGINSTRUCTION,
	DOM_TYPE_DOMIMPLEMENTATION,
	DOM_TYPE_DOMCONFIGURATION,
	DOM_TYPE_DOMSTRINGLIST,
	DOM_TYPE_DOMTOKENLIST,
	DOM_TYPE_DOMSETTABLETOKENLIST,
	DOM_TYPE_ENTITY,
	DOM_TYPE_NOTATION,
	DOM_TYPE_HTML_IMPLEMENTATION,
	DOM_TYPE_COLLECTION,
	DOM_TYPE_HTML_OPTIONS_COLLECTION,
	DOM_TYPE_HTML_FORMELEMENT,
	DOM_TYPE_HTML_SELECTELEMENT,
	DOM_TYPE_HTML_INPUTELEMENT,
	DOM_TYPE_HTML_OPTGROUPELEMENT,
	DOM_TYPE_HTML_OPTIONELEMENT,
	DOM_TYPE_HTML_TABLEELEMENT,
	DOM_TYPE_HTML_TABLEROWELEMENT,
	DOM_TYPE_HTML_TABLESECTIONELEMENT,
	DOM_TYPE_HTML_FRAMEELEMENT,
	DOM_TYPE_EVENT,
	DOM_TYPE_CUSTOMEVENT,
	DOM_TYPE_UIEVENT,
	DOM_TYPE_MOUSEEVENT,
	DOM_TYPE_KEYBOARDEVENT,
	DOM_TYPE_MUTATIONEVENT,
	DOM_TYPE_REMOTEEVENT,
	DOM_TYPE_VXMLEVENT,
	DOM_TYPE_USERJSEVENT,
	DOM_TYPE_CROSSDOCUMENTMESSAGEEVENT,
	DOM_TYPE_HASHCHANGEEVENT,
	DOM_TYPE_TIMEEVENT,
	DOM_TYPE_ERROREVENT,
	DOM_TYPE_NODEITERATOR,
	DOM_TYPE_TREEWALKER,
	DOM_TYPE_RANGE,
	DOM_TYPE_STYLESHEET,
	DOM_TYPE_CSS_CONDITIONALRULE,
	DOM_TYPE_CSS_KEYFRAMESRULE,
	DOM_TYPE_CSS_MEDIARULE,
	DOM_TYPE_CSS_SUPPORTSRULE,
	DOM_TYPE_CSS_RULE,
	DOM_TYPE_CSS_RULELIST,
	DOM_TYPE_CSS_STYLESHEET,
	DOM_TYPE_CSS_STYLEDECLARATION,
	DOM_TYPE_CSS_TRANSFORMVALUE,
	DOM_TYPE_CSS_MATRIX,
	DOM_TYPE_BLOB,
	DOM_TYPE_FILE,
	DOM_TYPE_FILELIST,
	DOM_TYPE_FILEREADER,
	DOM_TYPE_FILEREADERSYNC,
	DOM_TYPE_STYLESHEETLIST,
	DOM_TYPE_MEDIALIST,
	DOM_TYPE_MEDIAQUERYLIST,
	DOM_TYPE_LSPARSER,
	DOM_TYPE_DOMPARSER,
	DOM_TYPE_LSSERIALIZER,
	DOM_TYPE_XMLSERIALIZER,
	DOM_TYPE_WINDOW,
	DOM_TYPE_FAKE_WINDOW,
	DOM_TYPE_HISTORY,
	DOM_TYPE_LOCATION,
	DOM_TYPE_NAVIGATOR,
	DOM_TYPE_OPERA,
	DOM_TYPE_PLUGINARRAY,
	DOM_TYPE_JAVAOBJECT,
	DOM_TYPE_JAVAARRAY,
	DOM_TYPE_JAVACLASS,
	DOM_TYPE_JAVAMETHOD,
	DOM_TYPE_HTTPREQUEST,
	DOM_TYPE_XMLHTTPREQUEST,
	DOM_TYPE_XMLHTTPREQUEST_UPLOAD,
	DOM_TYPE_HTTPINPUTSTREAM,
	DOM_TYPE_HTTPOUTPUTSTREAM,
	DOM_TYPE_XPATHEVALUATOR,
	DOM_TYPE_XPATHEXPRESSION,
	DOM_TYPE_XPATHNSRESOLVER,
	DOM_TYPE_XPATHRESULT,
	DOM_TYPE_XPATHRESULT_NODELIST,
	DOM_TYPE_XPATHNAMESPACE,
	DOM_TYPE_DATASTORAGE,
	DOM_TYPE_EVENTLOOP,
	DOM_TYPE_HTML_MEDIAELEMENT,
	DOM_TYPE_HTML_VIDEOELEMENT,
	DOM_TYPE_HTML_AUDIOELEMENT,
	DOM_TYPE_HTML_SOURCEELEMENT,
	DOM_TYPE_PROGRESSEVENT,
	DOM_TYPE_MEDIAERROR,
	DOM_TYPE_TIMERANGES,
	DOM_TYPE_TEXTTRACK,
	DOM_TYPE_TEXTTRACKLIST,
	DOM_TYPE_TEXTTRACKCUE,
	DOM_TYPE_TEXTTRACKCUELIST,
	DOM_TYPE_HTML_CANVASELEMENT,
	DOM_TYPE_CANVASCONTEXT2D,
	DOM_TYPE_CANVASCONTEXTWEBGL,
	DOM_TYPE_CANVASGRADIENT,
	DOM_TYPE_CANVASPATTERN,
	DOM_TYPE_CANVASIMAGEDATA,
	DOM_TYPE_CANVASPIXELARRAY,
	DOM_TYPE_WEBGLCONTEXTATTRIBUTES,
	DOM_TYPE_WEBGLOBJECT,
	DOM_TYPE_WEBGLBUFFER,
	DOM_TYPE_WEBGLEXTENSION,
	DOM_TYPE_WEBGLFRAMEBUFFER,
	DOM_TYPE_WEBGLPROGRAM,
	DOM_TYPE_WEBGLRENDERBUFFER,
	DOM_TYPE_WEBGLSHADER,
	DOM_TYPE_WEBGLTEXTURE,
	DOM_TYPE_WEBGLOBJECTARRAY,
	DOM_TYPE_WEBGLUNIFORMLOCATION,
	DOM_TYPE_WEBGLACTIVEINFO,
	DOM_TYPE_SVG_DOCUMENT,
	DOM_TYPE_SVG_OBJECT,
	DOM_TYPE_SVG_LIST,
	DOM_TYPE_SVG_STRING_LIST,
	DOM_TYPE_SVG_ELEMENT,
	DOM_TYPE_SVG_IMPLEMENTATION,
	DOM_TYPE_SVG_ELEMENT_INSTANCE,
	DOM_TYPE_SVG_ELEMENT_INSTANCE_LIST,
	DOM_TYPE_SVG_ANIMATED_VALUE,
	DOM_TYPE_STATIC_NODE_LIST,
	DOM_TYPE_CONSOLE,
	DOM_TYPE_DEBUGGER,
	DOM_TYPE_TEXTRANGE,
	DOM_TYPE_XSLTPROCESSOR,
	DOM_TYPE_USERJSMAGICFUNCTION,
	DOM_TYPE_USERJSMAGICVARIABLE,
	DOM_TYPE_DOCUMENTSELECTION,
	DOM_TYPE_WINDOWSELECTION,
	DOM_TYPE_FORM_CONTROL_FORMS_COLLECTION,
	DOM_TYPE_WEBFEEDS,
	DOM_TYPE_FEEDLIST,
	DOM_TYPE_FEED,
	DOM_TYPE_FEEDENTRYLIST,
	DOM_TYPE_FEEDENTRY,
	DOM_TYPE_FEEDCONTENT,
	DOM_TYPE_FEEDREADERLIST,
	DOM_TYPE_FEEDREADER,
	DOM_TYPE_WIDGET,
	DOM_TYPE_WIDGETCOLLECTION,
	DOM_TYPE_WIDGETMANAGER,
	DOM_TYPE_WIDGETICON,
	DOM_TYPE_UPNP_DEVICE_DESCRIPTOR,
	DOM_TYPE_UPNP_SERVICE_DESCRIPTOR,
	DOM_TYPE_WEBSERVER,
	DOM_TYPE_WEBSERVER_CONNECTION,
	DOM_TYPE_WEBSERVER_CONNECTION_CLOSED_EVENT,
	DOM_TYPE_WEBSERVER_COOKIE,
	DOM_TYPE_WEBSERVER_REQUEST_EVENT,
	DOM_TYPE_WEBSERVER_REQUEST,
	DOM_TYPE_WEBSERVER_RESPONSE,
	DOM_TYPE_WEBSERVER_ARRAY,
	DOM_TYPE_WEBSERVER_AUTHENTICATION_REALM,
	DOM_TYPE_WEBSERVER_UPLOADED_FILE,
	DOM_TYPE_WEBSERVER_COLLECTION,
	DOM_TYPE_WEBSERVER_FILE,
	DOM_TYPE_WEBSERVER_SANDBOX,
	DOM_TYPE_WEBSERVER_SESSION,
	DOM_TYPE_WEBSERVER_BINARY_OBJECT,
	DOM_TYPE_WEBSERVER_SERVICE_DESCRIPTOR,
	DOM_TYPE_WINDOWCOMMANDER,
	DOM_TYPE_INSTALLEDWIDGETS,
	DOM_TYPE_INSTALLEDWIDGET,
	DOM_TYPE_WIDGETWINDOW,
	DOM_TYPE_DIALOG_EVENT,
	DOM_TYPE_AUTHENTICATION_EVENT,
	DOM_TYPE_CLIENTRECTLIST,
	DOM_TYPE_IO,
	DOM_TYPE_GADGETFILE,
	DOM_TYPE_FILESTREAM,
	DOM_TYPE_FILESYSTEM,
	DOM_TYPE_BYTEARRAY,
	DOM_TYPE_WORKERPOOL,
	DOM_TYPE_WORKERPOOL_WRAPPER,
	DOM_TYPE_WORKERPOOL_WRAPPER_CALLBACK,
	DOM_TYPE_GEOLOCATION,
	DOM_TYPE_POSITION,
	DOM_TYPE_COORDINATES,
	DOM_TYPE_POSITIONERROR,
	DOM_TYPE_TRANSITIONEVENT,
	DOM_TYPE_ANIMATIONEVENT,
	DOM_TYPE_APPLICATION_CACHE,
	DOM_TYPE_STORAGE,
	DOM_TYPE_STORAGEEVENT,
	DOM_TYPE_DATABASE,
	DOM_TYPE_SQL_TRANSACTION,
	DOM_TYPE_SQL_RESULTSET,
	DOM_TYPE_SQL_RESULTSETROWLIST,
	DOM_TYPE_SQL_ERROR,
	DOM_TYPE_WEBSOCKET,
	DOM_TYPE_CALLSTATE,
	DOM_TYPE_JIL_PIM,
	DOM_TYPE_JIL_ADDRESSBOOKITEM,
	DOM_TYPE_JIL_CALENDARITEM,
	DOM_TYPE_JIL_DEVICE,
	DOM_TYPE_JIL_DEVICEINFO,
	DOM_TYPE_JIL_DEVICESTATEINFO,
	DOM_TYPE_JIL_RADIOINFO,
	DOM_TYPE_JIL_DATANETWORKINFO,
	DOM_TYPE_JIL_POSITIONINFO,
	DOM_TYPE_JIL_MULTIMEDIA,
	DOM_TYPE_JIL_VIDEOPLAYER,
	DOM_TYPE_JIL_AUDIOPLAYER,
	DOM_TYPE_JIL_CAMERA,
	DOM_TYPE_JIL_TELEPHONY,
	DOM_TYPE_JIL_CALLRECORD,
	DOM_TYPE_JIL_ACCOUNTINFO,
	DOM_TYPE_JIL_MESSAGING,
	DOM_TYPE_JIL_MESSAGE,
	DOM_TYPE_JIL_MESSAGEFOLDERTYPES,
	DOM_TYPE_JIL_EMAILACCOUNT,
	DOM_TYPE_JIL_MESSAGETYPES,
	DOM_TYPE_JIL_MESSAGEQUANTITIES,
	DOM_TYPE_JIL_ATTACHMENT,
	DOM_TYPE_JIL_ATTACHMENT_ARRAY,
	DOM_TYPE_JIL_STRING_ARRAY,
	DOM_TYPE_JIL_ACCELEROMETERINFO,
	DOM_TYPE_JIL_WIDGETMANAGER,
	DOM_TYPE_JIL_CONFIG,
	DOM_TYPE_JIL_POWERINFO,
	DOM_TYPE_JIL_FILE,
	DOM_TYPE_JIL_WIDGET,
	DOM_TYPE_JIL_APPLICATIONTYPES,
	DOM_TYPE_JIL_CALL_RECORD_TYPES,
	DOM_TYPE_JIL_CALL_RECORD,
	DOM_TYPE_CLOSEEVENT,
	DOM_TYPE_WEBWORKERS_WORKER_OBJECT,
	DOM_TYPE_WEBWORKERS_WORKER_OBJECT_DEDICATED,
	DOM_TYPE_WEBWORKERS_WORKER_OBJECT_SHARED,
	DOM_TYPE_WEBWORKERS_WORKER,
	DOM_TYPE_WEBWORKERS_WORKER_DEDICATED,
	DOM_TYPE_WEBWORKERS_WORKER_SHARED,
	DOM_TYPE_MESSAGEEVENT,
	DOM_TYPE_MESSAGEPORT,
	DOM_TYPE_MESSAGECHANNEL,
	DOM_TYPE_OPERA_ACCOUNT_MANAGER,
	DOM_TYPE_UNITEDEVICEMANAGER,
	DOM_TYPE_EVENTSOURCE,
	DOM_TYPE_TOUCH,
	DOM_TYPE_TOUCHEVENT,
	DOM_TYPE_TOUCHLIST,
	DOM_TYPE_EXTENSION,
	DOM_TYPE_EXTENSION_BACKGROUND,
	DOM_TYPE_EXTENSION_CONTEXT,
	DOM_TYPE_EXTENSION_SPEEDDIAL_CONTEXT,
	DOM_TYPE_EXTENSION_CONTEXTS,
	DOM_TYPE_EXTENSION_PAGE_CONTEXT,
	DOM_TYPE_EXTENSION_RULELIST,
	DOM_TYPE_EXTENSION_RULEOPTIONS,
	DOM_TYPE_EXTENSION_SCOPE,
	DOM_TYPE_BROWSER_TAB,
	DOM_TYPE_BROWSER_TAB_MANAGER,
	DOM_TYPE_BROWSER_TAB_EVENT,
	DOM_TYPE_BROWSER_TAB_GROUP,
	DOM_TYPE_BROWSER_TAB_GROUP_MANAGER,
	DOM_TYPE_BROWSER_TAB_GROUP_EVENT,
	DOM_TYPE_BROWSER_WINDOW,
	DOM_TYPE_BROWSER_WINDOW_MANAGER,
	DOM_TYPE_BROWSER_WINDOW_EVENT,
	DOM_TYPE_EXTENSION_UIBADGE,
	DOM_TYPE_EXTENSION_UIITEM,
	DOM_TYPE_EXTENSION_UIITEM_EVENT,
	DOM_TYPE_EXTENSION_UIPOPUP,
	DOM_TYPE_EXTENSION_URLFILTER,
	DOM_TYPE_EXTENSION_URLFILTER_EVENT,
	DOM_TYPE_EXTENSION_MENUCONTEXT,
	DOM_TYPE_EXTENSION_ROOTMENUCONTEXT,
	DOM_TYPE_EXTENSION_MENUITEM,
	DOM_TYPE_EXTENSION_MENUCONTEXT_PROXY,
	DOM_TYPE_EXTENSION_MENUITEM_PROXY,
	DOM_TYPE_POPSTATEEVENT,
	DOM_TYPE_LOCALMEDIASTREAM,
	DOM_TYPE_HTML_PROPERTIES_COLLECTION,
	DOM_TYPE_PROPERTY_NODE_LIST_COLLECTION,
	DOM_TYPE_DEVICEORIENTATION_EVENT,
	DOM_TYPE_DEVICEMOTION_EVENT,
	DOM_TYPE_SEARCH_SUGGESTIONS_EVENT,
	DOM_TYPE_FORMDATA,
	DOM_TYPE_PAGEEVENT,
	DOM_TYPE_DATA_TRANSFER_ITEM,
	DOM_TYPE_DATA_TRANSFER_ITEMS,
	DOM_TYPE_DATA_TRANSFER,
	DOM_TYPE_DRAGEVENT,
	DOM_TYPE_CLIPBOARDEVENT,
	DOM_TYPE_TEXTEVENT,
	DOM_TYPE_HTML_PLUGINELEMENT,
	DOM_TYPE_LAST
};

/** These values correspond to the constants defined in the Node
    interface by DOM 2 Core.  Don't modify this enumeration unless
    you happen to know exactly what you are doing, code and tests
    depend on the actual value of these enumerators. */
enum DOM_NodeType
{
	NOT_A_NODE,
	ELEMENT_NODE,
	ATTRIBUTE_NODE,
	TEXT_NODE,
	CDATA_SECTION_NODE,
	ENTITY_REFERENCE_NODE,
	ENTITY_NODE,
	PROCESSING_INSTRUCTION_NODE,
	COMMENT_NODE,
	DOCUMENT_NODE,
	DOCUMENT_TYPE_NODE,
	DOCUMENT_FRAGMENT_NODE,
	NOTATION_NODE,
	XPATH_NAMESPACE_NODE,
	SVG_ELEMENTINSTANCE_NODE
};

#endif // DOM_TYPES_H
