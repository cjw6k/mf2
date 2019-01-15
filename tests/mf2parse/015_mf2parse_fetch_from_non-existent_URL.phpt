--TEST--
mf2: MF2Parse fetch and parse from a non-existent URL
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; if (getenv("SKIP_ONLINE_TESTS")) { die('skip online test'); } ?> 
--FILE--
<?php

$url = 'http://' .  substr(md5(rand()), 0, 7) . '.' .  substr(md5(rand()), 0, 20) . '.' .  substr(md5(rand()), 0, 20) .  substr(md5(rand()), 0, 20) . '.localdomain';

$parse = new MF2Parse($url, null, true);
var_dump($parse instanceof MF2Parse);
var_dump($parse);

?>
--EXPECTF--
Warning: MF2Parse::__construct(): php_network_getaddresses: getaddrinfo failed: Name or service not known in %s on line %d

Warning: MF2Parse::__construct(%s): failed to open stream: php_network_getaddresses: getaddrinfo failed: Name or service not known in %s on line %d

Warning: MF2Parse::__construct(): I/O warning : failed to load external entity %s in %s on line %d
bool(true)
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}