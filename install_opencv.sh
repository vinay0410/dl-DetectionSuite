#!/bin/sh
if [ -n "$(ls -A opencv/build)" ];
 then
 	# We're using a cached version of our OpenCV build
 	cd opencv/build;
	sudo make install
 else
 	# No OpenCV cache – clone and make the files
 	rm -rf opencv;
	wget https://github.com/opencv/opencv/archive/3.4.2.zip
	unzip -q 3.4.2.zip
	cd opencv-3.4.2
	mkdir build && cd build
	cmake ..
	make -j4
	sudo make install
 fi

