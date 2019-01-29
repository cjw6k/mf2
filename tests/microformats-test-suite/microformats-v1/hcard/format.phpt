--TEST--
mf2: mf-test-suite: v1/hcard/format
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/format.html')->items);

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
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(18) "John 
        Doe"
      }
      ["given-name"]=>
      array(1) {
        [0]=>
        string(4) "John"
      }
    }
  }
}