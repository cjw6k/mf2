--TEST--
mf2: mf-test-suite: microformats-v2/h-card/relativeurls
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

require_once __DIR__ . '/../../../utils.inc';

echo testSuiteFormat(mf2_fetch(__DIR__ . '/relativeurls.html', 'http://example.com/'));

?>
--EXPECT_EXTERNAL--
relativeurls.json