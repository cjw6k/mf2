--TEST--
mf2: mf-test-suite: v2/h-card/relativeurlsempty
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/relativeurlsempty.html')->items);

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
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(14) "Max Mustermann"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(26) "http://example.com/profile"
      }
      ["uid"]=>
      array(1) {
        [0]=>
        string(26) "http://example.com/profile"
      }
    }
  }
}
