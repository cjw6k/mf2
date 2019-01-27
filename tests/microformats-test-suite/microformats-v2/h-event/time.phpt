--TEST--
mf2: mf-test-suite: v2/h-event/time
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/time.html')->items);

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
    array(3) {
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
          string(25) "2009-06-26 19:00:00-08:00"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(1)
          ["timezone"]=>
          string(6) "-08:00"
        }
        [1]=>
        object(DateTime)#4 (4) {
          ["value"]=>
          string(24) "2009-06-26 19:00:00-0800"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(1)
          ["timezone"]=>
          string(6) "-08:00"
        }
        [2]=>
        object(DateTime)#5 (4) {
          ["value"]=>
          string(24) "2009-06-26 19:00:00+0800"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(1)
          ["timezone"]=>
          string(6) "+08:00"
        }
        [3]=>
        object(DateTime)#6 (4) {
          ["value"]=>
          string(20) "2009-06-26 19:00:00Z"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(2)
          ["timezone"]=>
          string(1) "Z"
        }
        [4]=>
        object(DateTime)#7 (4) {
          ["value"]=>
          string(19) "2009-06-26 19:00:00"
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
          string(22) "2009-06-26 19:00-08:00"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(1)
          ["timezone"]=>
          string(6) "-08:00"
        }
        [6]=>
        object(DateTime)#9 (4) {
          ["value"]=>
          string(22) "2009-06-26 19:00+08:00"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(1)
          ["timezone"]=>
          string(6) "+08:00"
        }
        [7]=>
        object(DateTime)#10 (4) {
          ["value"]=>
          string(17) "2009-06-26 19:00Z"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(2)
          ["timezone"]=>
          string(1) "Z"
        }
        [8]=>
        object(DateTime)#11 (4) {
          ["value"]=>
          string(16) "2009-06-26 19:00"
          ["date"]=>
          string(26) "2009-06-26 19:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
      }
      ["end"]=>
      array(2) {
        [0]=>
        string(8) "2013-034"
        [1]=>
        object(DateTime)#12 (4) {
          ["value"]=>
          string(16) "2013-06-27 15:34"
          ["date"]=>
          string(26) "2013-06-27 15:34:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
      }
    }
  }
}
