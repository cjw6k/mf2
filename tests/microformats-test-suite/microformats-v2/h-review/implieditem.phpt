--TEST--
mf2: mf-test-suite: v2/h-review/implieditem
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/implieditem.html')->items);

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
      ["item"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-item"
          }
          ["properties"]=>
          array(2) {
            ["name"]=>
            array(1) {
              [0]=>
              string(14) "Crepes on Cole"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(30) "http://example.com/crepeoncole"
            }
          }
          ["value"]=>
          string(14) "Crepes on Cole"
        }
      }
      ["rating"]=>
      array(1) {
        [0]=>
        string(3) "4.7"
      }
    }
  }
}