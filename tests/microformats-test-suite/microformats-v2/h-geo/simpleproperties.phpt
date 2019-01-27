--TEST--
mf2: mf-test-suite: v2/h-geo/simpleproperties
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/simpleproperties.html')->items);

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
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(21) "The Bricklayer's Arms"
      }
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