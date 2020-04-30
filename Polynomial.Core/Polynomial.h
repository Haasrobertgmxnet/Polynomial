#pragma once

#include <cmath>
#include <complex>
#include <vector>

typedef std::complex<double> cplx;

namespace Polynomial {
	namespace Core {
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
	}
}

#include "PolynomialRoots.h"

#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif

namespace Polynomial {
	namespace Core {
		Polynomial::RootsObject::RootsObject(Polynomial* _parent)
		{
			parent = _parent;
			if (parent->Degree == 2) {
				func = &PolynomialRoots::MidNightFormula;
			}
			if (parent->Degree == 3) {
				func = &PolynomialRoots::CardanoMethod;
			}
			if (parent->Degree == 4) {
				func = &PolynomialRoots::FerrariMethod;
			}
		}
		int Polynomial::RootsObject::operator() () { return func(parent); }

		Polynomial::Polynomial(unsigned int _deg) {
			Create(_deg);
		}

		void Polynomial::Create(unsigned int _deg) {
			Degree = _deg;
			Coefficients.reserve(Degree + 1);
			Roots.reserve(Degree);

			RootsCalculated = false;
			ResultError = DBL_MAX;
			RootsObject ro(this);
			FindRoots = ro;

			for (int j = 0; j < Degree; ++j) {
				Coefficients.push_back(cplx(0.0, 0.0));
			}
			Coefficients.push_back(cplx(0.0, 0.0));
		}

		void Polynomial::ValidateRoots() {
			PolynomialRoots::ValidateRoots(this);
		}
	}
}



