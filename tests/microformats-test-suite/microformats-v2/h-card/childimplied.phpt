--TEST--
mf2: mf-test-suite: v2/h-card/childimplied
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/childimplied.html')->items);

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
        string(15) "Håkon Wium Lie"
      }
      ["photo"]=>
      array(1) {
        [0]=>
        string(126) "http://upload.wikimedia.org/wikipedia/commons/thumb/9/96/H%C3%A5kon-Wium-Lie-2009-03.jpg/215px-H%C3%A5kon-Wium-Lie-2009-03.jpg"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(32) "http://people.opera.com/howcome/"
      }
    }
  }
}