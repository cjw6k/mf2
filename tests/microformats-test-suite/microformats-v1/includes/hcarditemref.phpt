--TEST--
mf2: mf-test-suite: v1/includes/hcarditemref
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/hcarditemref.html')->items);

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
        string(7) "Mozilla"
      }
      ["adr"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (4) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(6) {
            ["street-address"]=>
            array(1) {
              [0]=>
              string(11) "665 3rd St."
            }
            ["extended-address"]=>
            array(1) {
              [0]=>
              string(9) "Suite 207"
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
              string(5) "94107"
            }
            ["country-name"]=>
            array(1) {
              [0]=>
              string(6) "U.S.A."
            }
          }
          ["id"]=>
          string(11) "mozilla-adr"
          ["value"]=>
          string(87) "665 3rd St.  
    Suite 207  
    San Francisco,  
    CA  
    94107  
    U.S.A."
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
        string(7) "Mozilla"
      }
      ["adr"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#5 (4) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-adr"
          }
          ["properties"]=>
          array(6) {
            ["street-address"]=>
            array(1) {
              [0]=>
              string(11) "665 3rd St."
            }
            ["extended-address"]=>
            array(1) {
              [0]=>
              string(9) "Suite 207"
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
              string(5) "94107"
            }
            ["country-name"]=>
            array(1) {
              [0]=>
              string(6) "U.S.A."
            }
          }
          ["id"]=>
          string(11) "mozilla-adr"
          ["value"]=>
          string(87) "665 3rd St.  
    Suite 207  
    San Francisco,  
    CA  
    94107  
    U.S.A."
        }
      }
    }
  }
  [2]=>
  object(MF2Microformat)#6 (3) {
    ["type"]=>
    array(1) {
      [0]=>
      string(5) "h-adr"
    }
    ["properties"]=>
    array(6) {
      ["street-address"]=>
      array(1) {
        [0]=>
        string(11) "665 3rd St."
      }
      ["extended-address"]=>
      array(1) {
        [0]=>
        string(9) "Suite 207"
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
        string(5) "94107"
      }
      ["country-name"]=>
      array(1) {
        [0]=>
        string(6) "U.S.A."
      }
    }
    ["id"]=>
    string(11) "mozilla-adr"
  }
}
