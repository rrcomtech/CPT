#!/bin/bash

if [[ $# -eq 0 ]] ; then
    echo 'no argument'
    exit 0
fi

mkdir source/$(dirname $2)
cp .template.cpp source/$2.cpp
echo "add_executable($1 $2.cpp)" >> source/CMakeLists.txt