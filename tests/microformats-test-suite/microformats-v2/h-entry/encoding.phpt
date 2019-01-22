--TEST--
mf2: mf-test-suite: v2/h-entry/encoding
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/encoding.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-entry"
    }
    ["properties"]=>
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(28) "x<y AT&T <b>NotBold</b> Bold"
      }
      ["content"]=>
      array(1) {
        [0]=>
        array(2) {
          ["html"]=>
          string(54) "x&lt;y AT&amp;T &lt;b&gt;NotBold&lt;/b&gt; <b>Bold</b>"
          ["value"]=>
          string(28) "x<y AT&T <b>NotBold</b> Bold"
        }
      }
    }
  }
}
