#include "Polynomial.h"
#include "PolynomialRoots.h"

namespace Polynomial {
    namespace Dll {

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
    }
}
