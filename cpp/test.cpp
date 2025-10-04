#include <bits/stdc++.h>
#include "poscode.hpp"
#include "utils.hpp"

static size_t count_lines(const std::string& path){
    std::ifstream in(path);
    size_t c=0; std::string s;
    while(in>>s) ++c;
    return c;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: ./test <archivo> [algoritmo]\n"
                  << "  algoritmo: radix | quick | merge (por defecto: radix)\n";
        return 1;
    }
    std::string filename = argv[1];
    std::string algo = (argc >= 3 ? argv[2] : "radix");

    size_t n = count_lines(filename);
    if (n == 0) { std::cerr << "Archivo vacío o no legible.\n"; return 1; }

    std::unique_ptr<Poscode[]> data(readCodes(filename, n));
    if (!data) { std::cerr << "No pude leer " << filename << "\n"; return 1; }

    auto t0 = std::chrono::steady_clock::now();
    if (algo == "radix")      radix_sort(data.get(), n);
    else if (algo == "quick") quick_sort(data.get(), n);
    else if (algo == "merge") merge_sort(data.get(), n);
    else { std::cerr << "Algoritmo desconocido.\n"; return 1; }
    auto t1 = std::chrono::steady_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "OK " << algo << " n=" << n << " tiempo=" << ms << " ms\n";

    // Muestra primeros 10 para validar visualmente
    for (size_t i = 0; i < std::min<size_t>(n,10); ++i)
        std::cout << data[i].getData() << "\n";
    return 0;
}

