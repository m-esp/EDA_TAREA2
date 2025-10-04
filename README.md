Descargar codes: https://www.dropbox.com/scl/fi/ju7zgg4xellugvgfnuf74/poscodes.zip?rlkey=gl8ju4rxiv2yp3tud1pgnydw3&e=1&st=0xddcjk6 y coloca los archivos en cpp/

sudo apt update
sudo apt install -y build-essential cmake

Compilación: 
cd cpp
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

Benchmarks con 5 reps: 
cd cpp/build
./bench ../codes_500K.txt ../codes_1M.txt ../codes_10M.txt

