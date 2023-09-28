@echo off
mkdir build
cd build
cmake ..
make
.\coleon.exe help