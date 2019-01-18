--TEST--
mf2: MF2Microformat vocabularies are stored in the type member
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = mf2_parse('<div class="h-card"></div>');

foreach($parse->items as $microformat){
	foreach($microformat->type as $type){
		echo "$type\n";
	}
}

// In alphabetical order
$parse = mf2_parse('<div class="h-card h-adr"></div>');

foreach($parse->items as $microformat){
	foreach($microformat->type as $type){
		echo "$type\n";
	}
}

?>
--EXPECT--
h-card
h-adr
h-card
