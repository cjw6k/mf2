--TEST--
mf2: mf-test-suite: v1/hresume/skill
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/skill.html'));

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
        string(8) "h-resume"
      }
      ["properties"]=>
      array(3) {
        ["contact"]=>
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
                string(15) "Tim Berners-Lee"
              }
            }
            ["value"]=>
            string(15) "Tim Berners-Lee"
          }
        }
        ["summary"]=>
        array(1) {
          [0]=>
          string(27) "invented the World Wide Web"
        }
        ["skill"]=>
        array(3) {
          [0]=>
          string(19) "information systems"
          [1]=>
          string(8) "advocacy"
          [2]=>
          string(10) "leadership"
        }
      }
    }
  }
  ["rels"]=>
  array(1) {
    ["tag"]=>
    array(3) {
      [0]=>
      string(44) "http://example.com/skills/informationsystems"
      [1]=>
      string(34) "http://example.com/skills/advocacy"
      [2]=>
      string(36) "http://example.com/skills/leadership"
    }
  }
  ["rel_urls"]=>
  array(3) {
    ["http://example.com/skills/informationsystems"]=>
    array(2) {
      ["text"]=>
      string(19) "information systems"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
    ["http://example.com/skills/advocacy"]=>
    array(2) {
      ["text"]=>
      string(8) "advocacy"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
    ["http://example.com/skills/leadership"]=>
    array(2) {
      ["text"]=>
      string(10) "leadership"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "tag"
      }
    }
  }
}
