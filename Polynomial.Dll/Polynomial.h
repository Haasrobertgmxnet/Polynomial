#pragma once

#include <functional>
#include <vector>
#include <complex>

//#include "..\Polynomial.Core\Polynomial.h"

#ifdef POLYNOMIAL_EXPORTS
#define POLYNOMIAL_API __declspec(dllexport)
#else
#define POLYNOMIAL_API __declspec(dllimport)
#endif

using cplx = std::complex<double>;

namespace Polynomial {
    namespace Dll {
		class POLYNOMIAL_API Polynomial
		{
		public:
			void Create(unsigned int _deg);

			std::function<void()> FindRoots{ nullptr };
			std::function<void()> ValidateRoots{ nullptr };

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

