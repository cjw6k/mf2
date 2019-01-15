--TEST--
mf2: relative URLs are converted to absolute URLs, using HTML base if available
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

// Relative URL encountered with no base set results in a warning
mf2_parse('<a rel="test" href="/">', null, 0);
new MF2Parse('<a rel="test" href="/">', null, null, 0);

// Base provided in constructor
echo (mf2_parse('<a rel="test" href="/">', 'http://example.com/', 0))->rels['test'][0], "\n";
echo (new MF2Parse('<a rel="test" href="/">', 'http://example.com/', null, 0))->rels['test'][0], "\n";

// Base provided in HTML5 base tag
echo (mf2_parse('<base href="http://example.net/"><a rel="test" href="/"></a>', null, 0))->rels['test'][0], "\n";
echo (new MF2Parse('<base href="http://example.net/"><a rel="test" href="/"></a>', null, null, 0))->rels['test'][0], "\n";

// Base in HTML5 tag has priority
echo (mf2_parse('<base href="http://example.net/"><a rel="test" href="/"></a>', 'http://example.com/', 0))->rels['test'][0], "\n";
echo (new MF2Parse('<base href="http://example.net/"><a rel="test" href="/"></a>', 'http://example.com/', null, 0))->rels['test'][0], "\n";

// Base in HTML5 tag may be relative
echo (mf2_parse('<base href="/htmlbase/"><a rel="test" href="relative/"></a>', 'http://example.com/', 0))->rels['test'][0], "\n";
echo (new MF2Parse('<base href="/htmlbase/"><a rel="test" href="relative/"></a>', 'http://example.com/', null, 0))->rels['test'][0], "\n";

// Invalid base URL in HTML tag generates a notice
mf2_parse('<html><head><base href="http://:80"></head></html>', null, 0);
new MF2Parse('<html><head><base href="http://:80"></head></html>', null, null, 0);


?>
--EXPECTF--
Warning: mf2_parse(): Absolute base URL is not set, but is required to resolve a relative HTML <base> in %s on line %d

Warning: MF2Parse::__construct(): Absolute base URL is not set, but is required to resolve a relative HTML <base> in %s on line %d
http://example.com/
http://example.com/
http://example.net/
http://example.net/
http://example.net/
http://example.net/
http://example.com/htmlbase/relative/
http://example.com/htmlbase/relative/

Notice: mf2_parse(): Parsed document includes an invalid <base> URL in %s on line %d

Notice: MF2Parse::__construct(): Parsed document includes an invalid <base> URL in %s on line %d