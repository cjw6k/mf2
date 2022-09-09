#!/bin/bash
#set -euxo pipefail
set -euo pipefail

##
## This script will update all the microformats-test-suite tests in the tests/microformats-test-suite directory.
##
## Usage:
## - from the parent directory of the mf2 clone, e.g. if mf2 is cloned into php-src/ext/mf2, then from php-src/ext:
##   - clone the microformats/tests repo into microformats-test-suite, e.g. php-src/ext/microformats-test-suite
##   - run the script: mf2/ci/follow-microformats-test-suite.sh
##   - run the mf2 tests!
##

# stage 1 (before checkout)
[[ -f ./mf2/ci/microformats-test-suite-HEAD.sha ]] \
|| (echo "error: microformats test suite HEAD commit hash not found" && exit 1)

testSuiteCommitSha="$(git ls-remote https://github.com/microformats/tests HEAD | cut -f1)"
cmp \
  <(echo "$testSuiteCommitSha") \
  ./mf2/ci/microformats-test-suite-HEAD.sha \
&& echo "there are no new changes in the microformats test suite" && exit

# step2 (after checkout)
[[ -f ./microformats-test-suite/LICENSE ]] \
|| (echo "error: microformats test suite LICENSE not found" && exit 1)

cmp -s \
  <(sha1sum ./microformats-test-suite/LICENSE | cut -f1 -d' ') \
  ./mf2/ci/microformats-test-suite-LICENSE.sha \
|| (echo "error: microformats test suite LICENSE has been updated and must be manually verified" && exit 1)

tmp="$(mktemp)"
for json in ./microformats-test-suite/tests/*/*/*.json; do
  testName="$(basename "$json" .json)"
  testPath="$(dirname -- "$(realpath -- "$json")")"
  typeName="$(basename "$testPath")"
  typePath="$(dirname -- "$(realpath -- "$testPath")")"
  versionName="$(basename "$typePath")"

  mkdir -p "./mf2/tests/microformats-test-suite/$versionName/$typeName/"

  # merge HTML
  cp \
    "./microformats-test-suite/tests/$versionName/$typeName/$testName.html" \
    "./mf2/tests/microformats-test-suite/$versionName/$typeName/$testName.html"

  # reformat and merge JSON
  jq --sort-keys --indent 4 . "$json" > "$tmp"
  mv "$tmp" "./mf2/tests/microformats-test-suite/$versionName/$typeName/$testName.json"

  # make a new mf2 test using the template if one does not exist
  if [[ ! -f "./mf2/tests/microformats-test-suite/$versionName/$typeName/$testName.phpt" ]]; then
    sed "s/{{ testName }}/$testName/" ./mf2/ci/mf2-test-for-microformats-test-suite.phpt-template \
    | sed "s/{{ typeName }}/$typeName/" \
    | sed "s/{{ versionName }}/$versionName/" \
    > "./mf2/tests/microformats-test-suite/$versionName/$typeName/$testName.phpt"
  fi
done

cp ./microformats-test-suite/README.md ./mf2/tests/microformats-test-suite/README.md

[[ ! -f ./mf2/tests/microformats-test-suite/LICENSE ]] \
&& cp ./microformats-test-suite/LICENSE ./mf2/tests/microformats-test-suite/LICENSE

echo "$testSuiteCommitSha" > ./mf2/ci/microformats-test-suite-HEAD.sha