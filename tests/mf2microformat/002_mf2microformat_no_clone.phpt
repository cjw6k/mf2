--TEST--
mf2: MF2Microformat is not cloneable
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = new MF2Parse('<div class="h-card"></div>');
var_dump($parse->items[0] instanceof MF2Microformat);

try{
	$microformat = clone $parse->items[0];
} catch (Error $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

?>
--EXPECT--
bool(true)
Error: Trying to clone an uncloneable object of class MF2Microformat
