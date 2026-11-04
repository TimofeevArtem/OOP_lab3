#pragma once
#include <iostream>

class Complex{
public:
    Complex();
    Complex(float re);
    Complex(float re, float im);
    Complex(const Complex &complex);
    Complex(Complex &&complex) noexcept;
    ~Complex(){}
    Complex& operator=(const Complex& other);

    bool operator==(const Complex& complex) const;
    bool operator>(const Complex& complex) const;
    bool operator<(const Complex& complex) const;
    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);

private:
    float re_;
    float im_;
};