--TEST--
mf2: mf-test-suite: v2/rel/license
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/license.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(1) {
    ["license"]=>
    array(1) {
      [0]=>
      string(43) "http://creativecommons.org/licenses/by/2.5/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://creativecommons.org/licenses/by/2.5/"]=>
    array(2) {
      ["text"]=>
      string(9) "cc by 2.5"
      ["rels"]=>
      array(1) {
        [0]=>
        string(7) "license"
      }
    }
  }
}