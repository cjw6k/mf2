--TEST--
mf2: mf-test-suite: v2/rel/rels-urls
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/rel-urls.html', null, true));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(4) {
    ["author"]=>
    array(2) {
      [0]=>
      string(20) "http://example.com/a"
      [1]=>
      string(20) "http://example.com/b"
    }
    ["in-reply-to"]=>
    array(2) {
      [0]=>
      string(20) "http://example.com/1"
      [1]=>
      string(20) "http://example.com/2"
    }
    ["alternate"]=>
    array(1) {
      [0]=>
      string(21) "http://example.com/fr"
    }
    ["home"]=>
    array(1) {
      [0]=>
      string(21) "http://example.com/fr"
    }
  }
  ["rel_urls"]=>
  array(5) {
    ["http://example.com/a"]=>
    array(2) {
      ["text"]=>
      string(8) "author a"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "author"
      }
    }
    ["http://example.com/b"]=>
    array(2) {
      ["text"]=>
      string(8) "author b"
      ["rels"]=>
      array(1) {
        [0]=>
        string(6) "author"
      }
    }
    ["http://example.com/1"]=>
    array(2) {
      ["text"]=>
      string(6) "post 1"
      ["rels"]=>
      array(1) {
        [0]=>
        string(11) "in-reply-to"
      }
    }
    ["http://example.com/2"]=>
    array(2) {
      ["text"]=>
      string(6) "post 2"
      ["rels"]=>
      array(1) {
        [0]=>
        string(11) "in-reply-to"
      }
    }
    ["http://example.com/fr"]=>
    array(4) {
      ["hreflang"]=>
      string(2) "fr"
      ["media"]=>
      string(8) "handheld"
      ["text"]=>
      string(22) "French mobile homepage"
      ["rels"]=>
      array(2) {
        [0]=>
        string(9) "alternate"
        [1]=>
        string(4) "home"
      }
    }
  }
}