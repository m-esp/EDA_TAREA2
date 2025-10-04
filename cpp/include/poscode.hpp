#ifndef __POSCODE_HPP__
#define __POSCODE_HPP__

#include <string>

class Poscode {
private:
    std::string data;

public:
    Poscode();
    explicit Poscode(std::string _data);

    // const-correct
    char getValue(size_t i) const;
    const std::string& getData() const;
};

#endif

