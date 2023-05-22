#!/bin/bash

if [[ $# -eq 0 ]] ; then
    echo 'no argument'
    exit 0
fi

cd `dirname $0`
mkdir $(dirname $1)
cp .template.cpp source/$2.cpp
echo "add_executable($1 $2.cpp)" >> source/CMakeLists.txt