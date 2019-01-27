--TEST--
mf2: mf-test-suite: v2/h-event/ampm
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/ampm.html')->items);

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
        string(25) "The 4th Microformat party"
      }
      ["start"]=>
      array(9) {
        [0]=>
        object(DateTime)#3 (4) {
          ["value"]=>
          string(21) "2009-06-26 07:00:00pm"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [1]=>
        object(DateTime)#4 (4) {
          ["value"]=>
          string(21) "2009-06-26 07:00:00am"
          ["date"]=>
          string(26) "2009-06-26 07:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [2]=>
        object(DateTime)#5 (4) {
          ["value"]=>
          string(18) "2009-06-26 07:00pm"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [3]=>
        object(DateTime)#6 (4) {
          ["value"]=>
          string(15) "2009-06-26 07pm"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [4]=>
        object(DateTime)#7 (4) {
          ["value"]=>
          string(14) "2009-06-26 7pm"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [5]=>
        object(DateTime)#8 (4) {
          ["value"]=>
          string(17) "2009-06-26 7:00pm"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [6]=>
        object(DateTime)#9 (4) {
          ["value"]=>
          string(20) "2009-06-26 07:00p.m."
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [7]=>
        object(DateTime)#10 (4) {
          ["value"]=>
          string(18) "2009-06-26 07:00PM"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
        [8]=>
        object(DateTime)#11 (4) {
          ["value"]=>
          string(17) "2009-06-26 7:00am"
          ["date"]=>
          string(26) "2009-06-26 07:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
      }
    }
  }
}
