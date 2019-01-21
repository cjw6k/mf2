--TEST--
mf2: mf-test-suite: v2/h-card/extendeddescription
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/extendeddescription.html')->items);

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
    array(6) {
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(62) "http://blog.mozilla.org/press/files/2012/04/mitchell-baker.jpg"
          ["alt"]=>
          string(17) "photo of Mitchell"
        }
      }
      ["name"]=>
      array(1) {
        [0]=>
        string(14) "Mitchell Baker"
      }
      ["url"]=>
      array(2) {
        [0]=>
        string(31) "http://blog.lizardwrangler.com/"
        [1]=>
        string(33) "https://twitter.com/MitchellBaker"
      }
      ["org"]=>
      array(1) {
        [0]=>
        string(18) "Mozilla Foundation"
      }
      ["note"]=>
      array(1) {
        [0]=>
        string(105) "Mitchell is responsible for setting the direction and scope of the Mozilla Foundation and its activities."
      }
      ["category"]=>
      array(2) {
        [0]=>
        string(8) "Strategy"
        [1]=>
        string(10) "Leadership"
      }
    }
  }
}
