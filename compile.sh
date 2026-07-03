#!/bin/bash

/usr/local/bin/g++-15.2.0 -std=c++20 -fmodules-ts -c -x c++-system-header $(cat syslibs.txt)
/usr/local/bin/g++-15.2.0 -std=c++20 -fmodules-ts -Wall -g $(cat order.txt)