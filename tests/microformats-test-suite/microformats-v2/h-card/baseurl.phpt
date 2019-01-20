--TEST--
mf2: mf-test-suite: v2/h-card/baseurl
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/baseurl.html')->items);

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
    array(4) {
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
      ["org"]=>
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
              string(18) "Mozilla Foundation"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(39) "http://example.org/bios/mitchell-baker/"
            }
          }
          ["value"]=>
          string(18) "Mozilla Foundation"
        }
      }
      ["photo"]=>
      array(1) {
        [0]=>
        string(35) "http://example.org/images/photo.gif"
      }
    }
  }
}
