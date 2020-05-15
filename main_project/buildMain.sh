#!/bin/bash

cmake -Bbuild -H.
cd build
make
cp LTS_V2 ../LTS_V2
cd ../