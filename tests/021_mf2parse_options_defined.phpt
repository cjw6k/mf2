--TEST--
mf2: MF2Parse option constants are defined
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

/* MF2Parse() options */
var_dump(defined('MF2_NOWARNING'));
var_dump(defined('MF2_NONOTICE'));

/* LibXML HTML parsing context options */
var_dump(defined('MF2_PARSE_RECOVER'));
var_dump(defined('MF2_PARSE_NOERROR'));
var_dump(defined('MF2_PARSE_NOWARNING'));

/* MF2 combined convenience option */
var_dump(defined('MF2_PARSE_HAPPY'));

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
