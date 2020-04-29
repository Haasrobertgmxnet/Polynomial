#include "Polynomial.h"
#include "PolynomialRoots.h"
#include <iostream>

#ifdef VC9_PYTHON27
#include <limits.h>
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#endif

namespace Polynomial {
	namespace Core {
#ifdef VC9_PYTHON27
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

		
#else
		void Polynomial::Create(unsigned int _deg) {
			Degree = _deg;
			Coefficients.reserve(Degree + 1);
			Roots.reserve(Degree);
			if (Degree == 2) {
				FindRoots = [this]() { PolynomialRoots::MidNightFormula(this); };
			}
			if (Degree == 3) {
				FindRoots = [this]() { PolynomialRoots::CardanoMethod(this); };
			}
			if (Degree == 4) {
				FindRoots = [this]() { PolynomialRoots::FerrariMethod(this); };
			}

			for (auto j = 0; j < Degree; ++j) {
				Coefficients.push_back(cplx(0.0, 0.0));
			}
			Coefficients.push_back(cplx(0.0, 0.0));
		}

#endif

		void Polynomial::ValidateRoots() {
			if (RootsCalculated) {
				// This will store the Coefficients in reverse order
				// The leding coefficient is assumed to be 1 and not stored here
				std::vector<cplx> FlippedCoefficients;
				// But first, the calculated roots will be stored here
				// to apply Vieta's theorem
				for (std::vector<cplx>::iterator it = Roots.begin(); it != Roots.end();++it) {
					FlippedCoefficients.push_back(-1.0*(*it));
				}
				FlippedCoefficients = PolynomialRoots::Vieta(FlippedCoefficients);
				ResultError = 0.0;
				for (unsigned int j = 1; j <= FlippedCoefficients.size();++j) {
					unsigned int idx = FlippedCoefficients.size() - j;
					ResultError += abs(FlippedCoefficients[j - 1] - Coefficients[idx]);
				}
			}
		}
	}
}
