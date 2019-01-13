--TEST--
mf2: mf-test-suite: v2/rel/varying-text-duplicate-rels
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/varying-text-duplicate-rels.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(2) {
    ["category"]=>
    array(1) {
      [0]=>
      string(29) "http://ma.tt/category/asides/"
    }
    ["tag"]=>
    array(1) {
      [0]=>
      string(29) "http://ma.tt/category/asides/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://ma.tt/category/asides/"]=>
    array(2) {
      ["text"]=>
      string(6) "Asides"
      ["rels"]=>
      array(2) {
        [0]=>
        string(8) "category"
        [1]=>
        string(3) "tag"
      }
    }
  }
}