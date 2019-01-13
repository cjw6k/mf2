#Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Unreleased

### Added
- Space characters are trimmed from href attributes
- TEST: MF2Parse trim html space characters from href attributes
- TEST: mf-test-suite/v2/rel/xfn-elsewhere
- TEST: mf-test-suite/v2/rel/xfn-all
- TEST: mf-test-suite/v2/rel/varying-text-duplicate-rels
- TEST: mf-test-suite/v2/rel/rel-urls
- TEST: mf-test-suite/v2/rel/nofollow
- TEST: mf-test-suite/v2/rel/license
- Tests derived from the [microformats-test-suite](https://github.com/microformats/tests)
- MF2Parse has read property handler
- TEST: property access 2, with non-empty properties for rels & rel-urls
- MF2Parse, parses rel-urls
- MF2Parse, parses rels
- TEST: simple rel parsing
- Using HTMLParser from libxml with default options: HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING
- Added dependency on libxml extension for PHP
- TEST: MF2Parse encoded as JSON matches microformats2-json canonical output
- MF2Parse implements jsonSerializeable interface
- TEST: MF2Parse alternative access for rel-urls
- MF2Parse rel_urls property may be accessed as relurls, rel_urls or given $key = 'rel-urls', as $key
- TEST: MF2Parse property access
- TEST: MF2Parse empty file
- TEST: MF2Parse empty code string
- Initialize/destroy/free items, rels and relurls
- TEST: MF2Parse debug info includes required microformats elements (items, rels, relurls)
- TEST: mf2_parse returns MF2Parse object
- mf2_parse convenience function
- TEST: mf2_fetch returns MF2Parse object
- mf2_fetch convenience function
- TEST: MF2Parse may not be cloned
- Usage notes and Examples in [README.md](README.md)
- Test MF2Parse constructor
- The MF2Parse object
- MF2_STR convenience method, registers strings used in various places on module startup, and frees these strings on shutdown.
- TEST: MF2Parse class exists
- TEST: phpinfo() includes mf2 status
- TEST: mf2 extension is loaded
- Minimal PHP extension config
- This CHANGELOG.md to track what's happening with this software.
- An altogether too brief [README.md](README.md).
- Licensed (MIT) this work, see [LICENSE.md](LICENSE.md) for details.
