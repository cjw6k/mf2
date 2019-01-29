--TEST--
mf2: mf-test-suite: v1/hcalendar/attendees
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/attendees.html')->items);

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
    array(4) {
      ["name"]=>
      array(1) {
        [0]=>
        string(31) "CPJ Online Press Freedom Summit"
      }
      ["start"]=>
      array(1) {
        [0]=>
        object(DateTime)#3 (4) {
          ["value"]=>
          string(10) "2012-10-10"
          ["date"]=>
          string(26) "2012-10-10 00:00:00.000000"
          ["timezone_type"]=>
          int(3)
          ["timezone"]=>
          string(3) "UTC"
        }
      }
      ["location"]=>
      array(1) {
        [0]=>
        string(13) "San Francisco"
      }
      ["attendee"]=>
      array(4) {
        [0]=>
        object(MF2Microformat)#4 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-card"
          }
          ["properties"]=>
          array(1) {
            ["name"]=>
            array(1) {
              [0]=>
              string(12) "Brian Warner"
            }
          }
          ["value"]=>
          string(12) "Brian Warner"
        }
        [1]=>
        object(MF2Microformat)#5 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-card"
          }
          ["properties"]=>
          array(1) {
            ["name"]=>
            array(1) {
              [0]=>
              string(13) "Kyle Machulis"
            }
          }
          ["value"]=>
          string(13) "Kyle Machulis"
        }
        [2]=>
        object(MF2Microformat)#6 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-card"
          }
          ["properties"]=>
          array(1) {
            ["name"]=>
            array(1) {
              [0]=>
              string(13) "Tantek Çelik"
            }
          }
          ["value"]=>
          string(13) "Tantek Çelik"
        }
        [3]=>
        object(MF2Microformat)#7 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-card"
          }
          ["properties"]=>
          array(1) {
            ["name"]=>
            array(1) {
              [0]=>
              string(10) "Sid Sutter"
            }
          }
          ["value"]=>
          string(10) "Sid Sutter"
        }
      }
    }
  }
}
