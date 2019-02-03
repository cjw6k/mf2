--TEST--
mf2: mf-test-suite: v1/includes/table
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/table.html')->items);

?>
--EXPECT--
array(2) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(11) "Chris Mills"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(21) "http://dev.opera.com/"
      }
      ["org"]=>
      array(1) {
        [0]=>
        string(5) "Opera"
      }
    }
  }
  [1]=>
  object(MF2Microformat)#3 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(12) "Erik Möller"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(21) "http://dev.opera.com/"
      }
      ["org"]=>
      array(1) {
        [0]=>
        string(5) "Opera"
      }
    }
  }
}
