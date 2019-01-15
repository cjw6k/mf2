--TEST--
mf2: MF2Parse properties have the normal access pattern
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

// Properties are not there until after parsing
var_dump(property_exists('MF2Parse', 'items'));
var_dump(property_exists('MF2Parse', 'rels'));
var_dump(property_exists('MF2Parse', 'rel_urls'));

$parse = new MF2Parse('');

var_dump(property_exists($parse, 'items'));
var_dump(property_exists($parse, 'rels'));
var_dump(property_exists($parse, 'rel_urls'));

var_dump(isset($parse->items));
var_dump(isset($parse->rels));
var_dump(isset($parse->rel_urls));

var_dump(empty($parse->items));
var_dump(empty($parse->rels));
var_dump(empty($parse->rel_urls));

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
