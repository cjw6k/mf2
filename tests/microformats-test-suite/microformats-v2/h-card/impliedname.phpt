--TEST--
mf2: mf-test-suite: v2/h-card/impliedname
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/impliedname.html')->items);

?>
--EXPECT--
array(14) {
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
          string(9) "jane.html"
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
    array(1) {
      ["name"]=>
      array(1) {
        [0]=>
        string(8) "Jane Doe"
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
        array(2) {
          ["value"]=>
          string(9) "jane.html"
          ["alt"]=>
          string(8) "Jane Doe"
        }
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
      ["url"]=>
      array(1) {
        [0]=>
        string(9) "jane.html"
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
    array(1) {
      ["name"]=>
      array(1) {
        [0]=>
        string(8) "Jane Doe"
      }
    }
  }
  [6]=>
  object(MF2Microformat)#8 (2) {
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
          string(9) "jane.html"
          ["alt"]=>
          string(8) "Jane Doe"
        }
      }
    }
  }
  [7]=>
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
      ["url"]=>
      array(1) {
        [0]=>
        string(9) "jane.html"
      }
    }
  }
  [8]=>
  object(MF2Microformat)#10 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(1) {
      ["name"]=>
      array(1) {
        [0]=>
        string(8) "Jane Doe"
      }
    }
  }
  [9]=>
  object(MF2Microformat)#11 (3) {
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
          ["photo"]=>
          array(1) {
            [0]=>
            array(2) {
              ["value"]=>
              string(9) "john.html"
              ["alt"]=>
              string(8) "John Doe"
            }
          }
        }
      }
    }
  }
  [10]=>
  object(MF2Microformat)#13 (3) {
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
      object(MF2Microformat)#14 (2) {
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
          ["photo"]=>
          array(1) {
            [0]=>
            array(2) {
              ["value"]=>
              string(9) "john.html"
              ["alt"]=>
              string(8) "John Doe"
            }
          }
        }
      }
    }
  }
  [11]=>
  object(MF2Microformat)#15 (3) {
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
      object(MF2Microformat)#16 (2) {
        ["type"]=>
        array(1) {
          [0]=>
          string(6) "h-card"
        }
        ["properties"]=>
        array(1) {
          ["name"]=>
          array(1) {
            [0]=>
            string(8) "John Doe"
          }
        }
      }
    }
  }
  [12]=>
  object(MF2Microformat)#17 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-card"
    }
    ["properties"]=>
    array(1) {
      ["org"]=>
      array(1) {
        [0]=>
        string(7) "Mozilla"
      }
    }
  }
  [13]=>
  object(MF2Microformat)#18 (2) {
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
        string(12) "John Doe Jr."
      }
      ["photo"]=>
      array(1) {
        [0]=>
        array(2) {
          ["value"]=>
          string(10) "/photo.jpg"
          ["alt"]=>
          string(3) "Jr."
        }
      }
    }
  }
}
