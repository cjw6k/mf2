--TEST--
mf2: mf-test-suite: v2/h-entry/u-property
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/u-property.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-entry"
    }
    ["properties"]=>
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(21) "microformats.org at 7"
      }
      ["url"]=>
      array(8) {
        [0]=>
        string(24) "http://microformats.org/"
        [1]=>
        string(56) "http://microformats.org/2012/06/25/microformats-org-at-7"
        [2]=>
        string(56) "http://microformats.org/2012/06/25/microformats-org-at-7"
        [3]=>
        string(24) "http://microformats.org/"
        [4]=>
        string(50) "http://microformats.org/wiki/microformats2-parsing"
        [5]=>
        string(48) "http://microformats.org/wiki/value-class-pattern"
        [6]=>
        string(29) "http://microformats.org/wiki/"
        [7]=>
        string(31) "http://microformats.org/discuss"
      }
      ["photo"]=>
      array(2) {
        [0]=>
        array(2) {
          ["value"]=>
          string(34) "http://example.com/images/logo.gif"
          ["alt"]=>
          string(13) "company logos"
        }
        [1]=>
        string(34) "http://example.com/posterimage.jpg"
      }
    }
  }
}
