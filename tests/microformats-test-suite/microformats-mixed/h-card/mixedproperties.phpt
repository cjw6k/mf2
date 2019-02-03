--TEST--
mf2: mf-test-suite: mixed/h-card/mixedproperties
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/mixedproperties.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (3) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(18) "Mozilla Foundation"
      }
      ["org"]=>
      array(1) {
        [0]=>
        string(18) "Mozilla Foundation"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(19) "http://mozilla.org/"
      }
    }
    ["children"]=>
    array(1) {
      [0]=>
      object(MF2Microformat)#3 (2) {
        ["type"]=>
        array(1) {
          [0]=>
          string(5) "h-adr"
        }
        ["properties"]=>
        array(5) {
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
        }
      }
    }
  }
}
