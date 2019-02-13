--TEST--
mf2: mf-test-suite: v1/hreview-aggregate/vevent
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/vevent.html')->items);

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
    array(5) {
      ["item"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(7) "h-event"
          }
          ["properties"]=>
          array(3) {
            ["name"]=>
            array(1) {
              [0]=>
              string(11) "Fullfrontal"
            }
            ["description"]=>
            array(1) {
              [0]=>
              string(48) "A one day JavaScript Conference held in Brighton"
            }
            ["start"]=>
            array(1) {
              [0]=>
              string(10) "2012-11-09"
            }
          }
          ["value"]=>
          string(11) "Fullfrontal"
        }
      }
      ["rating"]=>
      array(1) {
        [0]=>
        string(3) "9.9"
      }
      ["average"]=>
      array(1) {
        [0]=>
        string(3) "9.9"
      }
      ["best"]=>
      array(1) {
        [0]=>
        string(2) "10"
      }
      ["count"]=>
      array(1) {
        [0]=>
        string(2) "62"
      }
    }
  }
}
