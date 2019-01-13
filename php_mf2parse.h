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

#include "ext/standard/url.h"

typedef struct _php_mf2parse_object {
	php_url *php_base_url;
	zval base_url;
	HashTable *items, *rels, *rel_urls, *properties;
	zend_object zo;
} php_mf2parse_object;

extern zend_class_entry *php_mf2parse_ce;

PHP_MINIT_FUNCTION( mf2parse );

#endif /* PHP_MF2PARSE_H */