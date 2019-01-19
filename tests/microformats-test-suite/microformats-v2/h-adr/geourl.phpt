--TEST--
mf2: mf-test-suite: v2/h-adr/geourl
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/geourl.html'));

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
        ["geo"]=>
        array(1) {
          [0]=>
          string(38) "geo:51.526421;-0.081067;crs=wgs84;u=40"
        }
        ["locality"]=>
        array(1) {
          [0]=>
          string(6) "London"
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