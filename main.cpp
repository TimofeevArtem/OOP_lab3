#include <iostream>
#include <cstddef>
#include "complexSet.h"
#include "complex.h"

int main(){
    Complex complex1{};
    Complex complex2{1};
    Complex complex3{3, 4};
    std::cout <<  "1: " <<complex1 << std::endl;
    std::cout <<  "2: " <<complex2 << std::endl;
    std::cout <<  "3: " <<complex3 << std::endl;
    Complex complex4 = complex3;
    std::cout <<  "4: " <<complex4 << std::endl;
    Complex complex5 = std::move(complex3);
    std::cout <<  "5: " <<complex5 << std::endl;
    std::cout <<  "3: " <<complex3 << std::endl;
    std::cout << "4: " << complex4 << std::endl;
    std::cout << "1 == 2: " << (complex1 == complex2) << std::endl;
    std::cout << "4 == 5: " << (complex4 == complex5) << std::endl;
    std::cout << "4 > 5: " << (complex4 > complex5) << std::endl;
    std::cout << "5 > 4: " << (complex4 < complex5) << std::endl;
    std::cout << "1 > 2: " << (complex1 > complex2) << std::endl;
    std::cout << "2 > 1: " << (complex2 > complex1) << std::endl;
    std::cout << "1 < 2: " << (complex1 < complex2) << std::endl;

    std::cout << "__________"<< std::endl;
    ComplexSet set1{};
    std::cout << "1: " << set1 << std::endl;
}
