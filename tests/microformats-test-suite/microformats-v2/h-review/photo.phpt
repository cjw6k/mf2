--TEST--
mf2: mf-test-suite: v2/h-review/photo
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/photo.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(8) "h-review"
    }
    ["properties"]=>
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(14) "Crepes on Cole"
      }
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(35) "http://example.com/images/photo.gif"
          ["alt"]=>
          string(14) "Crepes on Cole"
        }
      }
    }
  }
}
