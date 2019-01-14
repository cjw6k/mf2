--TEST--
mf2: MF2Parse respects allow_url_fopen restrictions
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--INI--
allow_url_fopen=0
--FILE--
<?php

mf2_fetch('http://microformats.org/');
new MF2Parse('http://microformats.org/', null, true);

?>
--EXPECTF--
Warning: mf2_fetch(): http:// wrapper is disabled in the server configuration by allow_url_fopen=0 in %s on line %d

Warning: mf2_fetch(%s): failed to open stream: no suitable wrapper could be found in %s on line %d

Warning: mf2_fetch(): I/O warning : failed to load external entity %s in %s on line %d

Warning: MF2Parse::__construct(): http:// wrapper is disabled in the server configuration by allow_url_fopen=0 in %s on line %d

Warning: MF2Parse::__construct(%s): failed to open stream: no suitable wrapper could be found in %s on line %d

Warning: MF2Parse::__construct(): I/O warning : failed to load external entity %s in %s on line %d
