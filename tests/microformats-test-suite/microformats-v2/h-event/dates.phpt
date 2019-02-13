--TEST--
mf2: mf-test-suite: v2/h-event/dates
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/dates.html')->items);

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
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(25) "The 4th Microformat party"
      }
      ["start"]=>
      array(8) {
        [0]=>
        string(22) "2009-06-26T19:00-08:00"
        [1]=>
        string(19) "2009-06-26T19:00-08"
        [2]=>
        string(21) "2009-06-26T19:00-0800"
        [3]=>
        string(21) "2009-06-26T19:00+0800"
        [4]=>
        string(22) "2009-06-26T19:00+08:00"
        [5]=>
        string(17) "2009-06-26T19:00Z"
        [6]=>
        string(22) "2009-06-26t19:00-08:00"
        [7]=>
        string(25) "2009-06-26 19:00:00-08:00"
      }
    }
  }
}
