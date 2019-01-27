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

#define MF2_REGEX_ROOTS      "/(?<=\\s|^)h-((?:[a-z0-9]+-)?[a-z]+(?:-[a-z]+)*)(?=\\s|$)/"
#define MF2_REGEX_PROPERTIES "/(?<=\\s|^)(e|u|dt|p)-((?:[a-z0-9]+-)?[a-z]+(?:-[a-z]+)*)(?=\\s|$)/"
#define MF2_REGEX_DT_ISO8601 "/^((?:[0-9]{4})-(?:1[0-2]|0[1-9])-(?:3[01]|0[1-9]|[12][0-9]))(?:T((?:2[0-3]|[01][0-9]):(?:[0-5][0-9]):(?:[0-5][0-9])(?:\\.[0-9]+)?)(Z|(?:[+-][01][0-9](?::?[0-5][0-9])?))?)?$/"
#define MF2_REGEX_DT_DAY "/^([0-9]{4}-(?:(?:00[1-9])|(?:[0-2][1-9][0-9])|(?:3[0-5][0-9])|(?:36[0-6])))$/"
#define MF2_REGEX_DT_TIME "/^((?:(?:0?[0-9])|(?:1[0-9])|2[0-3])(?:(?:(?:[aA]\\.?[mM]\\.?)|(?:[pP]\\.?[mM]\\.?))|(?::[0-5][0-9]))(?::[0-5][0-9])?(?:(?:[aA]\\.?[mM]\\.?)|(?:[pP]\\.?[mM]\\.?))?)(Z|(?:[+-][01][0-9](?::?[0-5][0-9])?))?$/"
#define MF2_REGEX_DT_TIMEZONE "/^(Z|(?:[+-][01][0-9](?::?[0-5][0-9])?))$/"

zend_bool mf2_in_array( zval *haystack, zval *needle );
int mf2_strcasecmp( const void *ida, const void *idb );
void mf2_trim_html_space_chars( zval *trimmed_string, char *string );
zend_bool mf2_is_relative_url( php_url *url_parts );

#endif /* MF2_H */
