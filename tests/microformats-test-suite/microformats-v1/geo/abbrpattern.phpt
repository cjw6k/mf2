--TEST--
mf2: mf-test-suite: v1/geo/abbrpattern
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/abbrpattern.html')->items);

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
        string(9) "37.408183"
      }
      ["longitude"]=>
      array(1) {
        [0]=>
        string(10) "-122.13855"
      }
    }
  }
}
