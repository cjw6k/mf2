# mf2

mf2 is an extension for PHP providing microformats2 parsing.

## Installation
T.B.D.

## Usage
mf2 provides a parse via the class `MF2Parse`. 

```php
public MF2Parse::__construct ( string $data [, string $base_url = null [, bool $data_is_url = FALSE [, int $options = 0 ]]] )
```

* To parse microformats from HTML, use `$parse = new MF2Parse($html, $url)`, where `$url` is the URL from which the `$html` was loaded, if any. This parameter is required for correct relative URL parsing and must not be left out unless parsing HTML which contains no relative URLs.
* To fetch HTML from a URL and parse microformats, use `new MF2Parse( $url, null, true )`
* To load HTML from a file and parse microformats, use `new MF2Parse( $file, $url, true )`, where `$file` is the full local path and filename, and `$url` is the URL from which the `$file` was loaded, if any.
 
## Examples
```php
$parse = MF2Parse( '<main class="h-feed"><article class="h-entry"> … </article> … </main>' );
```
__Specifying the Base URL__

For data which includes relative URLs, a `base URL` should be provided in the second argument:
```php
$parse = MF2Parse( '<link rel="me" href="/">', 'http://example.com' );
```

The base URL must be an absolute URL. Providing a relative URL as base URL will throw an exception:
```php
// This is wrong
$parse = MF2Parse( '<link rel="me" href="/">', 'example.com' );

// Outputs:

Fatal error: Uncaught Exception: Base URL must be absolute in …
```

__Parse a URL or Local File__

The third argument in the MF2Parse constructor is set to indicate that the data provided is a URL or a local filename. Set this to true and the data argument will be interpreted appropriately.
```php
$parse = MF2Parse( '/tmp/index.html', 'http://example.com', true );
```

If the data argument is a URL, the second argument is unused while the given URL in the data parameter is used to determine the base URL automatically. Set the base_url parameter to null:
```php
$parse = MF2Parse( 'http://microformats.org', null, true );
```

__Parsing Options__

mf2 uses the HTML parser from libxml2. The following option flags are available internally and will soon be made available to userland:

mf2 Name | LibXML2 Name | Integer Value | Purpose
-------- | ------------ | ------------- | -------
n/a | HTML_PARSE_RECOVER | 1 | Relaxed parsing
n/a | HTML_PARSE_NODEFDTD | 4 | do not default a doctype if not found
n/a | HTML_PARSE_NOERROR | 32 | suppress error reports
n/a | HTML_PARSE_NOWARNING | 64 | suppress warning reports
n/a | HTML_PARSE_PEDANTIC | 128 | pedantic error reporting
n/a | HTML_PARSE_NOBLANKS | 256 | remove blank nodes
n/a | HTML_PARSE_NONET | 2048 | Forbid network access
n/a | HTML_PARSE_NOIMPLIED | 8192 | Do not add implied html/body... elements
n/a | HTML_PARSE_COMPACT | 65535 | compact small text nodes
n/a | HTML_PARSE_IGNORE_ENC | 209<span></span>7152 | ignore internal document encoding hint

For immediate use, the integer values of these option flags may be or'd together and provided as the fourth parameter in the constructor:
```php
$parse = new MF2Parse( 'http://microformats.org', null, true, 1 | 32 | 64 );
```

The above `$options` could have been provided as the integer `97` to indicate the same configuration, namely `HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING`.

## Security
T.B.D.

## Benchmarks
T.B.D.

## Tests
T.B.D.

## Contributing
T.B.D.

## Changelog
All notable changes to this project will be documented in [CHANGELOG.md](CHANGELOG.md).

## Acknowledgements
The community that is [IndieWeb](https://indieweb.org/)!

## License
Copyright © `2019` `Christopher James Willcock`
 
mf2 is free software; you can redistribute it and/or modify it under the terms of the MIT License. See the [LICENSE.md](LICENSE.md) file for license rights and limitations (MIT).
