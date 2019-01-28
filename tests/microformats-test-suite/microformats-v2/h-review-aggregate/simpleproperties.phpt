--TEST--
mf2: mf-test-suite: v2/h-review-aggregate/simpleproperties
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/simpleproperties.html')->items);

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
    array(6) {
      ["item"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-card"
          }
          ["properties"]=>
          array(5) {
            ["name"]=>
            array(1) {
              [0]=>
              string(19) "Mediterranean Wraps"
            }
            ["street-address"]=>
            array(1) {
              [0]=>
              string(20) "433 S California Ave"
            }
            ["locality"]=>
            array(1) {
              [0]=>
              string(9) "Palo Alto"
            }
            ["region"]=>
            array(1) {
              [0]=>
              string(2) "CA"
            }
            ["tel"]=>
            array(1) {
              [0]=>
              string(14) "(650) 321-8189"
            }
          }
          ["value"]=>
          string(19) "Mediterranean Wraps"
        }
      }
      ["summary"]=>
      array(1) {
        [0]=>
        string(110) "Customers flock to this small restaurant for their 
    tasty falafel and shawerma wraps and welcoming staff."
      }
      ["rating"]=>
      array(1) {
        [0]=>
        string(3) "9.2"
      }
      ["average"]=>
      array(1) {
        [0]=>
        string(3) "9.2"
      }
      ["best"]=>
      array(1) {
        [0]=>
        string(2) "10"
      }
      ["count"]=>
      array(1) {
        [0]=>
        string(2) "17"
      }
    }
  }
}
