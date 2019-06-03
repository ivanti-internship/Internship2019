#!/bin/bash
clang -c sqlite3.c
clang++ -std=c++14 -c DtabaseUtil.cpp
clang++ -std=c++14 -c pch.cpp
clang++ -std=c++14 -c TreeNode.cpp
clang++ -std=c++14 -c TreeReaders.cpp
clang++ -std=c++14 -c TreeWriters.cpp
clang++ -std=c++14 -c TreeAppCoreC++.cpp
clang++ -std=c++14 DtabaseUtil.o pch.o TreeNode.o TreeReaders.o TreeWriters.o sqlite3.o TreeAppCoreC++.o -o main
