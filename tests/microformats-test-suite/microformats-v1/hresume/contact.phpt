--TEST--
mf2: mf-test-suite: v1/hresume/contact
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/contact.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(8) "h-resume"
    }
    ["properties"]=>
    array(2) {
      ["contact"]=>
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
              string(15) "Tim Berners-Lee"
            }
            ["org"]=>
            array(1) {
              [0]=>
              string(3) "MIT"
            }
            ["adr"]=>
            array(1) {
              [0]=>
              object(MF2Microformat)#4 (3) {
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
                    string(16) "32 Vassar Street"
                  }
                  ["extended-address"]=>
                  array(1) {
                    [0]=>
                    string(12) "Room 32-G524"
                  }
                  ["locality"]=>
                  array(1) {
                    [0]=>
                    string(9) "Cambridge"
                  }
                  ["region"]=>
                  array(1) {
                    [0]=>
                    string(2) "MA"
                  }
                  ["postal-code"]=>
                  array(1) {
                    [0]=>
                    string(5) "02139"
                  }
                  ["country-name"]=>
                  array(1) {
                    [0]=>
                    string(3) "USA"
                  }
                }
                ["value"]=>
                string(150) "32 Vassar Street, 
            Room 32-G524, 
            Cambridge,  
            MA 
            02139, 
            USA.  
            (Work)"
              }
            }
            ["tel"]=>
            array(1) {
              [0]=>
              string(17) "+1 (617) 253 5702"
            }
            ["email"]=>
            array(1) {
              [0]=>
              string(19) "mailto:timbl@w3.org"
            }
          }
          ["value"]=>
          string(15) "Tim Berners-Lee"
        }
      }
      ["summary"]=>
      array(1) {
        [0]=>
        string(28) "Invented the World Wide Web."
      }
    }
  }
}
