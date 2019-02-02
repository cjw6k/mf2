--TEST--
mf2: mf-test-suite: v1/hreview-aggregate/justahyperlink
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
      string(18) "h-review-aggregate"
    }
    ["properties"]=>
    array(3) {
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
              string(19) "Mediterranean Wraps"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(37) "http://example.com/mediterraneanwraps"
            }
          }
          ["value"]=>
          string(19) "Mediterranean Wraps"
        }
      }
      ["rating"]=>
      array(1) {
        [0]=>
        string(3) "4.5"
      }
      ["count"]=>
      array(1) {
        [0]=>
        string(1) "6"
      }
    }
  }
}
