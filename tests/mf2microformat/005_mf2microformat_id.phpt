--TEST--
mf2: MF2Microformat ids are stored in the optional id member
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = mf2_parse('<div class="h-card" id="test"></div>');
echo $parse->items[0]->id, "\n";

?>
--EXPECT--
test
