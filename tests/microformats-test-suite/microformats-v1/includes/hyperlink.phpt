--TEST--
mf2: mf-test-suite: v1/includes/hyperlink
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/hyperlink.html')->items);

?>
--EXPECT--
array(3) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(2) {
      ["org"]=>
      array(1) {
        [0]=>
        string(7) "Twitter"
      }
      ["adr"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(4) {
            ["street-address"]=>
            array(1) {
              [0]=>
              string(14) "1355 Market St"
            }
            ["locality"]=>
            array(1) {
              [0]=>
              string(13) "San Francisco"
            }
            ["region"]=>
            array(1) {
              [0]=>
              string(2) "CA"
            }
            ["postal-code"]=>
            array(1) {
              [0]=>
              string(5) "94103"
            }
          }
          ["value"]=>
          string(67) "1355 Market St,
        San Francisco, 
        CA
        94103"
        }
      }
    }
  }
  [1]=>
  object(MF2Microformat)#4 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(2) {
      ["org"]=>
      array(1) {
        [0]=>
        string(7) "Twitter"
      }
      ["adr"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#5 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(4) {
            ["street-address"]=>
            array(1) {
              [0]=>
              string(14) "1355 Market St"
            }
            ["locality"]=>
            array(1) {
              [0]=>
              string(13) "San Francisco"
            }
            ["region"]=>
            array(1) {
              [0]=>
              string(2) "CA"
            }
            ["postal-code"]=>
            array(1) {
              [0]=>
              string(5) "94103"
            }
          }
          ["value"]=>
          string(67) "1355 Market St,
        San Francisco, 
        CA
        94103"
        }
      }
    }
  }
  [2]=>
  object(MF2Microformat)#6 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(5) "h-adr"
    }
    ["properties"]=>
    array(4) {
      ["street-address"]=>
      array(1) {
        [0]=>
        string(14) "1355 Market St"
      }
      ["locality"]=>
      array(1) {
        [0]=>
        string(13) "San Francisco"
      }
      ["region"]=>
      array(1) {
        [0]=>
        string(2) "CA"
      }
      ["postal-code"]=>
      array(1) {
        [0]=>
        string(5) "94103"
      }
    }
  }
}
