--TEST--
mf2: mf-test-suite: v2/h-product/justahyperlink
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
      string(9) "h-product"
    }
    ["properties"]=>
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(12) "Raspberry Pi"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(27) "http://www.raspberrypi.org/"
      }
    }
  }
}
