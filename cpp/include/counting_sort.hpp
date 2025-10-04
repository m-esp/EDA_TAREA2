#pragma once
#include <vector>
#include "linked_list.hpp"

// Interfaz genérica: ordena ESTABLEMENTE el vector de índices `order`
// según la columna `p` del código (1..6). El rango M es:
//   - M = 26 para p = 5,6 (letras)
//   - M = 10 para p = 1..4 (dígitos)
//
// El "getter" es una función/funtor con firma:
//   int getter(int code_index, int p);
// que retorna el valor en [0..M-1] para la columna p del código con índice code_index.
template <typename Getter>
void counting_sort_indices(std::vector<int>& order, int p, int M, Getter getter) {
    std::vector< LinkedList<int> > buckets(M);

    // Distribución estable (en el orden actual de `order`)
    for (int idx : order) {
        int v = getter(idx, p); // 0..M-1
        buckets[v].push_back(idx);
    }

    // Recolección
    std::size_t k = 0;
    for (int b = 0; b < M; ++b) {
        for (auto it = buckets[b].begin(); it != buckets[b].end(); ++it) {
            order[k++] = *it;
        }
        buckets[b].clear();
    }
}

