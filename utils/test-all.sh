#!/usr/bin/env bash
(cd ../src && make clean && ./configure --enable-cross && make && make test && echo "ALL SEEMS TO BE GOOD!" && make clean)
