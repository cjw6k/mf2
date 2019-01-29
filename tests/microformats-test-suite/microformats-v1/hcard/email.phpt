--TEST--
mf2: mf-test-suite: v1/hcard/email
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/email.html')->items);

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
        string(8) "John Doe"
      }
      ["email"]=>
      array(4) {
        [0]=>
        string(23) "mailto:john@example.com"
        [1]=>
        string(16) "john@example.com"
        [2]=>
        string(43) "mailto:john@example.com?subject=parser-test"
        [3]=>
        string(16) "john@example.com"
      }
    }
  }
}
