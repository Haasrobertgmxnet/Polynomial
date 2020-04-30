#include "Polynomial.h"
#include "..\Polynomial.Core\Polynomial.h"
#include "..\Polynomial.Core\PolynomialRoots.h"

namespace Polynomial {
	namespace Dll {
		void Polynomial::Create(unsigned int _deg) {
			Degree = _deg;
			Coefficients.reserve(Degree + 1);
			Roots.reserve(Degree);
			if (Degree == 2) {
				FindRoots = [this]() { ::Polynomial::Core::PolynomialRoots::MidNightFormula(this); };
			}
			if (Degree == 3) {
				FindRoots = [this]() { ::Polynomial::Core::PolynomialRoots::CardanoMethod(this); };
			}
			if (Degree == 4) {
				FindRoots = [this]() { ::Polynomial::Core::PolynomialRoots::FerrariMethod(this); };
			}

			ValidateRoots = [this]() { ::Polynomial::Core::PolynomialRoots::ValidateRoots(this); };
			for (auto j = 0; j < Degree; ++j) {
				Coefficients.push_back(cplx(0.0, 0.0));
			}
			Coefficients.push_back(cplx(0.0, 0.0));
		}
	}
}
