--TEST--
mf2: MF2Parse is not cloneable
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = new MF2Parse('<html></html>');
try{
	$parse2 = clone $parse;
} catch (Error $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

?>
--EXPECT--
Error: Trying to clone an uncloneable object of class Mf2Parse
