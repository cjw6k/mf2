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

#include "php_mf2parse.h"

/**
 * @since 0.1.0
 */
PHP_FUNCTION(mf2_fetch)
{
	char *uri, *base_url = NULL;
	int num_args = ZEND_NUM_ARGS();
	size_t uri_length, base_url_length;
	zend_long options = 0;
	zend_bool options_is_null;

	if ( num_args == 0 ) {
		zend_throw_exception( zend_ce_exception, "URI parameter is required", 0 );
		return;
	}

	ZEND_PARSE_PARAMETERS_START( 1, 3 )
		Z_PARAM_STRING_EX( uri, uri_length, 0, 0 )
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_EX( base_url, base_url_length, 1, 0 )
		Z_PARAM_LONG_EX( options, options_is_null, 1, 0 )
	ZEND_PARSE_PARAMETERS_END();

	if ( ZEND_SIZE_T_INT_OVFL( uri_length ) ) {
		zend_throw_exception( zend_ce_exception, "URI is too long", 0 );
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

	object_init_ex(return_value, php_mf2parse_ce);
}

/**
 * @since 0.1.0
 */
PHP_FUNCTION(mf2_parse)
{
	char *data, *base_url = NULL;
	int num_args = ZEND_NUM_ARGS();
	size_t data_length, base_url_length;
	zend_long options = 0;
	zend_bool options_is_null;

	if ( num_args == 0 ) {
		zend_throw_exception( zend_ce_exception, "Data parameter is required", 0 );
		return;
	}

	ZEND_PARSE_PARAMETERS_START( 1, 3 )
		Z_PARAM_STRING_EX( data, data_length, 0, 0 )
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_EX( base_url, base_url_length, 1, 0 )
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

	object_init_ex(return_value, php_mf2parse_ce);	
}

#endif /* HAVE_MF2 */