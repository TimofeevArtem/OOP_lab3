#include <iostream>
#include <cstddef>
#include <utility>
#include "complexSet.h"


ComplexSet::ComplexSet(){
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

ComplexSet::ComplexSet(const ComplexSet& set){
    size_ = set.size_;
    capacity_ = set.capacity_;
    data_ = new Complex[capacity_];
    for(int i = 0; i < size_; i++){
        data_[i] = set.data_[i];
    }
}

ComplexSet::ComplexSet(ComplexSet&& set) noexcept{
    size_ = set.size_;
    capacity_ = set.capacity_;
    data_ = set.data_;
    set.data_ = nullptr;
    set.size_ = 0;
    set.capacity_ = 0;
}

ComplexSet& ComplexSet::operator=(const ComplexSet& set){
    size_ = set.size_;
    capacity_ = set.capacity_;
    data_ = set.data_;
    return *this;
}

ComplexSet& ComplexSet::operator=(ComplexSet&& set){
    size_ = set.size_;
    capacity_ = set.capacity_;
    data_ = set.data_;
    set.data_ = nullptr;
    return *this;
}

ComplexSet::~ComplexSet(){
    delete[] data_;
}

bool ComplexSet::add(Complex complex){
    for(int i = 0; i < size_; i++){
        if(data_[i] == complex){
            return false;
        }
    }
    while(size_ >= capacity_){
        if(capacity_ == 0){
            capacity_ = 1;
        }
        else{
            capacity_ *= 2;
        }
    }
    Complex* new_data = new Complex[capacity_];
    int i = 0;
    while(data_[i] < complex && i < size_){
        new_data[i] = data_[i];
        i++;
    }
    new_data[i] = complex;
    while(i < size_){
        new_data[i + 1] = data_[i];
        i++;
    }
    delete[] data_;
    data_ = new_data;
    size_++;
    return true;
}

bool ComplexSet::remove(const Complex& complex){
    for(int i = 0; i < size_; i++){
        if(data_[i] == complex){
            for(int j = i; j < size_ - 1; j++){
                data_[j] = data_[j + 1];
            }
            size_--;
            return true;
        }
    }
    return false;
}

bool ComplexSet::contains(const Complex& complex) const{
    for(int i = 0; i < size_; i++){
        if(data_[i] == complex){
            return true;
        }
    }
    return false;
}

bool ComplexSet::operator()(const Complex& complex) const{
    return contains(complex);
}

std::size_t ComplexSet::size() const{
    return size_;
}

bool ComplexSet::empty() const{
    return size_ == 0;
}

ComplexSet ComplexSet::operator+=(const Complex& complex){
    add(complex);
    return *this;
}

ComplexSet ComplexSet::operator-=(const Complex& complex){
    remove(complex);
    return *this;
}

ComplexSet ComplexSet::operator|(const ComplexSet& set) const{
    ComplexSet result = *this;
    for(int i = 0; i < set.size_; i++){
        result.add(set.data_[i]);
    }
    return result;
}

ComplexSet ComplexSet::operator&(const ComplexSet& set) const{
    ComplexSet result;
    for(int i = 0; i < size_; i++){
        if(set.contains(data_[i])){
            result.add(data_[i]);
        }
    }
    return result;
}

ComplexSet ComplexSet::operator-(const ComplexSet& set) const{
    ComplexSet result;
    for(int i = 0; i < size_; i++){
        if(!set.contains(data_[i])){
            result.add(data_[i]);
        }
    }
    return result;
}

bool ComplexSet::operator==(const ComplexSet& set) const{
    if(size_ != set.size_){
        return false;
    }
    for(int i = 0; i < size_; i++){
        if(data_[i] != set.data_[i]){
            return false;
        }
    }
    return true;
}

bool ComplexSet::operator!=(const ComplexSet& set) const{
    return !(*this == set);
}

friend std::ostream& operator<<(std::ostream& os, const ComplexSet& set){
    os << "{";
    for(int i = 0; i < set.size_; i++){
        os << set.data_[i];
        if(i != set.size_ - 1){
            os << ", ";
        }
    }
    os << "}";
    return os;
}