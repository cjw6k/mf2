--TEST--
mf2: mf-test-suite: mixed/h-entry/mixedroots
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/mixedroots.html'));

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
        string(7) "h-entry"
      }
      ["properties"]=>
      array(4) {
        ["author"]=>
        array(1) {
          [0]=>
          object(MF2Microformat)#3 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(6) "h-card"
            }
            ["properties"]=>
            array(5) {
              ["photo"]=>
              array(1) {
                [0]=>
                array(2) {
                  ["value"]=>
                  string(43) "https://aaronparecki.com/images/aaronpk.png"
                  ["alt"]=>
                  string(13) "Aaron Parecki"
                }
              }
              ["logo"]=>
              array(1) {
                [0]=>
                array(2) {
                  ["value"]=>
                  string(43) "https://aaronparecki.com/images/aaronpk.png"
                  ["alt"]=>
                  string(13) "Aaron Parecki"
                }
              }
              ["url"]=>
              array(1) {
                [0]=>
                string(25) "https://aaronparecki.com/"
              }
              ["uid"]=>
              array(1) {
                [0]=>
                string(25) "https://aaronparecki.com/"
              }
              ["name"]=>
              array(1) {
                [0]=>
                string(13) "Aaron Parecki"
              }
            }
            ["value"]=>
            string(13) "Aaron Parecki"
          }
        }
        ["content"]=>
        array(1) {
          [0]=>
          array(2) {
            ["html"]=>
            string(403) "Did you play
    <a href="http://twitter.com/playmapattack">@playmapattack</a>at
    <a href="http://aaronparecki.com/tag/realtimeconf">#<span class="p-category">realtimeconf</span></a>? Here is some more info about how we built it!
    <a href="http://pdx.esri.com/blog/2013/10/17/introducting-mapattack/"><span class="protocol">http://</span>pdx.esri.com/blog/2013/10/17/introducting-mapattack/</a>"
            ["value"]=>
            string(165) "Did you play
    @playmapattackat
    #realtimeconf? Here is some more info about how we built it!
    http://pdx.esri.com/blog/2013/10/17/introducting-mapattack/"
          }
        }
        ["name"]=>
        array(1) {
          [0]=>
          string(165) "Did you play
    @playmapattackat
    #realtimeconf? Here is some more info about how we built it!
    http://pdx.esri.com/blog/2013/10/17/introducting-mapattack/"
        }
        ["category"]=>
        array(1) {
          [0]=>
          string(12) "realtimeconf"
        }
      }
    }
  }
  ["rels"]=>
  array(1) {
    ["author"]=>
    array(2) {
      [0]=>
      string(25) "https://aaronparecki.com/"
      [1]=>
      string(45) "https://plus.google.com/117847912875913905493"
    }
  }
  ["rel_urls"]=>
  array(2) {
    ["https://aaronparecki.com/"]=>
    array(2) {
      ["text"]=>
      string(16) "aaronparecki.com"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "author"
      }
    }
    ["https://plus.google.com/117847912875913905493"]=>
    array(2) {
      ["text"]=>
      string(13) "Aaron Parecki"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "author"
      }
    }
  }
}
