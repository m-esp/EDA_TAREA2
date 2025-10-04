#pragma once
#include <vector>
#include "counting_sort.hpp"

// Radix LSD sobre 6 columnas (DDDDLL). Requiere un "getter" con firma:
//   int getter(int code_index, int p);   // p in [1..6]
template <typename Getter>
void radix_sort_indices(std::vector<int>& order, Getter getter) {
    // p = 6,5 con M=26 (letras), luego 4..1 con M=10 (dígitos)
    counting_sort_indices(order, 6, 26, getter);
    counting_sort_indices(order, 5, 26, getter);
    counting_sort_indices(order, 4, 10, getter);
    counting_sort_indices(order, 3, 10, getter);
    counting_sort_indices(order, 2, 10, getter);
    counting_sort_indices(order, 1, 10, getter);
}

