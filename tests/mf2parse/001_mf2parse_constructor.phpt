--TEST--
mf2: MF2Parse has a __construct method
--SKIPIF--
<?php
    if (!extension_loaded("mf2")) die("skip");
    if (PHP_VERSION_ID >= 80000) die("skip PHP < 8.0 only");
?>
--FILE--
<?php

// First parameter is required
try{
	$parse = new MF2Parse();
} catch (Exception $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

// Null is unacceptable in the data parameter position
try{
	$parse = new MF2Parse(null);
} catch (TypeError $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

// Arrays are not permitted data
try{
	$parse = new MF2Parse(array());
} catch (TypeError $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

// Objects are not permitted data
try{
	$parse = new MF2Parse(new stdClass());
} catch (TypeError $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

$parse = new MF2Parse('<html></html>');
var_dump($parse instanceof MF2Parse);

// Check that null can be passed to any nullable param
// string $data, ?string base_url, ?bool $data_is_uri, ?int $options
$parse = new MF2Parse('<html></html>', null, null, null);
var_dump($parse instanceof MF2Parse);

// Arrays are not a base_url
try{
	$parse = new MF2Parse('<html></html>', array());
} catch (TypeError $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

// Objects are not a base_url
try{
	$parse = new MF2Parse('<html></html>', new stdClass());
} catch (TypeError $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

// Non-well-formed URLs are not a base_url
try{
	$parse = new MF2Parse('<html></html>', "http://:80");
} catch (Exception $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

// base_url must be an absolute URL
try{
	$parse = new MF2Parse('<html></html>', 'example.com');
} catch (Exception $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

$parse = new MF2Parse('<html></html>', 'http://example.com/');
var_dump($parse instanceof MF2Parse);

// Arrays are not a data_is_uri (bool)
try{
	$parse = new MF2Parse('<html></html>', null, array());
} catch (TypeError $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

// Objects are not a data_is_uri (bool)
try{
	$parse = new MF2Parse('<html></html>', null, new stdClass());
} catch (TypeError $e){
	echo get_class($e), ': ', $e->getMessage(), "\n";
}

$filename = tempnam("/tmp", "phpt");

$parse = new MF2Parse($filename, 'http://example.com/', true);
var_dump($parse instanceof MF2Parse);

unlink($filename);

// slows down the tests, and shouldn't be mixed with offline tests anyway
// -- scenario is covered in 018_security_mf2parse_allow_url_fopen_restrictions
//$parse = new MF2Parse('http://microformats.org', null, true);
//var_dump($parse instanceof MF2Parse);

?>
--EXPECTF--
Exception: Data parameter is required
TypeError: Argument 1 passed to MF2Parse::__construct() must be of the type string%s
TypeError: Argument 1 passed to MF2Parse::__construct() must be of the type string%s
TypeError: Argument 1 passed to MF2Parse::__construct() must be of the type string%s
bool(true)
bool(true)
TypeError: Argument 2 passed to MF2Parse::__construct() must be of the type string%s
TypeError: Argument 2 passed to MF2Parse::__construct() must be of the type string%s
Exception: Invalid base URL
Exception: Base URL must be absolute
bool(true)
TypeError: Argument 3 passed to MF2Parse::__construct() must be of the type bool%s
TypeError: Argument 3 passed to MF2Parse::__construct() must be of the type bool%s
bool(true)