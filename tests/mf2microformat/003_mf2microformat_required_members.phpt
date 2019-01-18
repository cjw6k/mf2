--TEST--
mf2: MF2Microformat has required type and property members
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

// see http://microformats.org/wiki/microformats2-json

$parse = mf2_parse('<div class="h-card"></div>');

$microformat = $parse->items[0];

var_dump(isset($microformat->type));
var_dump(isset($microformat->properties));


?>
--EXPECT--
bool(true)
bool(true)
