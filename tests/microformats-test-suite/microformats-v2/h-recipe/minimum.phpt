--TEST--
mf2: mf-test-suite: v2/h-recipe/minimum
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/minimum.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(8) "h-recipe"
    }
    ["properties"]=>
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(5) "Toast"
      }
      ["ingredient"]=>
      array(2) {
        [0]=>
        array(2) {
          ["html"]=>
          string(14) "Slice of bread"
          ["value"]=>
          string(14) "Slice of bread"
        }
        [1]=>
        array(2) {
          ["html"]=>
          string(6) "Butter"
          ["value"]=>
          string(6) "Butter"
        }
      }
    }
  }
}
