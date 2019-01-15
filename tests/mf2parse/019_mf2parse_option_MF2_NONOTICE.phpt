--TEST--
mf2: MF2Parse accepts MF2_NONOTICE option
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

echo "HTML <base> href attribute needs to be a valid url, or a notice will be generated about it";
$parse = mf2_parse('<base href="http://:80">', null, 0);
var_dump($parse instanceof MF2Parse);

echo "Passing MF2_NONOTICE mutes those\n";
$parse = mf2_parse('<base href="http://:80">', null, MF2_NONOTICE);
var_dump($parse instanceof MF2Parse);

?>
--EXPECTF--
HTML <base> href attribute needs to be a valid url, or a notice will be generated about it
Notice: mf2_parse(): Parsed document includes an invalid <base> URL in %s on line %d
bool(true)
Passing MF2_NONOTICE mutes those
bool(true)
