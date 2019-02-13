--TEST--
mf2: mf-test-suite: v1/hcalendar/concatenate
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/concatenate.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-event"
    }
    ["properties"]=>
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(25) "The 4th Microformat party"
      }
      ["start"]=>
      array(1) {
        [0]=>
        string(16) "2009-06-26 19:00"
      }
      ["end"]=>
      array(1) {
        [0]=>
        string(16) "2009-06-26 22:00"
      }
    }
  }
}
