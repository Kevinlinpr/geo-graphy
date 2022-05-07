mkdir -p build
mkdir -p encode/build
cd ./encode/build
cmake ..
make 
cp libencode.so ../lib/libencode.so
cd ../../build
cmake ..
make 