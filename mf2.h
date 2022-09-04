/*
  +----------------------------------------------------------------------+
  | mf2: extension for PHP                                                |
  +----------------------------------------------------------------------+
  | Copyright © 2019 Christopher James Willcock                          |
  +----------------------------------------------------------------------+
  | This source file is subject to the MIT License (MIT), that is        |
  | bundled with this package in the file LICENSE.md.                    |
  +----------------------------------------------------------------------+
  | Author: Christopher James Willcock <cjwillcock@ieee.org>             |
  +----------------------------------------------------------------------+
*/

#ifndef MF2_H
#define MF2_H

#include "mf2_str_defs.h"

#include "ext/standard/url.h"

typedef struct _mf2_str_globals {
#define X(str) zend_string *str_ ## str;
	MF2_STR_DEFS
#undef X
} mf2_str_globals;

mf2_str_globals str_globals_mf2;

#define MF2_STR(str) str_globals_mf2.str

#define MF2_REGEX_ROOTS \
	"/(?<=\\s|^)h-((?:[a-z0-9]+-)?[a-z]+(?:-[a-z]+)*)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_ROOTS \
	"/(?<=\\s|^)(adr|geo|vevent|vcard|hentry|hfeed|hnews|hproduct|hreview|hreview-aggregate|hresume)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_ROOTS_WITH_ITEM \
	"/(?<=\\s|^)(adr|geo|vevent|vcard|hentry|hfeed|hnews|hproduct|hreview|item|hreview-aggregate|hresume)(?=\\s|$)/"

#define MF2_REGEX_PROPERTIES \
	"/(?<=\\s|^)(e|u|dt|p)-((?:[a-z0-9]+-)?[a-z]+(?:-[a-z]+)*)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_ADR_PROPERTIES \
	"/(?<=\\s|^)(post-office-box|extended-address|street-address|locality|region|postal-code|country-name)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_GEO_PROPERTIES \
	"/(?<=\\s|^)(latitude|longitude)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HCALENDAR_PROPERTIES \
	"/(?<=\\s|^)(dtstart|summary|location|url|dtend|duration|rdate|rrule|category|description|uid|geo|latitude|longitude|attendee|partstat|role|contact|organizer|attach|status)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HCARD_PROPERTIES \
	"/(?<=\\s|^)(fn|family-name|given-name|additional-name|honorific-prefix|honorific-suffix|adr|post-office-box|extended-address|street-address|locality|region|postal-code|country-name|agent|bday|category|class|email|geo|latitude|longitude|key|label|logo|mailer|nickname|note|org|organization-name|organization-unit|photo|rev|role|sort-string|sound|tel|title|tz|uid|url)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HENTRY_PROPERTIES \
	"/(?<=\\s|^)(author|entry-title|entry-content|entry-summary|published|updated)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HFEED_PROPERTIES \
	"/(?<=\\s|^)(author|photo|url)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HNEWS_PROPERTIES \
	"/(?<=\\s|^)(entry|source-org|dateline|geo)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HPRODUCT_PROPERTIES \
	"/(?<=\\s|^)(fn|photo|description|url|price|review|category|brand)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HREVIEW_PROPERTIES \
	"/(?<=\\s|^)(summary|fn|photo|url|reviewer|dtreviewed|rating|best|worst|description|item)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HITEM_PROPERTIES \
	"/(?<=\\s|^)(photo|fn|url)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HREVIEW_AGGREGATE_PROPERTIES \
	"/(?<=\\s|^)(item|rating|average|best|count)(?=\\s|$)/"

#define MF2_REGEX_BACKCOMPAT_HRESUME_PROPERTIES \
	"/(?<=\\s|^)(summary|contact|education|experience|skill|affiliation|publications)(?=\\s|$)/"

#define MF2_REGEX_DT_ISO8601 \
	"/^((?:[0-9]{4})-(?:1[0-2]|0[1-9])-(?:3[01]|0[1-9]|[12][0-9]))(?:T((?:2[0-3]|[01][0-9]):(?:[0-5][0-9]):(?:[0-5][0-9])(?:\\.[0-9]+)?)(Z|(?:[+-][01][0-9](?::?[0-5][0-9])?))?)?$/"

#define MF2_REGEX_DT_DAY \
	"/^([0-9]{4}-(?:(?:00[1-9])|(?:[0-2][1-9][0-9])|(?:3[0-5][0-9])|(?:36[0-6])))$/"

#define MF2_REGEX_DT_TIME \
	"/^((?:(?:0?[0-9])|(?:1[0-9])|2[0-3])(?:(?:(?:[aA]\\.?[mM]\\.?)|(?:[pP]\\.?[mM]\\.?))|(?::[0-5][0-9]))(?::[0-5][0-9])?(?:(?:[aA]\\.?[mM]\\.?)|(?:[pP]\\.?[mM]\\.?))?)(Z|(?:[+-][01][0-9](?::?[0-5][0-9])?))?$/"

#define MF2_REGEX_DT_TIMEZONE \
	"/^(Z|(?:[+-][01][0-9](?::?[0-5][0-9])?))$/"


zend_bool mf2_in_array( zval *haystack, zval *needle );
zend_bool mf2_string_in_array( zval *haystack, zend_string *needle );
int mf2_strcasecmp( struct _Bucket *first, struct _Bucket *second );
void mf2_trim_html_space_chars( zval *trimmed_string, char *string );
zend_bool mf2_is_relative_url( php_url *url_parts );

#define MF2_ZVAL_XMLATTR( _zv_result, _xml_node, _zstr_attribute ) \
	MF2_ZVAL_XMLATTR_P( &_zv_result, _xml_node, _zstr_attribute )

#define MF2_ZVAL_XMLATTR_P( _zv_result, _xml_node, _zstr_attribute ) \
	xmlChar *_xml_attr = xmlGetProp( _xml_node, ( xmlChar * )ZSTR_VAL( _zstr_attribute ) ); \
	ZVAL_STRING( _zv_result, ( char * ) _xml_attr ); \
	xmlFree( _xml_attr );

#define MF2_TRY_ZVAL_XMLATTR( _zv_result, _xml_node, _zstr_attribute ) \
	if ( xmlHasProp( _xml_node, ( xmlChar * ) ZSTR_VAL( _zstr_attribute ) ) ) { \
		MF2_ZVAL_XMLATTR( _zv_result, _xml_node, _zstr_attribute ); \
	}

#define MF2_SMART_STR_XMLATTR( _smart_str, _xml_node, _zstr_attribute ) \
	xmlChar *_xml_attr = xmlGetProp( _xml_node, ( xmlChar * ) ZSTR_VAL( _zstr_attribute ) ); \
	smart_str_appends( &_smart_str, ( char * ) _xml_attr ); \
	xmlFree( _xml_attr );

#define MF2_TRY_SMART_STR_XMLATTR( _smart_str, _xml_node, _zstr_attribute ) \
	if ( xmlHasProp( _xml_node, ( xmlChar * ) ZSTR_VAL( _zstr_attribute ) ) ) { \
		MF2_SMART_STR_XMLATTR( _smart_str, _xml_node, _zstr_attribute ) \
	}

#define MF2_ZVAL_XMLBUFFER( _zv_result, _xml_node ) \
	xmlBufferPtr _xml_buffer; \
	_xml_buffer = xmlBufferCreate(); \
	xmlNodeBufGetContent( _xml_buffer, _xml_node ); \
	ZVAL_STRING( &_zv_result, ( char * ) _xml_buffer->content ); \
	xmlBufferFree( _xml_buffer );

#define MF2_TRY_ZVAL_XMLATTR_XMLBUFFER( _zv_result, _xml_node, _zstr_attribute ) \
	MF2_TRY_ZVAL_XMLATTR( _zv_result, _xml_node, _zstr_attribute ) else { \
		MF2_ZVAL_XMLBUFFER( _zv_result, _xml_node ); \
	}

#define MF2_SMART_STR_XMLBUFFER( _smart_str, _xml_node ) \
	xmlBufferPtr _xml_buffer; \
	_xml_buffer = xmlBufferCreate(); \
	xmlNodeBufGetContent( _xml_buffer, _xml_node ); \
	smart_str_appends( &_smart_str, ( char * ) _xml_buffer->content ); \
	xmlBufferFree( _xml_buffer );

#define MF2_TRY_SMART_STR_XMLATTR_XMLBUFFER( _smart_str, _xml_node, _zstr_attribute ) \
	MF2_TRY_SMART_STR_XMLATTR( _smart_str, _xml_node, _zstr_attribute ) else { \
		MF2_SMART_STR_XMLBUFFER( _smart_str, _xml_node ) \
	}

#endif /* MF2_H */
