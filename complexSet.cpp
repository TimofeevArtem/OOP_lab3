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
    for(std::size_t i = 0; i < size_; i++){
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
    ComplexSet temp(set);

    std::swap(data_, temp.data_);
    std::swap(size_, temp.size_);
    std::swap(capacity_, temp.capacity_);
    return *this;
}

ComplexSet& ComplexSet::operator=(ComplexSet&& set) noexcept{
    if(this != &set){
        delete[] data_;

        data_ = set.data_;
        size_ = set.size_;
        capacity_ = set.capacity_;

        set.data_ = nullptr;
        set.size_ = 0;
        set.capacity_ = 0;
    }

    return *this;
}

ComplexSet::~ComplexSet(){
    delete[] data_;
}

bool ComplexSet::add(Complex complex){
    std::size_t i = 0;
    while(i < size_ && data_[i] < complex){
        i++;
    }

    if(i < size_ && data_[i] == complex){
        return false;
    }

    if(size_ == capacity_){
        if(capacity_ == 0){
            capacity_ = 1;
        }
        else{
            capacity_ *= 2;
        }

        Complex* new_data = new Complex[capacity_];

        for(std::size_t j = 0; j < i; j++){
            new_data[j] = data_[j];
        }

        new_data[i] = complex;

        for(std::size_t j = i; j < size_; j++){
            new_data[j + 1] = data_[j];
        }

        delete[] data_;
        data_ = new_data;
    }
    else{
        for(std::size_t j = size_; j > i; j--){
            data_[j] = data_[j - 1];
        }

        data_[i] = complex;
    }

    size_++;
    return true;
}

bool ComplexSet::remove(const Complex& complex){
    for(std::size_t i = 0; i < size_; i++){
        if(data_[i] == complex){
            for(std::size_t j = i; j < size_ - 1; j++){
                data_[j] = data_[j + 1];
            }
            size_--;
            return true;
        }
    }
    return false;
}

bool ComplexSet::contains(const Complex& complex) const{
    if(size_ == 0){
        return false;
    }

    std::size_t left = 0;
    std::size_t right = size_ - 1;

    while(left <= right){
        std::size_t mid = left + (right - left) / 2;

        if(data_[mid] == complex){
            return true;
        }
        else if(data_[mid] < complex){
            left = mid + 1;
        }
        else{
            if(mid == 0){
                return false;
            }
            right = mid - 1;
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

ComplexSet& ComplexSet::operator+=(const Complex& complex){
    add(complex);
    return *this;
}

ComplexSet& ComplexSet::operator-=(const Complex& complex){
    remove(complex);
    return *this;
}

ComplexSet ComplexSet::operator|(const ComplexSet& set) const{
    ComplexSet result;
    std::size_t i = 0;
    std::size_t j = 0;

    while(i < size_ && j < set.size_){
        if(data_[i] < set.data_[j]){
            result.add(data_[i]);
            i++;
        }
        else if(set.data_[j] < data_[i]){
            result.add(set.data_[j]);
            j++;
        }
        else{
            result.add(data_[i]);
            i++;
            j++;
        }
    }

    while(i < size_){
        result.add(data_[i]);
        i++;
    }

    while(j < set.size_){
        result.add(set.data_[j]);
        j++;
    }

    return result;
}

ComplexSet ComplexSet::operator&(const ComplexSet& set) const{
    ComplexSet result;
    std::size_t i = 0;
    std::size_t j = 0;

    while(i < size_ && j < set.size_){
        if(data_[i] < set.data_[j]){
            i++;
        }
        else if(set.data_[j] < data_[i]){
            j++;
        }
        else{
            result.add(data_[i]);
            i++;
            j++;
        }
    }

    return result;
}

ComplexSet ComplexSet::operator-(const ComplexSet& set) const{
    ComplexSet result;
    std::size_t i = 0;
    std::size_t j = 0;

    while(i < size_ && j < set.size_){
        if(data_[i] < set.data_[j]){
            result.add(data_[i]);
            i++;
        }
        else if(set.data_[j] < data_[i]){
            j++;
        }
        else{
            i++;
            j++;
        }
    }

    while(i < size_){
        result.add(data_[i]);
        i++;
    }

    return result;
}

bool ComplexSet::operator==(const ComplexSet& set) const{
    if(size_ != set.size_){
        return false;
    }
    for(std::size_t i = 0; i < size_; i++){
        if (!(data_[i] == set.data_[i])){
            return false;
        }
    }
    return true;
}

bool ComplexSet::operator!=(const ComplexSet& set) const{
    return !(*this == set);
}

std::ostream& operator<<(std::ostream& os, const ComplexSet& set){
    os << "{";
    for(std::size_t i = 0; i < set.size_; i++){
        os << set.data_[i];
        if(i != set.size_ - 1){
            os << ", ";
        }
    }
    os << "}";
    return os;
}