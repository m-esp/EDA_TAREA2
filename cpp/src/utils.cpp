#include <bits/stdc++.h>
#include "utils.hpp"
#include "linked_list.hpp"
#include "poscode.hpp"

// ---- Helpers ----
static inline int key_at(const Poscode& code, size_t p) {
    const char ch = code.getValue(p); // p = 0..5
    if (p <= 3) {
        if (ch < '0' || ch > '9')
            throw std::runtime_error("Código inválido: dígito fuera de rango");
        return ch - '0';
    } else {
        char up = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        if (up < 'A' || up > 'Z')
            throw std::runtime_error("Código inválido: letra fuera de rango");
        return up - 'A';
    }
}
static inline int alpha_for(size_t p) { return (p <= 3) ? 10 : 26; }

// ---- CountingSort estable por columna p ----
static void counting_sort_pass(Poscode* A, size_t n, size_t p) {
    const int M = alpha_for(p);
    std::vector< LinkedList<size_t> > buckets(M);

    for (size_t i = 0; i < n; ++i) {
        const int v = key_at(A[i], p);
        buckets[v].push_back(i);
    }

    std::vector<Poscode> tmp;
    tmp.reserve(n);
    for (int b = 0; b < M; ++b) {
        for (auto it = buckets[b].begin(); it != buckets[b].end(); ++it)
            tmp.emplace_back(A[*it]);
        buckets[b].clear();
    }
    for (size_t i = 0; i < n; ++i) A[i] = std::move(tmp[i]);
}

// ---- Radix (LSD) DDDDLL ----
void radix_sort(Poscode* A, size_t n) {
    if (n == 0) return;
    counting_sort_pass(A, n, 5);
    counting_sort_pass(A, n, 4);
    counting_sort_pass(A, n, 3);
    counting_sort_pass(A, n, 2);
    counting_sort_pass(A, n, 1);
    counting_sort_pass(A, n, 0);
}

// ---- Comparador lexicográfico ----
struct PoscodeLess {
    bool operator()(const Poscode& a, const Poscode& b) const {
        return a.getData() < b.getData();
    }
};

// ---- QuickSort (usa std::sort) ----
void quick_sort(Poscode* A, size_t n) {
    if (n <= 1) return;
    std::sort(A, A + n, PoscodeLess{});
}

// ---- MergeSort estable ----
static void merge_range(Poscode* A, Poscode* aux, size_t l, size_t m, size_t r) {
    size_t i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (!PoscodeLess{}(A[j], A[i])) aux[k++] = A[i++];
        else aux[k++] = A[j++];
    }
    while (i <= m) aux[k++] = A[i++];
    while (j <= r) aux[k++] = A[j++];
    for (size_t t = l; t <= r; ++t) A[t] = aux[t];
}
static void mergesort_rec(Poscode* A, Poscode* aux, size_t l, size_t r) {
    if (l >= r) return;
    size_t m = l + (r - l) / 2;
    mergesort_rec(A, aux, l, m);
    mergesort_rec(A, aux, m + 1, r);
    merge_range(A, aux, l, m, r);
}
void merge_sort(Poscode* A, size_t n) {
    if (n <= 1) return;
    std::vector<Poscode> aux(n);
    mergesort_rec(A, aux.data(), 0, n - 1);
}

// ---- IO: leer/liberar ----
Poscode* readCodes(const std::string& strfile, size_t n) {
    std::ifstream in(strfile);
    if (!in) return nullptr;
    auto* arr = new Poscode[n];
    std::string s; size_t i = 0;
    while (i < n && (in >> s)) arr[i++] = Poscode(s);
    if (i < n) {
        auto* arr2 = new Poscode[i];
        for (size_t k = 0; k < i; ++k) arr2[k] = std::move(arr[k]);
        delete[] arr; return arr2;
    }
    return arr;
}
void deleteCodes(Poscode* codes) { delete[] codes; }

