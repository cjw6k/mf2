--TEST--
mf2: mf-test-suite: v2/h-card/p-property
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/p-property.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(6) {
      ["name"]=>
      array(1) {
        [0]=>
        string(7) "JohnDoe"
      }
      ["given-name"]=>
      array(1) {
        [0]=>
        string(4) "John"
      }
      ["additional-name"]=>
      array(1) {
        [0]=>
        string(5) "Peter"
      }
      ["family-name"]=>
      array(1) {
        [0]=>
        string(3) "Doe"
      }
      ["honorific-suffix"]=>
      array(4) {
        [0]=>
        string(3) "MSc"
        [1]=>
        string(0) ""
        [2]=>
        string(0) ""
        [3]=>
        string(3) "PHD"
      }
      ["org"]=>
      array(2) {
        [0]=>
        string(6) "Madgex"
        [1]=>
        string(7) "Mozilla"
      }
    }
  }
}