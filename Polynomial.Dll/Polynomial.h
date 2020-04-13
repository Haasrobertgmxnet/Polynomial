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

enum class PolyType : unsigned int { Constant = 0, Linear = 1, Quadratic = 2, Cubic = 3, Quartic = 4, Any };
enum class CreateArg : unsigned int { Coefficients, Roots };

namespace Polynomial {
    namespace Dll {
        class POLYNOMIAL_API Polynomial
        {
        public:
            template<CreateArg arg>
            void Create(std::vector<cplx>);
            void CreateFromCoefficients(std::vector<cplx>);

            void ValidateRoots();

            std::vector <cplx> Coefficients;
            std::vector <cplx> Roots;
            PolyType Type{ PolyType::Any };
            std::function<void()> FindRoots{ nullptr };
            bool RootsCalculated{ false };

            cplx Discriminant;
            cplx Delta;
            cplx Q;
            double ResultError{ DBL_MAX };
        };
    }

}


