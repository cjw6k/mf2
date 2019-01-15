# mf2

mf2 is an extension for PHP providing microformats2 parsing.

## Installation
T.B.D.

## Usage
* To parse microformats from HTML, use `$parse = mf2_parse($html, $url)`, where `$url` is the URL from which the `$html` was loaded, if any. This parameter is required for correct relative URL parsing and must not be left out unless parsing HTML which contains no relative URLs.
* To fetch HTML from a URL and parse microformats, use `mf2_fetch( $url )`
* To fetch HTML from a file and parse microformats, use `mf2_fetch( $file, $url )`, where `$file` is the full local path and filename, and `$url` is the URL from which the `$file` was loaded, if any.

### Fetch and Parse Microformats from a URI or Local File
```php
mf2_fetch ( string $uri [, string $base_url = null [, int $options = 0 ]] )
```

<dl>
    <dt>$uri</dt><dd>The Uniform Resource Identifier from which to load. May be a URL or local file.</dd>
    <dt>$base_url</dt><dd>The base URL to use when resolving relative links.</dd>
    <dt>$options</dt><dd>Options which control the HTML parsing context.</dd>
</dl>

### Parse Microformats from a String
```php
mf2_parse ( string $data [, string $base_url = null [, int $options = 0 ]] )
```

<dl>
    <dt>$data</dt><dd>The data from which to parse microformats.</dd>
    <dt>$base_url</dt><dd>The base URL to use when resolving relative links.</dd>
    <dt>$options</dt><dd>Options which control the HTML parsing context.</dd>
</dl>

## Advanced Usage
mf2 provides a parse via the `MF2Parse` class. 

```php
public MF2Parse::__construct ( string $data [, string $base_url = null [, bool $data_is_uri = false [, int $options = 0 ]]] )
```

Each of `mf2_fetch` and `mf2_parse` return an object of this class and each uses the same functions internally to produce the parse -equivalent to instantiating the MF2Parse directly with the correct options. You may extend and customize this class to suit your needs. 

### Examples
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

mf2 uses the HTML parser from libxml2. The following option flags are available where indicated in the 'mf2 Name' column (others are as-yet, not implemented):

mf2 Name | LibXML2 Name | Purpose
-------- | ------------ | -------
MF2_PARSE_RECOVER | HTML_PARSE_RECOVER | Relaxed parsing
n/a | HTML_PARSE_NODEFDTD | do not default a doctype if not found
MF2_PARSE_NOERROR | HTML_PARSE_NOERROR | suppress error reports
MF2_PARSE_NOWARNING | HTML_PARSE_NOWARNING | suppress warning reports
n/a | HTML_PARSE_PEDANTIC | pedantic error reporting
n/a | HTML_PARSE_NOBLANKS | remove blank nodes
n/a | HTML_PARSE_NONET | Forbid network access
n/a | HTML_PARSE_NOIMPLIED | Do not add implied html/body... elements
n/a | HTML_PARSE_COMPACT | compact small text nodes
n/a | HTML_PARSE_IGNORE_ENC | ignore internal document encoding hint
MF2_NONOTICE | - | Suppress notice messages that originate outside libxml
MF2_NOWARNING | - | Suppress warning messages that originate outside libxml
MF2_PARSE_HAPPY | - | Combines all available flags; mutes all the complaining

The default behaviour, with no options set:
```php
$parse = mf2_fetch( 'http://microformats.org' );
```

The above default behaviour is equivalent to specifying the MF2_PARSE_HAPPY convenience option:

```php
$parse = mf2_fetch( 'http://microformats.org', null, MF2_PARSE_HAPPY );
```

## Security
T.B.D.

## Benchmarks
T.B.D.

## Tests
T.B.D.

## Internal Structure and Organization
### File and function naming
mf2 is spread across several translation units, where `.c` and `.h` files typically occur together with matching names, e.g.: `mf2.c` and `mf2.h`, implying that they together compose one unit of compilation.

A PHP extension generally may contain functionality in three areas:
1. functions exposed to userland PHP.
2. functions that are registered with, called by and hook directly into the engine.
2. functions which are called from other functions within the extension, but never from the engine or from userland.

Note: Some extensions may further sub-divide (3), but this does not apply in the mf2 extension. 

With the above three segments as a guideline, mf2 spreads the functionality supporting each module (e.g. the MF2Parse class) across up-to three translation units. The segment that a given translation unit belongs to is indicated by a prefix on the filename.
1. any functions that are exposed to userland PHP are defined in translation units with a user\_ prefix.
2. any functions that hook into PHP directly for registration of callbacks, etc. are defined in translation units with a php\_ prefix.
3. any functions which support the other functions, and are not directly called by the engine or by userland, have no prefix.

#### Example
The following files are together, the full definition of the MF2Parse object:
```
mf2parse.c \________ Support functions (the stuff) __ 
mf2parse.h /                                          \
php_mf2parse.c \____ Engine hooks (housekeeping) _____ \ __ $parse = new MF2Parse();
php_mf2parse.h /                                       /
user_mf2parse.c \___ Userland functions (API) _______ /
user_mf2parse.h /
```

Additionally, to verbosely indicate the purpose of (2), all functions therein are prefixed with `php_`.


## Contributing
### Open Issues
<dl>
    <dt>How can I test the MF2_PARSE_NOWARNING option?</dt>
    <dd>See [[tests/025_mf2parse_option_MF2_PARSE_NOWARNING.phpt]]</dd>
    <dt>How can I test the MF2_PARSE_RECOVER option?</dt>
    <dd>See [[tests/026_mf2parse_option_MF2_PARSE_RECOVER.phpt]]</dd>    
</dl>

## Changelog
All notable changes to this project will be documented in [CHANGELOG.md](CHANGELOG.md).

## Acknowledgements
The community that is [IndieWeb](https://indieweb.org/)!
The community that is [Microformats](http://microformats.org/)!

## License
Copyright © `2019` `Christopher James Willcock`
 
mf2 is free software; you can redistribute it and/or modify it under the terms of the MIT License. See the [LICENSE.md](LICENSE.md) file for license rights and limitations (MIT).

Bundled within this software, inside the folder `./tests/microformats-test-suite/` are found tests authored by various individuals and released to the public domain (with much gratitude from this author). See the [LICENSE](tests/microformats-test-suite/LICENSE) file for usage rights and limitations which apply to their inclusion and use.
