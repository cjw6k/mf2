--TEST--
mf2: MF2Parse accepts MF2_PARSE_NOWARNING option
--SKIPIF--
<?php if (!extension_loaded("mf2")) { print "skip"; } else print "skip unable to confirm via test" ?> 
--FILE--
<?php

$html = '';

echo "LibXML's HTML parsing context emits warnings, when ... (TODO: when?)";
$parse = mf2_parse($html, null, 0);
var_dump($parse instanceof MF2Parse);

echo "Passing MF2_PARSE_NOWARNING mutes those\n";
$parse = mf2_parse($html, null, MF2_PARSE_RECOVER | MF2_PARSE_NOWARNING);
var_dump($parse instanceof MF2Parse);

?>
--EXPECT--
LibXML's HTML parsing context emits warnings, when ... (TODO: )
bool(true)
Passing MF2_PARSE_NOWARNING mutes those
bool(true)