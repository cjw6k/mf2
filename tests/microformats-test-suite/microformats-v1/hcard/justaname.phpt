--TEST--
mf2: mf-test-suite: v1/hcard/justaname
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/justaname.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(1) {
    [0]=>
    object(MF2Microformat)#2 (2) {
      ["type"]=>
      array(1) {
        [0]=>
        string(6) "h-card"
      }
      ["properties"]=>
      array(0) {
      }
    }
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}