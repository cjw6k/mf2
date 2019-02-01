--TEST--
mf2: mf-test-suite: v1/hreview/item
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/item.html')->items);

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
          array(3) {
            ["photo"]=>
            array(1) {
              [0]=>
              string(35) "http://example.com/images/photo.gif"
            }
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
        string(1) "5"
      }
    }
  }
}
