--TEST--
mf2: MF2Parse properties have the normal access pattern (2 - non-empty rels / rel-urls)
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

$parse = new MF2Parse('<link rel="me" href="http://example.com/">');

var_dump(!empty($parse->rels));
var_dump($parse->rels);

$key = 'rel-urls';
var_dump(!empty($parse->rel_urls));

var_dump($parse->rel_urls);
echo $parse->rel_urls['http://example.com/']['rels'][0], "\n";

var_dump($parse->relurls);
echo $parse->rel_urls['http://example.com/']['rels'][0], "\n";

var_dump($parse->$key);
echo $parse->$key['http://example.com/']['rels'][0], "\n";

?>
--EXPECT--
bool(true)
array(1) {
  ["me"]=>
  array(1) {
    [0]=>
    string(19) "http://example.com/"
  }
}
bool(true)
array(1) {
  ["http://example.com/"]=>
  array(1) {
    ["rels"]=>
    array(1) {
      [0]=>
      string(2) "me"
    }
  }
}
me
array(1) {
  ["http://example.com/"]=>
  array(1) {
    ["rels"]=>
    array(1) {
      [0]=>
      string(2) "me"
    }
  }
}
me
array(1) {
  ["http://example.com/"]=>
  array(1) {
    ["rels"]=>
    array(1) {
      [0]=>
      string(2) "me"
    }
  }
}
me
