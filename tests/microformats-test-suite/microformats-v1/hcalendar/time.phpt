--TEST--
mf2: mf-test-suite: v1/hcalendar/time
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/time.html')->items);

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
      array(9) {
        [0]=>
        string(25) "2009-06-26 19:00:00-08:00"
        [1]=>
        string(24) "2009-06-26 19:00:00-0800"
        [2]=>
        string(24) "2009-06-26 19:00:00+0800"
        [3]=>
        string(20) "2009-06-26 19:00:00Z"
        [4]=>
        string(19) "2009-06-26 19:00:00"
        [5]=>
        string(22) "2009-06-26 19:00-08:00"
        [6]=>
        string(22) "2009-06-26 19:00+08:00"
        [7]=>
        string(10) "2009-06-26"
        [8]=>
        string(16) "2009-06-26 19:00"
      }
      ["end"]=>
      array(1) {
        [0]=>
        string(8) "2013-034"
      }
    }
  }
}
