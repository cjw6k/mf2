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

#include "mf2.h"
#include "mf2parse.h"

#include "user_mf2parse.h"

/**
 * @since 0.1.0
 */
PHP_METHOD( MF2Parse, __construct )
{
	char *data, *base_url = NULL;
	int num_args = ZEND_NUM_ARGS();
	size_t data_length, base_url_length;
	zend_long options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;
	zend_bool data_is_uri = 0, options_is_null = 0, data_is_uri_is_null = 0;
	zval *this;

	if ( num_args == 0 ) {
		zend_throw_exception( zend_ce_exception, "Data parameter is required", 0 );
		return;
	}

	ZEND_PARSE_PARAMETERS_START( 1, 4 )
		Z_PARAM_STRING_EX( data, data_length, 0, 0 )
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_EX( base_url, base_url_length, 1, 0 )
		Z_PARAM_BOOL_EX( data_is_uri, data_is_uri_is_null, 1, 0 )
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

	if ( options_is_null == 1 ) {
		mf2parse->options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;
	} else {
		mf2parse->options = options;
	}

	mf2parse_new( this, data, data_length, data_is_uri );
}

#if HAVE_JSON
/**
 * @since 0.1.0
 */
PHP_METHOD( MF2Parse, jsonSerialize )
{
	php_mf2parse_object *mf2parse;
	zend_string *zs_relurls;
	zval *this, items, rels, rel_urls;

	this = getThis();
	mf2parse = Z_MF2PARSEOBJ_P( this );

	ZVAL_ARR( &items, mf2parse->items );
	ZVAL_ARR( &rels, mf2parse->rels );
	ZVAL_ARR( &rel_urls, mf2parse->rel_urls );

	zval_copy_ctor( &items );
	zval_copy_ctor( &rels );
	zval_copy_ctor( &rel_urls );

	// Microformats2 parsing spec calls for empty hashes
	convert_to_object( &rels );
	convert_to_object( &rel_urls );

	array_init( return_value );
	zend_hash_add_new( Z_ARRVAL_P( return_value ), MF2_STR( str_items ), &items );
	zend_hash_add_new( Z_ARRVAL_P( return_value ), MF2_STR( str_rels ), &rels );

	// Microformats2 parsing spec calls for dashed key: rel-urls
	zs_relurls = zend_string_init( "rel-urls", 8, 0 ); // TODO: internalize this zend_string
	zend_hash_add_new( Z_ARRVAL_P( return_value ), zs_relurls, &rel_urls );
	zend_string_release( zs_relurls );
}

#endif /* HAVE_JSON */

#endif /* HAVE_MF2 */
