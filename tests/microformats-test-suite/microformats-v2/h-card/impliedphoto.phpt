--TEST--
mf2: mf-test-suite: v2/h-card/impliedphoto
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/impliedphoto.html')->items);

?>
--EXPECT--
array(10) {
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
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(9) "jane.jpeg"
          ["alt"]=>
          string(8) "Jane Doe"
        }
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
      ["photo"]=>
      array(1) {
        [0]=>
        string(9) "jane.jpeg"
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
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(9) "jane.jpeg"
          ["alt"]=>
          string(8) "Jane Doe"
        }
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
      ["photo"]=>
      array(1) {
        [0]=>
        string(9) "jane.jpeg"
      }
    }
  }
  [4]=>
  object(MF2Microformat)#6 (2) {
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
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(9) "jane.jpeg"
          ["alt"]=>
          string(8) "Jane Doe"
        }
      }
    }
  }
  [5]=>
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
      ["photo"]=>
      array(1) {
        [0]=>
        string(9) "jane.jpeg"
      }
    }
  }
  [6]=>
  object(MF2Microformat)#8 (3) {
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
      object(MF2Microformat)#9 (2) {
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
          ["photo"]=>
          array(1) {
            [0]=>
            array(2) {
              ["value"]=>
              string(9) "jane.jpeg"
              ["alt"]=>
              string(8) "Jane Doe"
            }
          }
        }
      }
    }
  }
  [7]=>
  object(MF2Microformat)#10 (3) {
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
      object(MF2Microformat)#11 (2) {
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
          ["photo"]=>
          array(1) {
            [0]=>
            string(9) "jane.jpeg"
          }
        }
      }
    }
  }
  [8]=>
  object(MF2Microformat)#12 (2) {
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
        string(8) "John Doe"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(19) "https://example.com"
      }
    }
  }
  [9]=>
  object(MF2Microformat)#13 (2) {
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
        string(8) "John Doe"
      }
      ["url"]=>
      array(1) {
        [0]=>
        string(19) "https://example.com"
      }
    }
  }
}
