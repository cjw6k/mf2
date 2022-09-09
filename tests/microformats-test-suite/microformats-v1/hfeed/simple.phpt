--TEST--
mf2: mf-test-suite: microformats-v1/hfeed/simple
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

require_once __DIR__ . '/../../../utils.inc';

echo testSuiteFormat(mf2_fetch(__DIR__ . '/simple.html', 'http://example.com/'));

?>
--EXPECT_EXTERNAL--
simple.json
