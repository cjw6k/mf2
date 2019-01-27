--TEST--
mf2: mf-test-suite: v2/h-geo/justaname
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/justaname.html')->items);

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
    array(1) {
      ["name"]=>
      array(1) {
        [0]=>
        string(18) "51.513458;-0.14812"
      }
    }
  }
}
