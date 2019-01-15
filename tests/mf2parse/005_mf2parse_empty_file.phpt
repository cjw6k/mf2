--TEST--
mf2: MF2Parse parse an empty file
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = new MF2Parse(__DIR__ . '/../empty_file.html', null, true);
var_dump($parse instanceof MF2Parse);
var_dump($parse);

?>
--EXPECT--
bool(true)
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}
