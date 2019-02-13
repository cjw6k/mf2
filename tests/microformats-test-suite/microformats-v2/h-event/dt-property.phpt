--TEST--
mf2: mf-test-suite: v2/h-event/dt-property
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/dt-property.html')->items);

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
        string(9) "The party"
      }
      ["start"]=>
      array(8) {
        [0]=>
        string(10) "2013-03-14"
        [1]=>
        string(21) "2013-06-25 07:00:00am"
        [2]=>
        string(10) "2013-06-26"
        [3]=>
        string(10) "2013-06-27"
        [4]=>
        string(10) "2013-06-28"
        [5]=>
        string(10) "2013-06-29"
        [6]=>
        string(10) "2013-07-01"
        [7]=>
        string(10) "2013-07-02"
      }
    }
  }
}
