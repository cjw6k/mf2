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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#if HAVE_MF2

#include "zend_exceptions.h"

/**
 * @since 0.1.0
 */
PHP_METHOD( MF2Microformat, __construct )
{
	zend_throw_exception( zend_ce_exception, "MF2Microformat cannot be directly instantiated", 0 );
}

#endif /* HAVE_MF2 */