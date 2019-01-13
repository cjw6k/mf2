--TEST--
mf2: mf-test-suite: v2/rel/xfn-elsewhere
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/xfn-elsewhere.html'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(1) {
    ["me"]=>
    array(8) {
      [0]=>
      string(29) "http://twitter.com/glennjones"
      [1]=>
      string(35) "http://delicious.com/glennjonesnet/"
      [2]=>
      string(55) "https://plus.google.com/u/0/105161464208920272734/about"
      [3]=>
      string(36) "http://lanyrd.com/people/glennjones/"
      [4]=>
      string(28) "http://github.com/glennjones"
      [5]=>
      string(43) "http://www.flickr.com/photos/glennjonesnet/"
      [6]=>
      string(37) "http://www.linkedin.com/in/glennjones"
      [7]=>
      string(50) "http://www.slideshare.net/glennjones/presentations"
    }
  }
  ["rel_urls"]=>
  array(8) {
    ["http://twitter.com/glennjones"]=>
    array(2) {
      ["text"]=>
      string(7) "twitter"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
    ["http://delicious.com/glennjonesnet/"]=>
    array(2) {
      ["text"]=>
      string(9) "delicious"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
    ["https://plus.google.com/u/0/105161464208920272734/about"]=>
    array(2) {
      ["text"]=>
      string(7) "google+"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
    ["http://lanyrd.com/people/glennjones/"]=>
    array(2) {
      ["text"]=>
      string(6) "lanyrd"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
    ["http://github.com/glennjones"]=>
    array(2) {
      ["text"]=>
      string(6) "github"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
    ["http://www.flickr.com/photos/glennjonesnet/"]=>
    array(2) {
      ["text"]=>
      string(6) "flickr"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
    ["http://www.linkedin.com/in/glennjones"]=>
    array(2) {
      ["text"]=>
      string(8) "linkedin"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
    ["http://www.slideshare.net/glennjones/presentations"]=>
    array(2) {
      ["text"]=>
      string(10) "slideshare"
      ["rels"]=>
      array(1) {
        [0]=>
        string(2) "me"
      }
    }
  }
}