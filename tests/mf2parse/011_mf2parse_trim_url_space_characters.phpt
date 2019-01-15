--TEST--
mf2: space characters are trimmed from URLs found in attributes
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

// see HTML spec (https://www.w3.org/TR/html/infrastructure.html#space-characters)
$parse = new MF2Parse("<a rel='test' href=' \t\n\f\rhttp://example.com/ \t\n\f\r'>");
echo $parse->rels['test'][0], "\n";

?>
--EXPECT--
http://example.com/
