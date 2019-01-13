--TEST--
mf2: mf-test-suite: v2/rel/xfn-all
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/xfn-all.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(17) {
    ["friend"]=>
    array(1) {
      [0]=>
      string(31) "http://example.com/profile/jane"
    }
    ["acquaintance"]=>
    array(1) {
      [0]=>
      string(30) "http://example.com/profile/jeo"
    }
    ["contact"]=>
    array(1) {
      [0]=>
      string(31) "http://example.com/profile/lily"
    }
    ["met"]=>
    array(1) {
      [0]=>
      string(33) "http://example.com/profile/oliver"
    }
    ["co-worker"]=>
    array(1) {
      [0]=>
      string(32) "http://example.com/profile/emily"
    }
    ["colleague"]=>
    array(1) {
      [0]=>
      string(31) "http://example.com/profile/jack"
    }
    ["neighbor"]=>
    array(1) {
      [0]=>
      string(35) "http://example.com/profile/isabella"
    }
    ["child"]=>
    array(1) {
      [0]=>
      string(32) "http://example.com/profile/harry"
    }
    ["parent"]=>
    array(1) {
      [0]=>
      string(33) "http://example.com/profile/sophia"
    }
    ["sibling"]=>
    array(1) {
      [0]=>
      string(34) "http://example.com/profile/charlie"
    }
    ["spouse"]=>
    array(1) {
      [0]=>
      string(33) "http://example.com/profile/olivia"
    }
    ["kin"]=>
    array(1) {
      [0]=>
      string(32) "http://example.com/profile/james"
    }
    ["muse"]=>
    array(1) {
      [0]=>
      string(30) "http://example.com/profile/ava"
    }
    ["crush"]=>
    array(1) {
      [0]=>
      string(33) "http://example.com/profile/joshua"
    }
    ["date"]=>
    array(1) {
      [0]=>
      string(32) "http://example.com/profile/chloe"
    }
    ["sweetheart"]=>
    array(1) {
      [0]=>
      string(32) "http://example.com/profile/alfie"
    }
    ["me"]=>
    array(1) {
      [0]=>
      string(31) "http://example.com/profile/isla"
    }
  }
  ["rel_urls"]=>
  array(17) {
    ["http://example.com/profile/jane"]=>
    array(2) {
      ["text"]=>
      string(4) "jane"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "friend"
      }
    }
    ["http://example.com/profile/jeo"]=>
    array(2) {
      ["text"]=>
      string(3) "jeo"
      ["rels"]=>
      array(1) {
        [0]=>
        string(12) "acquaintance"
      }
    }
    ["http://example.com/profile/lily"]=>
    array(2) {
      ["text"]=>
      string(4) "lily"
      ["rels"]=>
      array(1) {
        [0]=>
        string(7) "contact"
      }
    }
    ["http://example.com/profile/oliver"]=>
    array(2) {
      ["text"]=>
      string(6) "oliver"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "met"
      }
    }
    ["http://example.com/profile/emily"]=>
    array(2) {
      ["text"]=>
      string(5) "emily"
      ["rels"]=>
      array(1) {
        [0]=>
        string(9) "co-worker"
      }
    }
    ["http://example.com/profile/jack"]=>
    array(2) {
      ["text"]=>
      string(4) "jack"
      ["rels"]=>
      array(1) {
        [0]=>
        string(9) "colleague"
      }
    }
    ["http://example.com/profile/isabella"]=>
    array(2) {
      ["text"]=>
      string(8) "isabella"
      ["rels"]=>
      array(1) {
        [0]=>
        string(8) "neighbor"
      }
    }
    ["http://example.com/profile/harry"]=>
    array(2) {
      ["text"]=>
      string(5) "harry"
      ["rels"]=>
      array(1) {
        [0]=>
        string(5) "child"
      }
    }
    ["http://example.com/profile/sophia"]=>
    array(2) {
      ["text"]=>
      string(6) "sophia"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "parent"
      }
    }
    ["http://example.com/profile/charlie"]=>
    array(2) {
      ["text"]=>
      string(7) "charlie"
      ["rels"]=>
      array(1) {
        [0]=>
        string(7) "sibling"
      }
    }
    ["http://example.com/profile/olivia"]=>
    array(2) {
      ["text"]=>
      string(6) "olivia"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "spouse"
      }
    }
    ["http://example.com/profile/james"]=>
    array(2) {
      ["text"]=>
      string(5) "james"
      ["rels"]=>
      array(1) {
        [0]=>
        string(3) "kin"
      }
    }
    ["http://example.com/profile/ava"]=>
    array(2) {
      ["text"]=>
      string(3) "ava"
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "muse"
      }
    }
    ["http://example.com/profile/joshua"]=>
    array(2) {
      ["text"]=>
      string(6) "joshua"
      ["rels"]=>
      array(1) {
        [0]=>
        string(5) "crush"
      }
    }
    ["http://example.com/profile/chloe"]=>
    array(2) {
      ["text"]=>
      string(5) "chloe"
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "date"
      }
    }
    ["http://example.com/profile/alfie"]=>
    array(2) {
      ["text"]=>
      string(5) "alfie"
      ["rels"]=>
      array(1) {
        [0]=>
        string(10) "sweetheart"
      }
    }
    ["http://example.com/profile/isla"]=>
    array(2) {
      ["text"]=>
      string(4) "isla"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
  }
}