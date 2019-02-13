--TEST--
mf2: mf-test-suite: v1/hcard/single
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/single.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(10) {
      ["name"]=>
      array(1) {
        [0]=>
        string(8) "John Doe"
      }
      ["given-name"]=>
      array(1) {
        [0]=>
        string(4) "John"
      }
      ["sort-string"]=>
      array(1) {
        [0]=>
        string(4) "John"
      }
      ["bday"]=>
      array(1) {
        [0]=>
        string(25) "2000-01-01T00:00:00-08:00"
      }
      ["role"]=>
      array(1) {
        [0]=>
        string(8) "Designer"
      }
      ["geo"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(5) "h-geo"
          }
          ["properties"]=>
          array(0) {
          }
          ["value"]=>
          string(20) "30.267991;-97.739568"
        }
      }
      ["tz"]=>
      array(1) {
        [0]=>
        string(6) "-05:00"
      }
      ["uid"]=>
      array(1) {
        [0]=>
        string(35) "http://example.com/profiles/johndoe"
      }
      ["class"]=>
      array(1) {
        [0]=>
        string(6) "Public"
      }
      ["rev"]=>
      array(1) {
        [0]=>
        string(19) "2008-01-01T13:45:00"
      }
    }
  }
}
