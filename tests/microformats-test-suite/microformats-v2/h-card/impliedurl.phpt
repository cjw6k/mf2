--TEST--
mf2: mf-test-suite: v2/h-card/impliedurl
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/impliedurl.html')->items);

?>
--EXPECT--
array(5) {
  [0]=>
  object(MF2Microformat)#2 (2) {
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
        string(8) "Jane Doe"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(9) "jane.html"
      }
    }
  }
  [1]=>
  object(MF2Microformat)#3 (2) {
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
        string(8) "Jane Doe"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(9) "jane.html"
      }
    }
  }
  [2]=>
  object(MF2Microformat)#4 (2) {
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
        string(8) "Jane Doe"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(9) "jane.html"
      }
    }
  }
  [3]=>
  object(MF2Microformat)#5 (2) {
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
        string(8) "Jane Doe"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(9) "jane.html"
      }
    }
  }
  [4]=>
  object(MF2Microformat)#6 (3) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(0) {
    }
    ["children"]=>
    array(1) {
      [0]=>
      object(MF2Microformat)#7 (2) {
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
            string(8) "Jane Doe"
          }
          ["url"]=>
          array(1) {
            [0]=>
            string(9) "jane.html"
          }
        }
      }
    }
  }
}
