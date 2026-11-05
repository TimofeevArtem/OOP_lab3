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
    std::cout << "1 size: " << set1.size() << std::endl;
    set1.add(complex1);
    std::cout << "1: " << set1 << std::endl;
    set1.add(complex2);
    std::cout << "1: " << set1 << std::endl;
    ComplexSet set2{set1};
    std::cout << "2: " << set2 << std::endl;
    ComplexSet set3{std::move(set1)};
    std::cout << "3: " << set3 << std::endl;
    std::cout << "1: " << set1 << std::endl;
    ComplexSet set4 = set3;
    std::cout << "4: " << set4 << std::endl;
    set4.remove(complex1);
    std::cout << "4: " << set4 << std::endl;
    std::cout << "c1 in 4?: " << set4.contains(complex1) << std::endl;
    set4 += complex1;
    std::cout << "c1 in 4?: " << set4.contains(complex1) << std::endl;
    set4 -= complex1;
    std::cout << "c1 in 4?: " << set4.contains(complex1) << std::endl;
    std::cout << "3: " << set3 << std::endl;
    std::cout << "4: " << set4 << std::endl;
    ComplexSet set5 = set3 | set4;
    std::cout << "5: " << set5 << std::endl;
    ComplexSet set6 = set3 & set4;
    std::cout << "6: " << set6 << std::endl;
    ComplexSet set7 = set3 - set4;
    std::cout << "7: " << set7 << std::endl;
    std::cout << "3: " << set3 << std::endl;
    std::cout << "4: " << set4 << std::endl;
    std::cout << "3 == 4: " << (set3 == set4) << std::endl;
    std::cout << "3 != 4: " << (set3 != set4) << std::endl;
    std::cout << "5: " << set5 << std::endl;
    std::cout << "3 == 5: " << (set3 == set5) << std::endl;
    std::cout << "3 != 5: " << (set3 != set5) << std::endl;

}
