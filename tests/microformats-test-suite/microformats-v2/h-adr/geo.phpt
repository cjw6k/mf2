--TEST--
mf2: mf-test-suite: v2/h-adr/geo
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/geo.html'));

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
      array(7) {
        ["name"]=>
        array(1) {
          [0]=>
          string(17) "Bricklayer's Arms"
        }
        ["label"]=>
        array(1) {
          [0]=>
          string(78) "3 Charlotte Road,  
        City of London,  
        EC2A 3PE, 
        UK"
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
        ["postal-code"]=>
        array(1) {
          [0]=>
          string(8) "EC2A 3PE"
        }
        ["country-name"]=>
        array(1) {
          [0]=>
          string(2) "UK"
        }
        ["geo"]=>
        array(1) {
          [0]=>
          string(19) "51.526421;-0.081067"
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
