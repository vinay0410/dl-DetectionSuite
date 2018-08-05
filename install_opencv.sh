git clone --single-branch -b 3.4 https://github.com/opencv/opencv.git
git branch
mkdir build && cd build
cmake ..
make -j${nproc}
sudo make install
