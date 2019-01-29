--TEST--
mf2: mf-test-suite: v1/hcard/name
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/name.html')->items);

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
      ["honorific-prefix"]=>
      array(1) {
        [0]=>
        string(2) "Dr"
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
      array(2) {
        [0]=>
        string(3) "MSc"
        [1]=>
        string(3) "PHD"
      }
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(34) "http://example.com/images/logo.gif"
          ["alt"]=>
          string(3) "PHD"
        }
      }
    }
  }
}
