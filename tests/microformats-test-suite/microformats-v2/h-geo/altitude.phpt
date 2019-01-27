--TEST--
mf2: mf-test-suite: v2/h-geo/altitude
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/altitude.html')->items);

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
    array(4) {
      ["name"]=>
      array(1) {
        [0]=>
        string(11) "Pen-y-ghent"
      }
      ["latitude"]=>
      array(1) {
        [0]=>
        string(9) "54.155278"
      }
      ["longitude"]=>
      array(1) {
        [0]=>
        string(9) "-2.249722"
      }
      ["altitude"]=>
      array(1) {
        [0]=>
        string(3) "694"
      }
    }
  }
}
