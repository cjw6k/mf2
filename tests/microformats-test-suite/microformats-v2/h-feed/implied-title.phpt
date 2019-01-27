--TEST--
mf2: mf-test-suite: v2/h-feed/implied-title
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/implied-title.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (3) {
    ["type"]=>
    array(1) {
      [0]=>
      string(6) "h-feed"
    }
    ["properties"]=>
    array(0) {
    }
    ["children"]=>
    array(1) {
      [0]=>
      object(MF2Microformat)#3 (2) {
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
              string(609) "<p class="p-summary">Last week the microformats.org community 
		            celebrated its 7th birthday at a gathering hosted by Mozilla in 
		            San Francisco and recognized accomplishments, challenges, and 
		            opportunities.</p>
		
		        <p>The microformats tagline “humans first, machines second” 
		            forms the basis of many of our 
		            <a href="http://microformats.org/wiki/principles">principles</a>, and 
		            in that regard, we’d like to recognize a few people and 
		            thank them for their years of volunteer service </p>"
              ["value"]=>
              string(522) "Last week the microformats.org community 
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
            string(229) "Last week the microformats.org community 
		            celebrated its 7th birthday at a gathering hosted by Mozilla in 
		            San Francisco and recognized accomplishments, challenges, and 
		            opportunities."
          }
          ["updated"]=>
          array(1) {
            [0]=>
            object(DateTime)#4 (4) {
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
