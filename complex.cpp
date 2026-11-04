#include <iostream>
#include <cstddef>
#include <utility>
#include "complex.h"


Complex::Complex(){
    this->re_ = 0;
    this->im_ = 0;
}

Complex::Complex(float re){
    this->re_ = re;
    this->im_ = 0;
}

Complex::Complex(float re, float im){
    this->re_ = re;
    this->im_ = im;
}

Complex::Complex(const Complex &complex){
    re_ = complex.re_;
    im_ = complex.im_;
}

Complex::Complex(Complex &&complex) noexcept{
    re_ = complex.re_;
    im_ = complex.im_;
    complex.re_ = 0;
    complex.im_ = 0;
}

Complex& Complex::operator=(Complex& other){
    swap(other);
    return *this;
}

bool Complex::operator==(const Complex& complex) const{
    if (re_ == complex.re_ && im_ == complex.im_){
        return true;
    }
    return false;
}

bool Complex::operator>(const Complex& complex) const{
    if (re_ > complex.re_){
        return true;
    }
    else if (re_ == complex.re_ && im_ > complex.im_){
        return true;
    }
    return false;
}

bool Complex::operator<(const Complex& complex) const{
    if (re_ < complex.re_){
        return true;
    }
    else if (re_ == complex.re_ && im_ < complex.im_){
        return true;
    }
    return false;
}
std::ostream& operator<<(std::ostream& os, const Complex& complex){
    os << complex.re_;
    if (complex.im_ >= 0){
        os << " + " << complex.im_ << "i";
    }
    else{
        os << " - " << -complex.im_ << "i";
    }

    return os;
}

void Complex::swap(Complex& other) noexcept{
    std::swap(re_, other.re_);
    std::swap(im_, other.im_);
}