--TEST--
mf2: mf-test-suite: v2/h-adr/simpleproperties
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/simpleproperties.html'));

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
      array(6) {
        ["street-address"]=>
        array(1) {
          [0]=>
          string(11) "665 3rd St."
        }
        ["extended-address"]=>
        array(1) {
          [0]=>
          string(9) "Suite 207"
        }
        ["locality"]=>
        array(1) {
          [0]=>
          string(13) "San Francisco"
        }
        ["region"]=>
        array(1) {
          [0]=>
          string(2) "CA"
        }
        ["postal-code"]=>
        array(1) {
          [0]=>
          string(5) "94107"
        }
        ["country-name"]=>
        array(1) {
          [0]=>
          string(6) "U.S.A."
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