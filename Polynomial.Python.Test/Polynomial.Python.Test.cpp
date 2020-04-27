#include <map>
#include <iostream>

#define VC9_PYTHON27
#include "C:\Users\Robert\source\repos\Polynomial\Polynomial.Core\Polynomial.h"


int main()
{
    Polynomial::Core::Polynomial poly;
    poly.Create(4);

    for (int j = 0; j < 5; ++j) {
        char c = static_cast<char>(65 + j);
        double re;
        double im;
        std::cout << c << ", Realteil: ";
        std::cin >> re;
        std::cout << c << ", Imaginaerteil: ";
        std::cin >> im;
        poly.Coefficients[4-j].real(re);
        poly.Coefficients[4-j].imag(im);
    }

    poly.FindRoots();

    if (!poly.RootsCalculated) {
        std::cout << "Roots could not be calculated!" << std::endl;
        std::cout << "Program will end now" << std::endl;
        return -1;
    }

    for (int j = 0; j < 4; ++j) {
        double re = poly.Roots[j].real();
        double im = poly.Roots[j].imag();
        std::cout << "Realteil: ";
        std::cout << re << std::endl;
        std::cout << "Imaginaerteil: ";
        std::cout << im << std::endl;
    }

    std::cout << "End!\n";
}
