#pragma once
#include <iostream>
#include <cstddef>
#include <utility>
#include "complex.h"


class ComplexSet{
public:
    ComplexSet();
    ComplexSet(const ComplexSet& set);
    ComplexSet(ComplexSet&& set) noexcept;
    ComplexSet& operator=(const ComplexSet& set);
    ComplexSet& operator=(ComplexSet&& set);
    ~ComplexSet();

    bool add(Complex complex);
    bool remove(const Complex& complex);
    bool contains(const Complex& complex) const;
    bool operator()(const Complex& complex) const;

    std::size_t size() const;
    bool empty() const;

    ComplexSet operator+=(const Complex& complex);
    ComplexSet operator-=(const Complex& complex);

    ComplexSet operator|(const ComplexSet& set) const;
    ComplexSet operator&(const ComplexSet& set) const;
    ComplexSet operator-(const ComplexSet& set) const;

    bool operator==(const ComplexSet& set) const;
    bool operator!=(const ComplexSet& set) const;

    friend std::ostream& operator<<(std::ostream& os, const ComplexSet& set);
    
private:
    Complex* data_;
    std::size_t size_;
    std::size_t capacity_;
};