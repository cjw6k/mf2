--TEST--
mf2: mf-test-suite: v2/h-resume/education
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
    array(4) {
      ["name"]=>
      array(1) {
        [0]=>
        string(15) "Tim Berners-Lee"
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
          array(1) {
            ["title"]=>
            array(1) {
              [0]=>
              string(41) "Director of the World Wide Web Foundation"
            }
          }
          ["value"]=>
          string(41) "Director of the World Wide Web Foundation"
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
              object(DateTime)#5 (4) {
                ["value"]=>
                string(7) "1973-09"
                ["date"]=>
                string(26) "1973-09-01 00:00:00.000000"
                ["timezone_type"]=>
                int(3)
                ["timezone"]=>
                string(3) "UTC"
              }
            }
            ["end"]=>
            array(1) {
              [0]=>
              object(DateTime)#6 (4) {
                ["value"]=>
                string(7) "1976-06"
                ["date"]=>
                string(26) "1976-06-01 00:00:00.000000"
                ["timezone_type"]=>
                int(3)
                ["timezone"]=>
                string(3) "UTC"
              }
            }
          }
          ["value"]=>
          string(38) "The Queen's College, Oxford University"
        }
      }
    }
  }
}
