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

#ifndef PHP_MF2_H
#define PHP_MF2_H

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_MF2_VERSION "0.1.0"

extern zend_module_entry php_mf2_module_entry;
#define phpext_mf2_ptr &php_mf2_module_entry

/* MF2Parse() options */
#define PHP_MF2_NOWARNING       0x01 // 1 << 1
#define PHP_MF2_NONOTICE        0x02 // 1 << 2

/* LibXML HTML parsing context options */
#define PHP_MF2_PARSE_RECOVER   0x04 // 1 << 3
#define PHP_MF2_PARSE_NOERROR   0x08 // 1 << 4
#define PHP_MF2_PARSE_NOWARNING 0x10 // 1 << 5

/* Combined convenience option, it's the default if no options are specified */
#define PHP_MF2_PARSE_HAPPY     0x1F // PHP_MF2_NOWARNING | PHP_MF2_NONOTICE | PHP_MF2_PARSE_RECOVER | PHP_MF2_PARSE_NOERROR | PHP_MF2_PARSE_NOWARNING

#endif /* PHP_MF2 */