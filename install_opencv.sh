#!/bin/sh

which cmake
sudo which cmake
ls /usr/local

if [ -n "$(ls -A $HOME/opencv/build)" ];
 then
 	# We're using a cached version of our OpenCV build
 	cd $HOME/opencv/build;
	sudo env "PATH=$PATH" make install
 else
 	# No OpenCV cache – clone and make the files
 	rm -rf $HOME/opencv;
	wget https://github.com/opencv/opencv/archive/3.4.2.zip
	unzip -q 3.4.2.zip -d $HOME/
	mv $HOME/opencv-3.4.2 $HOME/opencv && cd $HOME/opencv
	mkdir build && cd build
	cmake -DWITH_GTK=OFF -DWITH_QT=ON ..
	make -j2
	sudo env "PATH=$PATH" make install
 fi
