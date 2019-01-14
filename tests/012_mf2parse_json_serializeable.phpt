--TEST--
mf2: MF2Parse implements json serializeable interface to provide microformats2-JSON output
--SKIPIF--
<?php if (!extension_loaded("mf2")) die("skip"); if(!extension_loaded("json")) die("skip json extension unavailable"); ?> 
--FILE--
<?php

echo json_encode(new MF2Parse(''), JSON_PRETTY_PRINT);

?>
--EXPECT--
{
    "items": [],
    "rels": {},
    "rel-urls": {}
}
