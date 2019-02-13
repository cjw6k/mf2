--TEST--
mf2: mf-test-suite: v1/hcalendar/ampm
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/ampm.html')->items);

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
      array(9) {
        [0]=>
        string(21) "2009-06-26 07:00:00pm"
        [1]=>
        string(21) "2009-06-26 07:00:00am"
        [2]=>
        string(18) "2009-06-26 07:00pm"
        [3]=>
        string(15) "2009-06-26 07pm"
        [4]=>
        string(14) "2009-06-26 7pm"
        [5]=>
        string(17) "2009-06-26 7:00pm"
        [6]=>
        string(20) "2009-06-26 07:00p.m."
        [7]=>
        string(18) "2009-06-26 07:00PM"
        [8]=>
        string(17) "2009-06-26 7:00am"
      }
    }
  }
}
