--TEST--
mf2: mf-test-suite: v2/h-card/nested
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/nested.html')->items);

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
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(14) "Mitchell Baker"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(31) "http://blog.lizardwrangler.com/"
      }
    }
    ["children"]=>
    array(1) {
      [0]=>
      object(MF2Microformat)#3 (2) {
        ["type"]=>
        array(2) {
          [0]=>
          string(6) "h-card"
          [1]=>
          string(5) "h-org"
        }
        ["properties"]=>
        array(2) {
          ["name"]=>
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
      }
    }
  }
}
