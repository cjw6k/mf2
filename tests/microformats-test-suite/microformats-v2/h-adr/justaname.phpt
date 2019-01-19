--TEST--
mf2: mf-test-suite: v2/h-adr/justaname
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/justaname.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(1) {
    [0]=>
    object(MF2Microformat)#2 (2) {
      ["type"]=>
      array(1) {
        [0]=>
        string(5) "h-adr"
      }
      ["properties"]=>
      array(1) {
        ["name"]=>
        array(1) {
          [0]=>
          string(52) "665 3rd St. Suite 207 San Francisco, CA 94107 U.S.A."
        }
      }
    }
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}