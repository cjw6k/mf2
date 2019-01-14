--TEST--
mf2: MF2Parse accepts MF2_NOWARNING option
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

echo "Base URL parameter needed to resolve relative URI - it's not set, so it's going to complain";
$parse = mf2_parse('<link rel="me" href="/">', null, 0);
var_dump($parse instanceof MF2Parse);

echo "Passing MF2_NOWARNING mutes those\n";
$parse = mf2_parse('<link rel="me" href="/">', null, MF2_NOWARNING);
var_dump($parse instanceof MF2Parse);

?>
--EXPECTF--
Base URL parameter needed to resolve relative URI - it's not set, so it's going to complain
Warning: mf2_parse(): Absolute base URL is not set, but is required to resolve a relative HTML <base> in %s on line %d
bool(true)
Passing MF2_NOWARNING mutes those
bool(true)
