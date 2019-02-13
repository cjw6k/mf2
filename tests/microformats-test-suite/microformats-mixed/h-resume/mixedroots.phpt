--TEST--
mf2: mf-test-suite: mixed/h-resume/mixedroots
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/mixedroots.html')->items);

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
          array(2) {
            ["name"]=>
            array(1) {
              [0]=>
              string(15) "Tim Berners-Lee"
            }
            ["job-title"]=>
            array(1) {
              [0]=>
              string(41) "Director of the World Wide Web Foundation"
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
      ["experience"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#4 (3) {
          ["type"]=>
          array(2) {
            [0]=>
            string(6) "h-card"
            [1]=>
            string(7) "h-event"
          }
          ["properties"]=>
          array(6) {
            ["job-title"]=>
            array(1) {
              [0]=>
              string(8) "Director"
            }
            ["name"]=>
            array(1) {
              [0]=>
              string(25) "World Wide Web Foundation"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(29) "http://www.webfoundation.org/"
            }
            ["org"]=>
            array(1) {
              [0]=>
              string(25) "World Wide Web Foundation"
            }
            ["start"]=>
            array(1) {
              [0]=>
              string(10) "2009-01-18"
            }
            ["duration"]=>
            array(1) {
              [0]=>
              string(6) "P2Y11M"
            }
          }
          ["value"]=>
          string(25) "World Wide Web Foundation"
        }
      }
    }
  }
}
