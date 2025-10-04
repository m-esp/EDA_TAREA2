#include "poscode.hpp"
#include <utility>

Poscode::Poscode() : data("") {}
Poscode::Poscode(std::string _data) : data(std::move(_data)) {}

char Poscode::getValue(size_t i) const {
    return data[i]; // asume largo correcto (DDDDLL). Valida si quieres.
}

const std::string& Poscode::getData() const {
    return data;
}

