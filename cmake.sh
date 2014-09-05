#!/bin/bash

# if any command fails, bash will exit with a non-zero exit code
set -e

case $1 in
    "setup")
        cmake -H. -Bbuild
        ;;
    "debug")
        cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug
        ;;
    "clean")
        echo "removing build/, libgamelogic.a and test_executable"
        rm -rf build libgamelogic.a test_executable
        ;;
    "test")
        ./test_executable
        ;;
    *)
        make -C build $1
        ;;
esac

if [ $# -gt 1 ]
    then
        shift
        ./cmake.sh $*
fi
