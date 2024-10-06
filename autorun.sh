chmod +x scripts/setup.sh

./scripts/setup.sh

cmake --build build --target clean

cmake -S . -B build

cd build

make

cd ..

./sandbox/Bin/Sandbox