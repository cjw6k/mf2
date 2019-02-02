--TEST--
mf2: mf-test-suite: v1/hreview/vcard
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/vcard.html'));

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
        string(8) "h-review"
      }
      ["properties"]=>
      array(7) {
        ["rating"]=>
        array(1) {
          [0]=>
          string(1) "5"
        }
        ["name"]=>
        array(1) {
          [0]=>
          string(25) "Crepes on Cole is awesome"
        }
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
            array(1) {
              ["name"]=>
              array(1) {
                [0]=>
                string(6) "Tantek"
              }
            }
            ["value"]=>
            string(6) "Tantek"
          }
        }
        ["content"]=>
        array(1) {
          [0]=>
          array(2) {
            ["html"]=>
            string(561) "<p class="item vcard">
        <span class="fn org">Crepes on Cole</span> is one of the best little 
        creperies in <span class="adr"><span class="locality">San Francisco</span></span>.
        Excellent food and service. Plenty of tables in a variety of sizes 
        for parties large and small.  Window seating makes for excellent 
        people watching to/from the N-Judah which stops right outside.  
        I've had many fun social gatherings here, as well as gotten 
        plenty of work done thanks to neighborhood WiFi.
        </p>"
            ["value"]=>
            string(432) "Crepes on Cole is one of the best little 
        creperies in San Francisco.
        Excellent food and service. Plenty of tables in a variety of sizes 
        for parties large and small.  Window seating makes for excellent 
        people watching to/from the N-Judah which stops right outside.  
        I've had many fun social gatherings here, as well as gotten 
        plenty of work done thanks to neighborhood WiFi."
          }
        }
        ["item"]=>
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
                string(14) "Crepes on Cole"
              }
              ["org"]=>
              array(1) {
                [0]=>
                string(14) "Crepes on Cole"
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
                  array(1) {
                    ["locality"]=>
                    array(1) {
                      [0]=>
                      string(13) "San Francisco"
                    }
                  }
                  ["value"]=>
                  string(13) "San Francisco"
                }
              }
            }
            ["value"]=>
            string(14) "Crepes on Cole"
          }
        }
        ["category"]=>
        array(1) {
          [0]=>
          string(5) "crepe"
        }
        ["url"]=>
        array(1) {
          [0]=>
          string(24) "http://example.com/crepe"
        }
      }
    }
  }
  ["rels"]=>
  array(4) {
    ["tag"]=>
    array(1) {
      [0]=>
      string(34) "http://en.wikipedia.org/wiki/crepe"
    }
    ["self"]=>
    array(1) {
      [0]=>
      string(24) "http://example.com/crepe"
    }
    ["bookmark"]=>
    array(1) {
      [0]=>
      string(24) "http://example.com/crepe"
    }
    ["license"]=>
    array(1) {
      [0]=>
      string(107) "http://en.wikipedia.org/wiki/Wikipedia:Text_of_Creative_Commons_Attribution-ShareAlike_3.0_Unported_License"
    }
  }
  ["rel_urls"]=>
  array(3) {
    ["http://en.wikipedia.org/wiki/crepe"]=>
    array(2) {
      ["text"]=>
      string(5) "crepe"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
    ["http://example.com/crepe"]=>
    array(2) {
      ["text"]=>
      string(24) "http://example.com/crepe"
      ["rels"]=>
      array(2) {
        [0]=>
        string(8) "bookmark"
        [1]=>
        string(4) "self"
      }
    }
    ["http://en.wikipedia.org/wiki/Wikipedia:Text_of_Creative_Commons_Attribution-ShareAlike_3.0_Unported_License"]=>
    array(2) {
      ["text"]=>
      string(47) "Creative Commons Attribution-ShareAlike License"
      ["rels"]=>
      array(1) {
        [0]=>
        string(7) "license"
      }
    }
  }
}
