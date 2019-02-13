--TEST--
mf2: mf-test-suite: v2/h-event/combining
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/combining.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-event"
    }
    ["properties"]=>
    array(5) {
      ["name"]=>
      array(1) {
        [0]=>
        string(17) "IndieWebCamp 2012"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(28) "http://indiewebcamp.com/2012"
      }
      ["start"]=>
      array(1) {
        [0]=>
        string(10) "2012-06-30"
      }
      ["end"]=>
      array(1) {
        [0]=>
        string(10) "2012-07-01"
      }
      ["location"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-card"
          }
          ["properties"]=>
          array(6) {
            ["name"]=>
            array(1) {
              [0]=>
              string(7) "Geoloqi"
            }
            ["org"]=>
            array(1) {
              [0]=>
              string(7) "Geoloqi"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(19) "http://geoloqi.com/"
            }
            ["street-address"]=>
            array(1) {
              [0]=>
              string(25) "920 SW 3rd Ave. Suite 400"
            }
            ["locality"]=>
            array(1) {
              [0]=>
              string(8) "Portland"
            }
            ["region"]=>
            array(1) {
              [0]=>
              string(6) "Oregon"
            }
          }
          ["value"]=>
          string(7) "Geoloqi"
        }
      }
    }
  }
}
