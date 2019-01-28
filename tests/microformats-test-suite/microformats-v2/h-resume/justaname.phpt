--TEST--
mf2: mf-test-suite: v2/h-resume/justaname
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/justaname.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(8) "h-resume"
    }
    ["properties"]=>
    array(1) {
      ["name"]=>
      array(1) {
        [0]=>
        string(45) "Tim Berners-Lee, invented the World Wide Web."
      }
    }
  }
}
