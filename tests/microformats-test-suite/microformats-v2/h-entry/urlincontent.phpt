--TEST--
mf2: mf-test-suite: v2/h-entry/urlincontent
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/urlincontent.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(7) "h-entry"
    }
    ["properties"]=>
    array(2) {
      ["name"]=>
      array(1) {
        [0]=>
        string(34) "Expanding URLs within HTML content"
      }
      ["content"]=>
      array(1) {
        [0]=>
        array(2) {
          ["html"]=>
          string(578) "<ul>
            <li><a href="http://www.w3.org/">Should not change: http://www.w3.org/</a></li>
            <li><a href="http://example.com/">Should not change: http://example.com/</a></li>
            <li><a href="test.html">File relative: test.html = http://example.com/test.html</a></li>
            <li><a href="/test/test.html">Directory relative: /test/test.html = http://example.com/test/test.html</a></li>
            <li><a href="/test.html">Relative to root: /test.html = http://example.com/test.html</a></li>
        </ul>
        <img src="images/photo.gif">"
          ["value"]=>
          string(353) "Should not change: http://www.w3.org/
            Should not change: http://example.com/
            File relative: test.html = http://example.com/test.html
            Directory relative: /test/test.html = http://example.com/test/test.html
            Relative to root: /test.html = http://example.com/test.html
        
         images/photo.gif"
        }
      }
    }
  }
}
