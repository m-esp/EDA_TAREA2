#include <bits/stdc++.h>
#include "poscode.hpp"
#include "utils.hpp"

using Clock = std::chrono::steady_clock;

static size_t count_lines(const std::string& path){
    std::ifstream in(path);
    size_t c=0; std::string s;
    while(in>>s) ++c;
    return c;
}
static std::vector<Poscode> read_all(const std::string& path){
    size_t n = count_lines(path);
    std::vector<Poscode> v; v.reserve(n);
    std::ifstream in(path); std::string s;
    while(in>>s) v.emplace_back(s);
    return v;
}
static long long time_ms(void(*fn)(Poscode*, size_t), std::vector<Poscode> base){
    auto t0 = Clock::now();
    fn(base.data(), base.size());
    auto t1 = Clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
}
static std::pair<double,double> mean_std(const std::vector<long long>& t){
    double m=0; for (auto x:t) m+=x; m/=t.size();
    double v=0; for (auto x:t) v+=(x-m)*(x-m); v/=t.size();
    return {m, std::sqrt(v)};
}

int main(int argc, char** argv){
    std::vector<std::string> files;
    if (argc>=2){
        for(int i=1;i<argc;++i) files.emplace_back(argv[i]);
    } else {
        files = {"codes_500K.txt","codes_1M.txt","codes_10M.txt"};
    }

    struct Algo { const char* name; void(*fn)(Poscode*, size_t); } algos[] = {
        {"Radix", radix_sort},
        {"Quick", quick_sort},
        {"Merge", merge_sort},
    };

    std::cout << "== Benchmarks (5 repeticiones, tiempo en ms) ==\n";
    for (auto& f : files){
        auto base = read_all(f);
        if (base.empty()){ std::cerr << "No pude leer " << f << "\n"; continue; }
        std::cout << "\nArchivo: " << f << "  (n=" << base.size() << ")\n";
        std::cout << "Algoritmo      μ ± σ   [runs]\n";

        for (auto& a : algos){
            std::vector<long long> runs;
            for (int r=0;r<5;++r){
                auto copy = base; // copia para no ordenar ya ordenados
                runs.push_back(time_ms(a.fn, std::move(copy)));
            }
            auto [mu, sigma] = mean_std(runs);
            std::cout << std::left << std::setw(10) << a.name
                      << "  " << std::fixed << std::setprecision(1)
                      << mu << " ± " << sigma
                      << "   ";
            for (auto x : runs) std::cout << x << " ";
            std::cout << "\n";
        }
    }
    return 0;
}

