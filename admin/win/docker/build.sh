#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: $(basename $0) directory_relative_to_home [uid]"
  exit
fi

useradd utvikling -u ${2:-1000}
su - utvikling << EOF
  cd /home/utvikling/$1
  rm -rf build-win32
  mkdir build-win32
  cd build-win32
  ../admin/win/download_runtimes.sh
  cmake .. -DCMAKE_TOOLCHAIN_FILE=../admin/win/Toolchain-mingw32-openSUSE.cmake -DWITH_CRASHREPORTER=ON
  make -j4
  make package
  ctest .
EOF
