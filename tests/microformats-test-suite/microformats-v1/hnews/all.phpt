--TEST--
mf2: mf-test-suite: v1/hnews/all
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/all.html'));

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
        string(6) "h-news"
      }
      ["properties"]=>
      array(5) {
        ["entry"]=>
        array(1) {
          [0]=>
          object(MF2Microformat)#3 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(7) "h-entry"
            }
            ["properties"]=>
            array(6) {
              ["name"]=>
              array(1) {
                [0]=>
                string(21) "microformats.org at 7"
              }
              ["url"]=>
              array(1) {
                [0]=>
                string(56) "http://microformats.org/2012/06/25/microformats-org-at-7"
              }
              ["content"]=>
              array(1) {
                [0]=>
                array(2) {
                  ["html"]=>
                  string(627) "<p class="entry-summary">Last week the microformats.org community 
                celebrated its 7th birthday at a gathering hosted by Mozilla in 
                San Francisco and recognized accomplishments, challenges, and 
                opportunities.</p>

            <p>The microformats tagline “humans first, machines second” 
                forms the basis of many of our 
                <a href="http://microformats.org/wiki/principles">principles</a>, and 
                in that regard, we’d like to recognize a few people and 
                thank them for their years of volunteer service </p>"
                  ["value"]=>
                  string(536) "Last week the microformats.org community 
                celebrated its 7th birthday at a gathering hosted by Mozilla in 
                San Francisco and recognized accomplishments, challenges, and 
                opportunities.

            The microformats tagline “humans first, machines second” 
                forms the basis of many of our 
                principles, and 
                in that regard, we’d like to recognize a few people and 
                thank them for their years of volunteer service"
                }
              }
              ["summary"]=>
              array(1) {
                [0]=>
                string(235) "Last week the microformats.org community 
                celebrated its 7th birthday at a gathering hosted by Mozilla in 
                San Francisco and recognized accomplishments, challenges, and 
                opportunities."
              }
              ["updated"]=>
              array(1) {
                [0]=>
                string(19) "2012-06-25T17:08:26"
              }
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
                      string(6) "Tantek"
                    }
                    ["url"]=>
                    array(1) {
                      [0]=>
                      string(18) "http://tantek.com/"
                    }
                  }
                  ["value"]=>
                  string(6) "Tantek"
                }
              }
            }
            ["value"]=>
            string(21) "microformats.org at 7"
          }
        }
        ["dateline"]=>
        array(1) {
          [0]=>
          object(MF2Microformat)#5 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(6) "h-card"
            }
            ["properties"]=>
            array(1) {
              ["adr"]=>
              array(1) {
                [0]=>
                object(MF2Microformat)#6 (3) {
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
                      string(13) "San Francisco"
                    }
                    ["region"]=>
                    array(1) {
                      [0]=>
                      string(2) "CA"
                    }
                  }
                  ["value"]=>
                  string(35) "San Francisco, 
                CA"
                }
              }
            }
            ["value"]=>
            string(35) "San Francisco, 
                CA"
          }
        }
        ["geo"]=>
        array(1) {
          [0]=>
          object(MF2Microformat)#7 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(5) "h-geo"
            }
            ["properties"]=>
            array(0) {
            }
            ["value"]=>
            string(21) "37.774921;-122.445202"
          }
        }
        ["source-org"]=>
        array(1) {
          [0]=>
          object(MF2Microformat)#8 (3) {
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
                string(16) "microformats.org"
              }
              ["org"]=>
              array(1) {
                [0]=>
                string(16) "microformats.org"
              }
              ["url"]=>
              array(1) {
                [0]=>
                string(24) "http://microformats.org/"
              }
            }
            ["value"]=>
            string(16) "microformats.org"
          }
        }
        ["principles"]=>
        array(1) {
          [0]=>
          string(59) "http://microformats.org/wiki/Category:public_domain_license"
        }
      }
    }
  }
  ["rels"]=>
  array(2) {
    ["bookmark"]=>
    array(1) {
      [0]=>
      string(56) "http://microformats.org/2012/06/25/microformats-org-at-7"
    }
    ["principles"]=>
    array(1) {
      [0]=>
      string(59) "http://microformats.org/wiki/Category:public_domain_license"
    }
  }
  ["rel_urls"]=>
  array(2) {
    ["http://microformats.org/2012/06/25/microformats-org-at-7"]=>
    array(2) {
      ["text"]=>
      string(21) "microformats.org at 7"
      ["rels"]=>
      array(1) {
        [0]=>
        string(8) "bookmark"
      }
    }
    ["http://microformats.org/wiki/Category:public_domain_license"]=>
    array(2) {
      ["text"]=>
      string(17) "Publishing policy"
      ["rels"]=>
      array(1) {
        [0]=>
        string(10) "principles"
      }
    }
  }
}
