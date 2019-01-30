--TEST--
mf2: mf-test-suite: v1/hproduct/simpleproperties
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
        string(9) "h-product"
      }
      ["properties"]=>
      array(7) {
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
              string(8) "h-review"
            }
            ["properties"]=>
            array(1) {
              ["rating"]=>
              array(1) {
                [0]=>
                string(3) "4.5"
              }
            }
            ["value"]=>
            string(12) "4.5 out of 5"
          }
        }
        ["category"]=>
        array(2) {
          [0]=>
          string(8) "Computer"
          [1]=>
          string(9) "Education"
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
