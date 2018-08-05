#!/bin/sh
set -ex
wget https://github.com/opencv/opencv/archive/3.4.2.zip
unzip -q 3.4.2.zip
cd opencv-3.4.2
mkdir build && cd build
cmake ..
make -j4
sudo make install
