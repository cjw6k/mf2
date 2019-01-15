--TEST--
mf2: MF2Parse class exists
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(class_exists('MF2Parse'));

?>
--EXPECT--
bool(true)
