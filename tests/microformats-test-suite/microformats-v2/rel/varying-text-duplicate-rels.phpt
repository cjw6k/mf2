--TEST--
mf2: mf-test-suite: microformats-v2/rel/varying-text-duplicate-rels
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

require_once __DIR__ . '/../../../utils.inc';

echo testSuiteFormat(mf2_fetch(__DIR__ . '/varying-text-duplicate-rels.html', 'http://example.com/'));

?>
--EXPECT_EXTERNAL--
varying-text-duplicate-rels.json
