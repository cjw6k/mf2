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

#include "php_mf2microformat.h"

#include "mf2microformat.h"

/**
 * Convert a standard zend_object reference to an MF2Microformat object
 * reference.
 *
 * A standard zend_object is embedded within each MF2Microformat object. Many
 * API functions expect a zend_object parameter, making this function helpful
 * to reference the containing MF2Parse object of the standard zend_object
 * passed by the API.
 *
 * @link https://phpinternals.net/categories/zend_objects#offset
 *
 * @since 0.1.0
 *
 * @param  zend_object * object  The reference to a standard zend_object.
 *
 * @return  mf2microformat_object *  The containing MF2Microformat object.
 */
php_mf2microformat_object *mf2microformat_fetch_object( zend_object *object )
{
	return ( php_mf2microformat_object * ) ( ( char * ) ( object ) - XtOffsetOf( php_mf2microformat_object, zo ) );
}

#endif /* HAVE_MF2 */
