--TEST--
mf2: mf-test-suite: v1/hproduct/aggregate
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/aggregate.html'));

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
        string(9) "h-product"
      }
      ["properties"]=>
      array(8) {
        ["name"]=>
        array(1) {
          [0]=>
          string(12) "Raspberry Pi"
        }
        ["photo"]=>
        array(1) {
          [0]=>
          string(94) "http://upload.wikimedia.org/wikipedia/commons/thumb/3/3d/RaspberryPi.jpg/320px-RaspberryPi.jpg"
        }
        ["description"]=>
        array(1) {
          [0]=>
          string(344) "The Raspberry Pi is a credit-card sized computer that plugs into your TV and a keyboard. It’s a capable little PC which can be used for many of the things that your desktop PC does, like spreadsheets, word-processing and games. It also plays high-definition video. We want to see it being used by kids all over the world to learn programming."
        }
        ["url"]=>
        array(1) {
          [0]=>
          string(27) "http://www.raspberrypi.org/"
        }
        ["price"]=>
        array(1) {
          [0]=>
          string(7) "£29.95"
        }
        ["review"]=>
        array(1) {
          [0]=>
          object(MF2Microformat)#3 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(18) "h-review-aggregate"
            }
            ["properties"]=>
            array(4) {
              ["rating"]=>
              array(1) {
                [0]=>
                string(3) "9.2"
              }
              ["average"]=>
              array(1) {
                [0]=>
                string(3) "9.2"
              }
              ["best"]=>
              array(1) {
                [0]=>
                string(2) "10"
              }
              ["count"]=>
              array(1) {
                [0]=>
                string(3) "178"
              }
            }
            ["value"]=>
            string(62) "9.2 out of 
            10 
            based on 178 reviews"
          }
        }
        ["category"]=>
        array(2) {
          [0]=>
          string(8) "Computer"
          [1]=>
          string(9) "Education"
        }
        ["brand"]=>
        array(1) {
          [0]=>
          object(MF2Microformat)#4 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(6) "h-card"
            }
            ["properties"]=>
            array(3) {
              ["name"]=>
              array(1) {
                [0]=>
                string(27) "The Raspberry Pi Foundation"
              }
              ["org"]=>
              array(1) {
                [0]=>
                string(27) "The Raspberry Pi Foundation"
              }
              ["adr"]=>
              array(1) {
                [0]=>
                object(MF2Microformat)#5 (3) {
                  ["type"]=>
                  array(1) {
                    [0]=>
                    string(5) "h-adr"
                  }
                  ["properties"]=>
                  array(2) {
                    ["locality"]=>
                    array(1) {
                      [0]=>
                      string(9) "Cambridge"
                    }
                    ["country-name"]=>
                    array(1) {
                      [0]=>
                      string(2) "UK"
                    }
                  }
                  ["value"]=>
                  string(26) "Cambridge 
            UK"
                }
              }
            }
            ["value"]=>
            string(27) "The Raspberry Pi Foundation"
          }
        }
      }
    }
  }
  ["rels"]=>
  array(1) {
    ["tag"]=>
    array(2) {
      [0]=>
      string(37) "http://en.wikipedia.org/wiki/computer"
      [1]=>
      string(38) "http://en.wikipedia.org/wiki/education"
    }
  }
  ["rel_urls"]=>
  array(2) {
    ["http://en.wikipedia.org/wiki/computer"]=>
    array(2) {
      ["text"]=>
      string(8) "Computer"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
    ["http://en.wikipedia.org/wiki/education"]=>
    array(2) {
      ["text"]=>
      string(9) "Education"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
  }
}
