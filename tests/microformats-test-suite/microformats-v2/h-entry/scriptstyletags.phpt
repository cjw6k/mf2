--TEST--
mf2: mf-test-suite: v2/h-entry/scriptstyletags
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/scriptstyletags.html')->items);

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
        string(6) "A post"
      }
      ["content"]=>
      array(1) {
        [0]=>
        array(2) {
          ["html"]=>
          string(84) "text <strong>bold</strong><script>x = 1</script><style>strong {color: #fff};</style>"
          ["value"]=>
          string(9) "text bold"
        }
      }
    }
  }
}
