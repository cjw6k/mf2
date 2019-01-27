--TEST--
mf2: mf-test-suite: v2/h-event/dt-property
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/dt-property.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-event"
    }
    ["properties"]=>
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(9) "The party"
      }
      ["start"]=>
      array(8) {
        [0]=>
        object(DateTime)#3 (4) {
          ["value"]=>
          string(10) "2013-03-14"
          ["date"]=>
          string(26) "2013-03-14 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [1]=>
        object(DateTime)#4 (4) {
          ["value"]=>
          string(21) "2013-06-25 07:00:00am"
          ["date"]=>
          string(26) "2013-06-25 07:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [2]=>
        object(DateTime)#5 (4) {
          ["value"]=>
          string(10) "2013-06-26"
          ["date"]=>
          string(26) "2013-06-26 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [3]=>
        object(DateTime)#6 (4) {
          ["value"]=>
          string(10) "2013-06-27"
          ["date"]=>
          string(26) "2013-06-27 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [4]=>
        object(DateTime)#7 (4) {
          ["value"]=>
          string(10) "2013-06-28"
          ["date"]=>
          string(26) "2013-06-28 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [5]=>
        object(DateTime)#8 (4) {
          ["value"]=>
          string(10) "2013-06-29"
          ["date"]=>
          string(26) "2013-06-29 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [6]=>
        object(DateTime)#9 (4) {
          ["value"]=>
          string(10) "2013-07-01"
          ["date"]=>
          string(26) "2013-07-01 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [7]=>
        object(DateTime)#10 (4) {
          ["value"]=>
          string(10) "2013-07-02"
          ["date"]=>
          string(26) "2013-07-02 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
      }
    }
  }
}
