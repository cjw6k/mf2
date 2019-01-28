--TEST--
mf2: mf-test-suite: v2/h-resume/affiliation
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/affiliation.html')->items);

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
        string(27) "invented the World Wide Web"
      }
      ["affiliation"]=>
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
              string(3) "W3C"
            }
            ["photo"]=>
            array(1) {
              [0]=>
              array(2) {
                ["value"]=>
                string(43) "http://www.w3.org/Icons/WWW/w3c_home_nb.png"
                ["alt"]=>
                string(3) "W3C"
              }
            }
          }
          ["value"]=>
          string(3) "W3C"
        }
      }
    }
  }
}
