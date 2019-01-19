--TEST--
mf2: mf-test-suite: v2/rel/duplicate-rels
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/duplicate-rels.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(2) {
    [0]=>
    object(MF2Microformat)#2 (2) {
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
          string(4) "Matt"
        }
        ["url"]=>
        array(1) {
          [0]=>
          string(28) "http://ma.tt/author/saxmatt/"
        }
      }
    }
    [1]=>
    object(MF2Microformat)#3 (2) {
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
          string(4) "Matt"
        }
        ["url"]=>
        array(1) {
          [0]=>
          string(28) "http://ma.tt/author/saxmatt/"
        }
      }
    }
  }
  ["rels"]=>
  array(4) {
    ["bookmark"]=>
    array(2) {
      [0]=>
      string(43) "http://ma.tt/2015/05/beethoven-mozart-bach/"
      [1]=>
      string(43) "http://ma.tt/2015/06/jefferson-on-idleness/"
    }
    ["category"]=>
    array(1) {
      [0]=>
      string(29) "http://ma.tt/category/asides/"
    }
    ["tag"]=>
    array(1) {
      [0]=>
      string(29) "http://ma.tt/category/asides/"
    }
    ["author"]=>
    array(1) {
      [0]=>
      string(28) "http://ma.tt/author/saxmatt/"
    }
  }
  ["rel_urls"]=>
  array(4) {
    ["http://ma.tt/2015/05/beethoven-mozart-bach/"]=>
    array(3) {
      ["title"]=>
      string(36) "Permalink to Beethoven, Mozart, Bach"
      ["text"]=>
      string(14) "
May 31, 2015"
      ["rels"]=>
      array(1) {
        [0]=>
        string(8) "bookmark"
      }
    }
    ["http://ma.tt/category/asides/"]=>
    array(2) {
      ["text"]=>
      string(6) "Asides"
      ["rels"]=>
      array(2) {
        [0]=>
        string(8) "category"
        [1]=>
        string(3) "tag"
      }
    }
    ["http://ma.tt/author/saxmatt/"]=>
    array(3) {
      ["title"]=>
      string(22) "View all posts by Matt"
      ["text"]=>
      string(4) "Matt"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "author"
      }
    }
    ["http://ma.tt/2015/06/jefferson-on-idleness/"]=>
    array(3) {
      ["title"]=>
      string(34) "Permalink to Jefferson on Idleness"
      ["text"]=>
      string(12) "June 2, 2015"
      ["rels"]=>
      array(1) {
        [0]=>
        string(8) "bookmark"
      }
    }
  }
}