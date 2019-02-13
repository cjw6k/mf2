--TEST--
issues: item roots are valid only within hreview and hreview-aggregate
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

echo count(mf2_parse('<div class="item"></div>')->items);

?>
--EXPECT--
0
