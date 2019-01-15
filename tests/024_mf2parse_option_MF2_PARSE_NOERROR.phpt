--TEST--
mf2: MF2Parse accepts MF2_PARSE_NOERROR option
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

echo "LibXML's HTML parsing context emits errors, labelled as warnings (!), about post HTML4 tags";
$parse = mf2_parse('<aside></aside>', null, 0);
var_dump($parse instanceof MF2Parse);

echo "Passing MF2_PARSE_NOERROR mutes those\n";
$parse = mf2_parse('<aside></aside>', null, MF2_PARSE_NOERROR);
var_dump($parse instanceof MF2Parse);

?>
--EXPECTF--
LibXML's HTML parsing context emits errors, labelled as warnings (!), about post HTML4 tags
Warning: mf2_parse(): HTML parser error : Tag aside invalid in %s on line %d

Warning: mf2_parse(): <aside></aside> in %s on line %d

Warning: mf2_parse():       ^ in %s on line %d
bool(true)
Passing MF2_PARSE_NOERROR mutes those
bool(true)