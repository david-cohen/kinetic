#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Linting files"
find /usr/local/src/osd/src \( -name "*.hpp" -o -name "*.cpp" \) -type f | grep -v pb | xargs python $DIR/cpplint.py --root=src --header-guard-prefix=KINETIC_CPP_CLIENT --filter=-build/include,-whitespace/comments,-readability/streams,-runtime/references,-readability/casting,-runtime/arrays,-runtime/printf
find /usr/local/src/osd/include \( -name "*.hpp" -o -name "*.cpp" \) -type f | grep -v pb | xargs python $DIR/cpplint.py --root=src --header-guard-prefix=KINETIC_CPP_CLIENT --filter=-build/include,-whitespace/comments,-readability/streams,-runtime/references,-readability/casting,-runtime/arrays,-runtime/printf
find /usr/local/src/osd/test \( -name "*.hpp" -o -name "*.cpp" \) -type f | grep -v pb | xargs python $DIR/cpplint.py --root=src --header-guard-prefix=KINETIC_CPP_CLIENT --filter=-build/include,-whitespace/comments,-readability/streams,-runtime/references,-readability/casting,-runtime/arrays,-runtime/printf
