--TEST--
mf2: extension exists and is loaded
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(extension_loaded("mf2"));

?>
--EXPECT--
bool(true)
