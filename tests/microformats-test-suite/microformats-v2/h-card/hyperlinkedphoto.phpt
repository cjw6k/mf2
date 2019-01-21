--TEST--
mf2: mf-test-suite: v2/h-card/hyperlinkedphoto
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/hyperlinkedphoto.html')->items);

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
        string(11) "Rohit Khare"
      }
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(16) "images/photo.gif"
          ["alt"]=>
          string(11) "Rohit Khare"
        }
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(23) "http://rohit.khare.org/"
      }
    }
  }
}