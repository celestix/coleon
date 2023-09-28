@echo off
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
.\coleon.exe help