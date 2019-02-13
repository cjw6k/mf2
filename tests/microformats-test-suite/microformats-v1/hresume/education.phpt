--TEST--
mf2: mf-test-suite: v1/hresume/education
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/education.html')->items);

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
      ["education"]=>
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
          array(5) {
            ["name"]=>
            array(1) {
              [0]=>
              string(38) "The Queen's College, Oxford University"
            }
            ["org"]=>
            array(1) {
              [0]=>
              string(38) "The Queen's College, Oxford University"
            }
            ["description"]=>
            array(1) {
              [0]=>
              string(19) "BA Hons (I) Physics"
            }
            ["start"]=>
            array(1) {
              [0]=>
              string(7) "1973-09"
            }
            ["end"]=>
            array(1) {
              [0]=>
              string(7) "1976-06"
            }
          }
          ["value"]=>
          string(38) "The Queen's College, Oxford University"
        }
      }
    }
  }
}
