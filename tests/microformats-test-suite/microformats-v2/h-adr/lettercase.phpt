--TEST--
mf2: mf-test-suite: v2/h-adr/lettercase
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/lettercase.html'));

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
      array(3) {
        ["name"]=>
        array(1) {
          [0]=>
          string(17) "Bricklayer's Arms"
        }
        ["street-address"]=>
        array(1) {
          [0]=>
          string(16) "3 Charlotte Road"
        }
        ["locality"]=>
        array(1) {
          [0]=>
          string(14) "City of London"
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