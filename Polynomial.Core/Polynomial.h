#pragma once

//all math stuff
#include <cmath>
#include <complex>

//std containers
#include <vector>
#include <functional>

const double Pi = 3.1415926535;

typedef std::complex<double> cplx;

namespace Polynomial {
	namespace Core {

#ifdef VC9_PYTHON27
		class Polynomial
		{
		public:
			Polynomial() {}
			Polynomial(unsigned int _deg);
			void Create(unsigned int _deg);
			void ValidateRoots();

			struct RootsObject {
				RootsObject() {}
				RootsObject(Polynomial* _parent);
				int operator() ();
				Polynomial* parent;
				int (*func)(Polynomial*);
			};
			RootsObject FindRoots;
			int Degree;
			std::vector <cplx> Coefficients;
			std::vector <cplx> Roots;
			bool RootsCalculated;
			double ResultError;
			cplx Discriminant;
			cplx Delta;
			cplx Q;
		};
#else
		class Polynomial
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
#endif
	}
}




