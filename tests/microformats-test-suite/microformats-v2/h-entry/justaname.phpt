--TEST--
mf2: mf-test-suite: v2/h-entry/justaname
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
      string(7) "h-entry"
    }
    ["properties"]=>
    array(1) {
      ["name"]=>
      array(1) {
        [0]=>
        string(21) "microformats.org at 7"
      }
    }
  }
}
