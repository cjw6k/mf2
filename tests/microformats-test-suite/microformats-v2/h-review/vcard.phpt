--TEST--
mf2: mf-test-suite: v2/h-review/vcard
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
      array(8) {
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
        ["reviewer"]=>
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
        ["reviewed"]=>
        array(1) {
          [0]=>
          string(10) "2005-04-18"
        }
        ["description"]=>
        array(1) {
          [0]=>
          array(2) {
            ["html"]=>
            string(580) "<p class="p-item h-card">
        <span class="p-name p-org">Crepes on Cole</span> is one of the best little 
        creperies in <span class="p-adr h-adr"><span class="p-locality">San Francisco</span></span>.
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
  array(1) {
    ["license"]=>
    array(1) {
      [0]=>
      string(107) "http://en.wikipedia.org/wiki/Wikipedia:Text_of_Creative_Commons_Attribution-ShareAlike_3.0_Unported_License"
    }
  }
  ["rel_urls"]=>
  array(1) {
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


