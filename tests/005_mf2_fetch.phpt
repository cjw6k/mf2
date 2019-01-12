--TEST--
mf2: fetch data from a URI and return an MF2Parse instance
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(function_exists('mf2_fetch'));
var_dump(mf2_fetch('http://microformats.org/') instanceof MF2Parse);
var_dump(mf2_fetch(__DIR__ . '/sample.html') instanceof MF2Parse);

// Specifying base URL
var_dump(mf2_fetch(__DIR__ . '/sample.html', 'http://example.com') instanceof MF2Parse);

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
