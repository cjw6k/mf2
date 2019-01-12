--TEST--
mf2: parse data from a string and return an MF2Parse instance
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(function_exists('mf2_parse'));
var_dump(mf2_parse('<html></html>') instanceof MF2Parse);

// Specifying base URL
var_dump(mf2_parse('<html></html>', 'http://example.com/') instanceof MF2Parse);

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
