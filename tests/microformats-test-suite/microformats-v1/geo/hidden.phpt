--TEST--
mf2: mf-test-suite: v1/geo/hidden
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/hidden.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(5) "h-geo"
    }
    ["properties"]=>
    array(2) {
      ["latitude"]=>
      array(1) {
        [0]=>
        string(9) "51.513458"
      }
      ["longitude"]=>
      array(1) {
        [0]=>
        string(8) "-0.14812"
      }
    }
  }
}
