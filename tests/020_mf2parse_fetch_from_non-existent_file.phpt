--TEST--
mf2: MF2Parse fetch and parse from a non-existent file
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = new MF2Parse(__DIR__ . '/file-that-does-not-exist-here', null, true);
var_dump($parse instanceof MF2Parse);
var_dump($parse);

?>
--EXPECTF--
Warning: MF2Parse::__construct(): I/O warning : failed to load external entity %s in %s on line %d
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