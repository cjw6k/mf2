--TEST--
mf2: mf-test-suite: v1/hfeed/simple
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/simple.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(1) {
    [0]=>
    object(MF2Microformat)#2 (3) {
      ["type"]=>
      array(1) {
        [0]=>
        string(6) "h-feed"
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
        ["url"]=>
        array(1) {
          [0]=>
          string(28) "http://microformats.org/blog"
        }
        ["photo"]=>
        array(1) {
          [0]=>
          string(10) "photo.jpeg"
        }
        ["category"]=>
        array(2) {
          [0]=>
          string(12) "microformats"
          [1]=>
          string(4) "html"
        }
      }
      ["children"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#4 (2) {
          ["type"]=>
          array(1) {
            [0]=>
            string(7) "h-entry"
          }
          ["properties"]=>
          array(5) {
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
                string(604) "<p class="entry-summary">Last week the microformats.org community 
	            celebrated its 7th birthday at a gathering hosted by Mozilla in 
	            San Francisco and recognized accomplishments, challenges, and 
	            opportunities.</p>
	
	        <p>The microformats tagline “humans first, machines second” 
	            forms the basis of many of our 
	            <a href="http://microformats.org/wiki/principles">principles</a>, and 
	            in that regard, we’d like to recognize a few people and 
	            thank them for their years of volunteer service </p>"
                ["value"]=>
                string(513) "Last week the microformats.org community 
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
              string(226) "Last week the microformats.org community 
	            celebrated its 7th birthday at a gathering hosted by Mozilla in 
	            San Francisco and recognized accomplishments, challenges, and 
	            opportunities."
            }
            ["updated"]=>
            array(1) {
              [0]=>
              object(DateTime)#5 (4) {
                ["value"]=>
                string(19) "2012-06-25T17:08:26"
                ["date"]=>
                string(26) "2012-06-25 17:08:26.000000"
                ["timezone_type"]=>
                int(3)
                ["timezone"]=>
                string(3) "UTC"
              }
            }
          }
        }
      }
    }
  }
  ["rels"]=>
  array(2) {
    ["tag"]=>
    array(2) {
      [0]=>
      string(17) "tags/microformats"
      [1]=>
      string(9) "tags/html"
    }
    ["bookmark"]=>
    array(1) {
      [0]=>
      string(56) "http://microformats.org/2012/06/25/microformats-org-at-7"
    }
  }
  ["rel_urls"]=>
  array(3) {
    ["tags/microformats"]=>
    array(2) {
      ["text"]=>
      string(12) "microformats"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
    ["tags/html"]=>
    array(2) {
      ["text"]=>
      string(4) "html"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
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
  }
}
