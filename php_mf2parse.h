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

#ifndef PHP_MF2PARSE_H
#define PHP_MF2PARSE_H

#include "ext/libxml/php_libxml.h"
#include "ext/pcre/php_pcre.h"
#include "ext/standard/url.h"

typedef struct _php_mf2parse_object {
	php_url *php_base_url;
	zval base_url;
	zend_ulong options;
	HashTable *items, *rels, *rel_urls, *properties;
	xmlDocPtr document;
	pcre_cache_entry *regex_roots;
	pcre_cache_entry *regex_backcompat_roots;
	pcre_cache_entry *regex_properties;
	pcre_cache_entry *regex_backcompat_adr_properties;
	pcre_cache_entry *regex_backcompat_geo_properties;
	pcre_cache_entry *regex_backcompat_hcalendar_properties;
	pcre_cache_entry *regex_backcompat_hcard_properties;
	pcre_cache_entry *regex_dt_iso8601;
	pcre_cache_entry *regex_dt_day;
	pcre_cache_entry *regex_dt_time;
	pcre_cache_entry *regex_dt_timezone;
	zval *context;
	zend_object zo;
} php_mf2parse_object;

extern zend_class_entry *php_mf2parse_ce;

PHP_MINIT_FUNCTION( mf2parse );

#endif /* PHP_MF2PARSE_H */