--TEST--
mf2: mf-test-suite: v1/hcard/multiple
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/multiple.html'));

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
        string(6) "h-card"
      }
      ["properties"]=>
      array(19) {
        ["name"]=>
        array(1) {
          [0]=>
          string(8) "John Doe"
        }
        ["given-name"]=>
        array(1) {
          [0]=>
          string(4) "John"
        }
        ["family-name"]=>
        array(1) {
          [0]=>
          string(3) "Doe"
        }
        ["sound"]=>
        array(1) {
          [0]=>
          string(34) "http://www.madgex.com/johndoe.mpeg"
        }
        ["photo"]=>
        array(1) {
          [0]=>
          array(2) {
            ["value"]=>
            string(35) "http://example.com/images/photo.gif"
            ["alt"]=>
            string(17) "Photo of John Doe"
          }
        }
        ["nickname"]=>
        array(2) {
          [0]=>
          string(16) "Man with no name"
          [1]=>
          string(8) "Lost boy"
        }
        ["note"]=>
        array(2) {
          [0]=>
          string(59) "John Doe is one of those names you always have issues with."
          [1]=>
          string(69) "It can be a real problem booking a hotel room with the name John Doe."
        }
        ["logo"]=>
        array(2) {
          [0]=>
          array(2) {
            ["value"]=>
            string(34) "http://example.com/images/logo.gif"
            ["alt"]=>
            string(19) "Madgex company logo"
          }
          [1]=>
          array(2) {
            ["value"]=>
            string(34) "http://example.com/images/logo.gif"
            ["alt"]=>
            string(27) "Web Feet Media company logo"
          }
        }
        ["url"]=>
        array(2) {
          [0]=>
          string(22) "http://www.madgex.com/"
          [1]=>
          string(28) "http://www.webfeetmedia.com/"
        }
        ["org"]=>
        array(2) {
          [0]=>
          string(6) "Madgex"
          [1]=>
          string(18) "Web Feet Media Ltd"
        }
        ["job-title"]=>
        array(2) {
          [0]=>
          string(17) "Creative Director"
          [1]=>
          string(5) "Owner"
        }
        ["category"]=>
        array(3) {
          [0]=>
          string(6) "design"
          [1]=>
          string(11) "development"
          [2]=>
          string(3) "web"
        }
        ["tel"]=>
        array(3) {
          [0]=>
          string(14) "+1 415 555 100"
          [1]=>
          string(14) "+1 415 555 200"
          [2]=>
          string(14) "+1 415 555 300"
        }
        ["email"]=>
        array(2) {
          [0]=>
          string(26) "mailto:john.doe@madgex.com"
          [1]=>
          string(32) "mailto:john.doe@webfeetmedia.com"
        }
        ["mailer"]=>
        array(2) {
          [0]=>
          string(14) "PigeonMail 2.1"
          [1]=>
          string(12) "Outlook 2007"
        }
        ["label"]=>
        array(2) {
          [0]=>
          string(98) "Work: 
                North Street, 
                Brighton, 
                United Kingdom"
          [1]=>
          string(97) "Home: 
                West Street, 
                Brighton, 
                United Kingdom"
        }
        ["adr"]=>
        array(2) {
          [0]=>
          object(MF2Microformat)#3 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(5) "h-adr"
            }
            ["properties"]=>
            array(3) {
              ["street-address"]=>
              array(1) {
                [0]=>
                string(12) "North Street"
              }
              ["locality"]=>
              array(1) {
                [0]=>
                string(8) "Brighton"
              }
              ["country-name"]=>
              array(1) {
                [0]=>
                string(14) "United Kingdom"
              }
            }
            ["value"]=>
            string(98) "Work: 
                North Street, 
                Brighton, 
                United Kingdom"
          }
          [1]=>
          object(MF2Microformat)#4 (3) {
            ["type"]=>
            array(1) {
              [0]=>
              string(5) "h-adr"
            }
            ["properties"]=>
            array(3) {
              ["street-address"]=>
              array(1) {
                [0]=>
                string(11) "West Street"
              }
              ["locality"]=>
              array(1) {
                [0]=>
                string(8) "Brighton"
              }
              ["country-name"]=>
              array(1) {
                [0]=>
                string(14) "United Kingdom"
              }
            }
            ["value"]=>
            string(97) "Home: 
                West Street, 
                Brighton, 
                United Kingdom"
          }
        }
        ["agent"]=>
        array(2) {
          [0]=>
          string(8) "Jane Doe"
          [1]=>
          object(MF2Microformat)#5 (3) {
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
                string(8) "Dave Doe"
              }
            }
            ["value"]=>
            string(8) "Dave Doe"
          }
        }
        ["key"]=>
        array(1) {
          [0]=>
          string(31) "hd02$Gfu*d%dh87KTa2=23934532479"
        }
      }
    }
  }
  ["rels"]=>
  array(1) {
    ["tag"]=>
    array(3) {
      [0]=>
      string(35) "http://en.wikipedia.org/wiki/design"
      [1]=>
      string(40) "http://en.wikipedia.org/wiki/development"
      [2]=>
      string(32) "http://en.wikipedia.org/wiki/web"
    }
  }
  ["rel_urls"]=>
  array(3) {
    ["http://en.wikipedia.org/wiki/design"]=>
    array(2) {
      ["text"]=>
      string(6) "design"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
    ["http://en.wikipedia.org/wiki/development"]=>
    array(2) {
      ["text"]=>
      string(11) "development"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
    ["http://en.wikipedia.org/wiki/web"]=>
    array(2) {
      ["text"]=>
      string(3) "web"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
  }
}
