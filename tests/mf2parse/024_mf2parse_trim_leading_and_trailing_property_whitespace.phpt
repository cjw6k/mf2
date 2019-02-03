--TEST--
mf2: MF2Microformat trims leading and trailing whitespace from properties
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = mf2_parse('<div class="h-card"><p class="p-name"> CJWillcock </p></div>');
var_dump($parse->items[0]->properties['name'][0]);

// Any leading or trailing space characters are trimmed
// see HTML spec (https://www.w3.org/TR/html/infrastructure.html#space-characters)
$parse = mf2_parse("<div class='h-card'><p class='p-name'> \r\t\f\n  Christopher    \f\n\r\t\f\n  </p></div>");
var_dump($parse->items[0]->properties['name'][0]);

?>
--EXPECT--
string(10) "CJWillcock"
string(11) "Christopher"
