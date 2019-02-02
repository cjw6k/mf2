--TEST--
mf2: mf-test-suite: v1/includes/object
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/object.html')->items);

?>
--EXPECT--
array(3) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-event"
    }
    ["properties"]=>
    array(3) {
      ["start"]=>
      array(1) {
        [0]=>
        object(DateTime)#3 (4) {
          ["value"]=>
          string(25) "2012-10-30T11:45:00-08:00"
          ["date"]=>
          string(26) "2012-10-30 11:45:00.000000"
          ["timezone_type"]=>
          int(1)
          ["timezone"]=>
          string(6) "-08:00"
        }
      }
      ["name"]=>
      array(1) {
        [0]=>
        string(16) "Build Conference"
      }
      ["location"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#4 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(3) {
            ["locality"]=>
            array(1) {
              [0]=>
              string(7) "Redmond"
            }
            ["region"]=>
            array(1) {
              [0]=>
              string(10) "Washington"
            }
            ["country-name"]=>
            array(1) {
              [0]=>
              string(3) "USA"
            }
          }
          ["value"]=>
          string(44) "Redmond, 
        Washington, 
        USA"
        }
      }
    }
  }
  [1]=>
  object(MF2Microformat)#5 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-event"
    }
    ["properties"]=>
    array(3) {
      ["start"]=>
      array(1) {
        [0]=>
        object(DateTime)#6 (4) {
          ["value"]=>
          string(25) "2012-10-31T11:15:00-08:00"
          ["date"]=>
          string(26) "2012-10-31 11:15:00.000000"
          ["timezone_type"]=>
          int(1)
          ["timezone"]=>
          string(6) "-08:00"
        }
      }
      ["name"]=>
      array(1) {
        [0]=>
        string(16) "Build Conference"
      }
      ["location"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#7 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(3) {
            ["locality"]=>
            array(1) {
              [0]=>
              string(7) "Redmond"
            }
            ["region"]=>
            array(1) {
              [0]=>
              string(10) "Washington"
            }
            ["country-name"]=>
            array(1) {
              [0]=>
              string(3) "USA"
            }
          }
          ["value"]=>
          string(44) "Redmond, 
        Washington, 
        USA"
        }
      }
    }
  }
  [2]=>
  object(MF2Microformat)#8 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(5) "h-adr"
    }
    ["properties"]=>
    array(3) {
      ["locality"]=>
      array(1) {
        [0]=>
        string(7) "Redmond"
      }
      ["region"]=>
      array(1) {
        [0]=>
        string(10) "Washington"
      }
      ["country-name"]=>
      array(1) {
        [0]=>
        string(3) "USA"
      }
    }
  }
}
