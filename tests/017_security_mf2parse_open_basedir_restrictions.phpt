--TEST--
mf2: MF2Parse respects open_basedir restrictions
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

if(!file_exists(__DIR__ . '/basedir-test')){
	mkdir(__DIR__ . '/basedir-test');
}

var_dump(mf2_fetch(__DIR__ . '/empty_file.html') instanceof MF2Parse);

ini_set('open_basedir', __DIR__ . '/basedir-test');

mf2_fetch(__DIR__ . '/empty_file.html');
new MF2Parse(__DIR__ . '/empty_file.html', null, true);

?>
--CLEAN--
<?php

unlink(__DIR__ . '/basedir-test');

?>
--EXPECTF--
bool(true)

Warning: mf2_fetch(): I/O warning : failed to load external entity %s in %s on line %d

Warning: MF2Parse::__construct(): I/O warning : failed to load external entity %s in %s on line %d