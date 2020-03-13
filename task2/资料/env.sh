#!/bin/bash 
sudo apt-get install build-essential
sudo apt-get install libelf-dev
sudo apt-get install libncurses-dev
sudo apt-get install flex	#sudo make menuconfig        /bin/sh: 1: flex: not found
sudo apt-get install bison	#sudo make menuconfig       /bin/sh: 1: bison: not found
sudo apt-get install libssl-dev 	#sudo make -j2 scripts/sign-file.c:25:10: fatal error: openssl/opensslv.h: 没有那个文件或目录