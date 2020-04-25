#include "Polynomial.h"
#include "PolynomialRoots.h"

namespace Polynomial {
	namespace Core {
#ifdef VC9_PYTHON27
#include <limits.h>
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
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

			Degree = -1;
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
			std::vector<cplx> z;
			z.reserve(4);
			for (unsigned int j = 0; j < Roots.size();j++) {
				z.push_back(Roots[j]);
			}
			z.resize(4);

			std::vector<cplx> w;
			w.reserve(8);
			w.push_back(0.0);
			w.push_back(0.0);
			w.push_back(0.0);
			for (unsigned int j = 0; j < Coefficients.size(); j++) {
				w.push_back(Coefficients[j]);
			}
			w.resize(8);

			//implement Vieta's theorem
			//std::_Vector_iterator<std::_Vector_val<std::_Simple_types<cplx>>> A = Coefficients.end() - 1;
			//typename std::iterator_traits<std::vector<cplx>>::value_type A = *(Coefficients.end() - 1;
			cplx A = Coefficients[Coefficients.size() - 1];
			cplx B = -(z[0] + z[1] + z[2] + z[3]);
			cplx C = +(z[0] * z[1] + z[0] * z[2] + z[0] * z[3]
				+ z[1] * z[2] + z[1] * z[3] + z[2] * z[3]);
			cplx D = -(z[0] * z[1] * z[2] +
				z[0] * z[1] * z[3] +
				z[0] * z[2] * z[3] +
				z[1] * z[2] * z[3]);
			cplx E = +(z[0] * z[1] * z[2] * z[3]);

			B = cplx(A.real(), A.imag()) * B;
			C = cplx(A.real(), A.imag()) * C;
			D = cplx(A.real(), A.imag()) * D;
			E = cplx(A.real(), A.imag()) * E;

			int ofs = Degree;
			ResultError = abs(w[ofs - 1] - E) + abs(w[ofs] - D) + abs(w[1 + ofs] - C) + abs(w[2 + ofs] - B);
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
		void Polynomial::ValidateRoots() {
			std::vector<cplx> z;
			z.reserve(4);
			for (auto elem : Roots) {
				z.emplace_back(elem);
			}
			z.resize(4);

			std::vector<cplx> w;
			w.reserve(8);
			w.emplace_back(0.0);
			w.emplace_back(0.0);
			w.emplace_back(0.0);
			for (auto elem : Coefficients) {
				w.emplace_back(elem);
			}
			w.resize(8);

			//implement Vieta's theorem
			auto A{ Coefficients.end() - 1 };
			auto B{ -(z.at(0) + z.at(1) + z.at(2) + z.at(3)) };
			auto C{ +(z.at(0) * z.at(1) + z.at(0) * z.at(2) + z.at(0) * z.at(3)
				+ z.at(1) * z.at(2) + z.at(1) * z.at(3) + z.at(2) * z.at(3)) };
			auto D{ -(z.at(0) * z.at(1) * z.at(2) +
				z.at(0) * z.at(1) * z.at(3) +
				z.at(0) * z.at(2) * z.at(3) +
				z.at(1) * z.at(2) * z.at(3)) };
			auto E{ +(z.at(0) * z.at(1) * z.at(2) * z.at(3)) };

			B = cplx(A->real(), A->imag()) * B;
			C = cplx(A->real(), A->imag()) * C;
			D = cplx(A->real(), A->imag()) * D;
			E = cplx(A->real(), A->imag()) * E;

			int ofs{ Degree };
			ResultError = abs(w.at(ofs - 1) - E) + abs(w.at(ofs) - D) + abs(w.at(1 + ofs) - C) + abs(w.at(2 + ofs) - B);
		}
#endif
	}
}
