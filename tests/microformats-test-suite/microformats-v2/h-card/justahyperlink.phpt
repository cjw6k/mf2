--TEST--
mf2: mf-test-suite: v2/h-card/justahyperlink
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/justahyperlink.html')->items);

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
        string(8) "Ben Ward"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(18) "http://benward.me/"
      }
    }
  }
}
