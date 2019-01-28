--TEST--
mf2: mf-test-suite: v2/h-resume/skill
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/skill.html')->items);

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
    array(3) {
      ["name"]=>
      array(1) {
        [0]=>
        string(15) "Tim Berners-Lee"
      }
      ["summary"]=>
      array(1) {
        [0]=>
        string(27) "invented the World Wide Web"
      }
      ["skill"]=>
      array(3) {
        [0]=>
        string(19) "information systems"
        [1]=>
        string(8) "advocacy"
        [2]=>
        string(10) "leadership"
      }
    }
  }
}
