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

#include "mf2parse.h"

#include "uphp_mf2parse.h"

/**
 * @since 0.1.0
 */
PHP_METHOD( MF2Parse, __construct )
{
	char *data, *base_url = NULL;
	int num_args = ZEND_NUM_ARGS();
	size_t data_length, base_url_length;
	zend_long options = 0;
	zend_bool data_is_url = 0, options_is_null, data_is_url_is_null;
	zval *this;

	if ( num_args == 0 ) {
		zend_throw_exception( zend_ce_exception, "Data parameter is required", 0 );
		return;
	}

	ZEND_PARSE_PARAMETERS_START( 1, 4 )
		Z_PARAM_STRING_EX( data, data_length, 0, 0 )
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_EX( base_url, base_url_length, 1, 0 )
		Z_PARAM_BOOL_EX( data_is_url, data_is_url_is_null, 1, 0 )
		Z_PARAM_LONG_EX( options, options_is_null, 1, 0 )
	ZEND_PARSE_PARAMETERS_END();

	if ( ZEND_SIZE_T_INT_OVFL( data_length ) ) {
		zend_throw_exception( zend_ce_exception, "Data is too long", 0 );
		return;
	}

	if ( base_url != NULL ) {
		if ( ZEND_SIZE_T_INT_OVFL( base_url_length ) ) {
			zend_throw_exception( zend_ce_exception, "Base URL is too long", 0 );
			return;
		}
	}

	if ( ZEND_LONG_EXCEEDS_INT( options ) ) {
		zend_throw_exception( zend_ce_exception, "Invalid options", 0 );
		return;
	}

	this = getThis();
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( this );	
	
	if ( base_url != NULL ) {
		mf2parse->php_base_url = php_url_parse_ex( base_url, base_url_length );
		if ( mf2parse->php_base_url == NULL ) {
			zend_throw_exception( zend_ce_exception, "Invalid base URL", 0 );
			return;
		}
		if ( mf2parse->php_base_url->scheme == NULL ) {
			zend_throw_exception( zend_ce_exception, "Base URL must be absolute", 0 );
			return;
		}
		ZVAL_STRINGL( &mf2parse->base_url, base_url, base_url_length );
	}	
}

#endif /* HAVE_MF2 */
