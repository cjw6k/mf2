--TEST--
mf2: mf-test-suite: v2/h-entry/impliedname
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/impliedname.html')->items);

?>
--EXPECT--
array(4) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-entry"
    }
    ["properties"]=>
    array(1) {
      ["name"]=>
      array(1) {
        [0]=>
        string(26) "This should imply a p-name"
      }
    }
  }
  [1]=>
  object(MF2Microformat)#3 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-entry"
    }
    ["properties"]=>
    array(1) {
      ["content"]=>
      array(1) {
        [0]=>
        string(60) "This should not imply a p-name since it has an p-* property."
      }
    }
  }
  [2]=>
  object(MF2Microformat)#4 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-entry"
    }
    ["properties"]=>
    array(1) {
      ["content"]=>
      array(1) {
        [0]=>
        array(2) {
          ["html"]=>
          string(67) "<p>This should not imply a p-name since it has an e-* property.</p>"
          ["value"]=>
          string(60) "This should not imply a p-name since it has an e-* property."
        }
      }
    }
  }
  [3]=>
  object(MF2Microformat)#5 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-entry"
    }
    ["properties"]=>
    array(1) {
      ["like-of"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#6 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-cite"
          }
          ["properties"]=>
          array(2) {
            ["name"]=>
            array(1) {
              [0]=>
              string(12) "Microformats"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(24) "http://microformats.org/"
            }
          }
          ["value"]=>
          string(24) "http://microformats.org/"
        }
      }
    }
  }
}
