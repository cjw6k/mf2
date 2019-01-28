--TEST--
mf2: mf-test-suite: v2/h-review-aggregate/justahyperlink
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
          array(1) {
            ["name"]=>
            array(1) {
              [0]=>
              string(19) "Mediterranean Wraps"
            }
          }
          ["value"]=>
          string(19) "Mediterranean Wraps"
        }
      }
      ["summary"]=>
      array(1) {
        [0]=>
        string(114) "Customers flock to this small restaurant for their 
        tasty falafel and shawerma wraps and welcoming staff."
      }
      ["rating"]=>
      array(1) {
        [0]=>
        string(3) "4.5"
      }
    }
  }
}
