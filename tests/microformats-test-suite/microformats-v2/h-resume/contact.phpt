--TEST--
mf2: mf-test-suite: v2/h-resume/contact
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
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(15) "Tim Berners-Lee"
      }
      ["summary"]=>
      array(1) {
        [0]=>
        string(28) "Invented the World Wide Web."
      }
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
          array(9) {
            ["name"]=>
            array(1) {
              [0]=>
              string(3) "MIT"
            }
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
          string(3) "MIT"
        }
      }
    }
  }
}
