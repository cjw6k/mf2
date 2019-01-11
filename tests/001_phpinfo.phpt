--TEST--
mf2: phpinfo() includes Microformats2 status
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

ob_start();
phpinfo();
$info = ob_get_clean();

var_dump(false !== strpos($info, 'Microformats2 support => enabled'));

?>
--EXPECT--
bool(true)
