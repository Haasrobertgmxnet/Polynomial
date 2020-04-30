#include <iostream>

#include "Polynomial.h"

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
        poly.Coefficients[4 - j].real(re);
        poly.Coefficients[4 - j].imag(im);
    }

    poly.FindRoots();
    poly.ValidateRoots();

    if (!poly.RootsCalculated) {
        std::cout << "Roots could not be calculated!" << std::endl;
        std::cout << "Program will end now" << std::endl;
        return -1;
    }
    std::cout << std::endl;
    std::cout << "Calculated Solutions" << std::endl;
    std::cout << "############################" << std::endl;
    std::cout << "Result Error: ";
    std::cout << poly.ResultError << std::endl;
    for (int j = 0; j < 4; ++j) {
        double re = poly.Roots[j].real();
        double im = poly.Roots[j].imag();
        std::cout << "############################" << std::endl;
        std::cout << "Solution " << 1+j << std::endl;
        std::cout << "----------------------------" << std::endl;
        std::cout << "Real Part: ";
        std::cout << re << std::endl;
        std::cout << "Imaginary Part: ";
        std::cout << im << std::endl;
    }

    std::cout << "End!\n";
}

