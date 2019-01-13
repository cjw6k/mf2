--TEST--
mf2: mf-test-suite: v2/rel/nofollow
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/nofollow.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(1) {
    ["nofollow"]=>
    array(1) {
      [0]=>
      string(52) "http://microformats.org/wiki/microformats:copyrights"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://microformats.org/wiki/microformats:copyrights"]=>
    array(2) {
      ["text"]=>
      string(10) "Copyrights"
      ["rels"]=>
      array(1) {
        [0]=>
        string(8) "nofollow"
      }
    }
  }
}