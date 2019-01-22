--TEST--
mf2: mf-test-suite: v2/h-entry/impliedvalue-nested
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/impliedvalue-nested.html')->items);

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
    array(1) {
      ["in-reply-to"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-cite"
          }
          ["properties"]=>
          array(3) {
            ["author"]=>
            array(1) {
              [0]=>
              object(MF2Microformat)#4 (3) {
                ["type"]=>
                array(1) {
                  [0]=>
                  string(6) "h-card"
                }
                ["properties"]=>
                array(2) {
                  ["name"]=>
                  array(1) {
                    [0]=>
                    string(14) "Example Author"
                  }
                  ["url"]=>
                  array(1) {
                    [0]=>
                    string(18) "http://example.com"
                  }
                }
                ["value"]=>
                string(14) "Example Author"
              }
            }
            ["name"]=>
            array(1) {
              [0]=>
              string(12) "Example Post"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(23) "http://example.com/post"
            }
          }
          ["value"]=>
          string(23) "http://example.com/post"
        }
      }
    }
  }
}
