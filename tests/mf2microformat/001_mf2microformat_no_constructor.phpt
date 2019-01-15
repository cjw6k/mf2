--TEST--
mf2: MF2Microformat may not be directly instantiated
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

try{
	var_dump(new MF2Microformat());
} catch (Exception $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

?>
--EXPECT--
Exception: MF2Microformat cannot be directly instantiated
