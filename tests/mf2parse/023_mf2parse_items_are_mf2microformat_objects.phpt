--TEST--
mf2: MF2Parse parse a microformat and return an MF2Microformat object in items
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_parse('<div class="h-card"></div>')->items[0] instanceof MF2Microformat);

?>
--EXPECT--
bool(true)