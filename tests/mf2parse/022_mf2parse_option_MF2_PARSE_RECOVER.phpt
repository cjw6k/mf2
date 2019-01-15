--TEST--
mf2: MF2Parse accepts MF2_PARSE_RECOVER option
--SKIPIF--
<?php if (!extension_loaded("mf2")) { print "skip"; } else print "skip unable to confirm via test"; ?> 
--FILE--
<?php

$html = '';

echo "LibXML's HTML parsing context halts when a recoverable error occurs ... (TODO: does it?)";
$parse = mf2_parse($html, null, 0);
var_dump($parse instanceof MF2Parse);

echo "Passing MF2_PARSE_RECOVER allows parsing to continue, after recovery\n";
$parse = mf2_parse($html, null, MF2_PARSE_RECOVER);
var_dump($parse instanceof MF2Parse);

?>
--EXPECTF--
LibXML's HTML parsing context halts when a recoverable error occurs ... (TODO: )";
bool(true)
Passing MF2_PARSE_RECOVER allows parsing to continue, after recovery
bool(true)