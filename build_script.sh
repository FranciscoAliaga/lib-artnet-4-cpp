#! /bin/bash

<<<<<<< HEAD
rm -rf build/

=======
>>>>>>> 14f02c47d7122834b7acb25e6efdd5f4fa49c3bf
mkdir build
cd build

cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
make

cd ..