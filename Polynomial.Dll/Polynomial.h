#pragma once

#ifdef POLYNOMIAL_NOLIB
#define POLYNOMIAL_API
#else
#ifdef POLYNOMIAL_EXPORTS
#define POLYNOMIAL_API __declspec(dllexport)
#else
#define POLYNOMIAL_API __declspec(dllimport)
#endif
#endif

//all math stuff
#include <cmath>
#include <complex>

//std containers
#include <vector>
#include <functional>

const double Pi = 3.1415926535;

using cplx = std::complex<double>;

enum class PolyType : int { NotDefined = -1, Constant = 0, Linear = 1, Quadratic = 2, Cubic = 3, Quartic = 4, Any };
enum class CreateArg : unsigned int { Coefficients, Roots };

namespace Polynomial {
    namespace Dll {
        class POLYNOMIAL_API Polynomial
        {
        public:
            void Create(unsigned int _deg);

            void ValidateRoots();

            std::function<void()> FindRoots{ nullptr };

            int Degree{ -1 };
            std::vector <cplx> Coefficients;
            std::vector <cplx> Roots;


            bool RootsCalculated{ false };

            cplx Discriminant;
            cplx Delta;
            cplx Q;
            double ResultError{ DBL_MAX };
        };
    }
}


