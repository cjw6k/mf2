--TEST--
mf2: MF2Parse rel-urls may be accessed as $parse->rel_urls, or $parse->relurls, or given $key = 'rel-urls' as $parse->$key
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$key = 'rel-urls';

// Properties are not there until after parsing
var_dump(property_exists('MF2Parse', 'relurls'));
var_dump(property_exists('MF2Parse', 'rel_urls'));
var_dump(property_exists('MF2Parse', 'rel-urls'));

$parse = new MF2Parse('');

var_dump(property_exists($parse, 'relurls'));
var_dump(property_exists($parse, 'rel_urls'));
var_dump(property_exists($parse, 'rel-urls'));

var_dump(isset($parse->relurls));
var_dump(isset($parse->rel_urls));
var_dump(isset($parse->$key));

var_dump(empty($parse->relurls));
var_dump(empty($parse->rel_urls));
var_dump(empty($parse->$key));

?>
--EXPECT--
bool(false)
bool(false)
bool(false)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
