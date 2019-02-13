--TEST--
mf2: mf-test-suite: v1/includes/heventitemref
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/heventitemref.html')->items);

?>
--EXPECT--
array(2) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-event"
    }
    ["properties"]=>
    array(3) {
      ["location"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(2) {
            ["extended-address"]=>
            array(2) {
              [0]=>
              string(7) "Room 10"
              [1]=>
              string(14) "Moscone Center"
            }
            ["locality"]=>
            array(1) {
              [0]=>
              string(13) "San Francisco"
            }
          }
          ["value"]=>
          string(56) "Room 10
    
    Moscone Center,   
    San Francisco"
        }
      }
      ["start"]=>
      array(1) {
        [0]=>
        string(24) "2012-06-27T15:45:00-0800"
      }
      ["end"]=>
      array(1) {
        [0]=>
        string(24) "2012-06-27T16:45:00-0800"
      }
    }
  }
  [1]=>
  object(MF2Microformat)#4 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-event"
    }
    ["properties"]=>
    array(3) {
      ["location"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#5 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(2) {
            ["extended-address"]=>
            array(2) {
              [0]=>
              string(7) "Room 11"
              [1]=>
              string(14) "Moscone Center"
            }
            ["locality"]=>
            array(1) {
              [0]=>
              string(13) "San Francisco"
            }
          }
          ["value"]=>
          string(56) "Room 11
    
    Moscone Center,   
    San Francisco"
        }
      }
      ["start"]=>
      array(1) {
        [0]=>
        string(24) "2012-06-27T15:45:00-0800"
      }
      ["end"]=>
      array(1) {
        [0]=>
        string(24) "2012-06-27T16:45:00-0800"
      }
    }
  }
}
