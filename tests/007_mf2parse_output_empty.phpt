--TEST--
mf2: MF2Parse empty parse representation
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(new MF2Parse('<html></html>'));

?>
--EXPECT--
object(Mf2Parse)#1 (3) {
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
