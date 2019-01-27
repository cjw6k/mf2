--TEST--
mf2: mf-test-suite: v2/h-entry/summarycontent
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/summarycontent.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
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
          string(591) "<p class="p-summary">Last week the microformats.org community 
            celebrated its 7th birthday at a gathering hosted by Mozilla in 
            San Francisco and recognized accomplishments, challenges, and 
            opportunities.</p>

        <p>The microformats tagline “humans first, machines second” 
            forms the basis of many of our 
            <a href="http://microformats.org/wiki/principles">principles</a>, and 
            in that regard, we’d like to recognize a few people and 
            thank them for their years of volunteer service </p>"
          ["value"]=>
          string(504) "Last week the microformats.org community 
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
        string(223) "Last week the microformats.org community 
            celebrated its 7th birthday at a gathering hosted by Mozilla in 
            San Francisco and recognized accomplishments, challenges, and 
            opportunities."
      }
      ["updated"]=>
      array(1) {
        [0]=>
        object(DateTime)#3 (4) {
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
  }
}
