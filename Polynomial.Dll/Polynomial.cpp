#include "Polynomial.h"

#include <array>
#include <iostream>

namespace Polynomial {
    namespace Dll {
        namespace PolynomialRoots {
            void MidNightFormula(Polynomial* _poly) {
                cplx A{ _poly->Coefficients.at(2) };
                cplx B{ _poly->Coefficients.at(1) };
                cplx C{ _poly->Coefficients.at(0) };

                if (abs(A) <= 0.0) {
                    return;
                }

                if (abs(B) + abs(C) <= 0.0) {
                    _poly->Roots.emplace_back(0.0);
                    _poly->Roots.emplace_back(0.0);
                    return;
                }

                if (abs(B) <= 0.0) {
                    _poly->Roots.emplace_back((+sqrt(C)) / A);
                    _poly->Roots.emplace_back((-sqrt(C)) / A);
                    return;
                }

                if (abs(C) <= 0.0) {
                    _poly->Roots.emplace_back(0.0);
                    _poly->Roots.emplace_back(-B / A);
                    return;
                }

                _poly->Roots.emplace_back((-B + sqrt(B * B - 4.0 * A * C)) / (2.0 * A));
                _poly->Roots.emplace_back((-B - sqrt(B * B - 4.0 * A * C)) / (2.0 * A));

            }

            void CardanoMethod(Polynomial* _poly) {
                cplx A{ _poly->Coefficients.at(3) };
                if (abs(A) <= 0.0) {
                    return;
                }

                for (auto& elem : _poly->Coefficients) {
                    elem = elem / A;
                }

                A = 1.0;
                cplx B{ _poly->Coefficients.at(2) };
                cplx C{ _poly->Coefficients.at(1) };
                cplx D{ _poly->Coefficients.at(0) };

                if (abs(B) + abs(C) + abs(D) <= 0.0) {
                    _poly->Roots.emplace_back(0.0);
                    _poly->Roots.emplace_back(0.0);
                    _poly->Roots.emplace_back(0.0);
                    return;
                }

                if (abs(D) <= 0.0) {
                    _poly->Roots.emplace_back(0.0);

                    //aux poly of deg 2
                    std::vector<cplx> tmpCoeffs;
                    tmpCoeffs.emplace_back(C);
                    tmpCoeffs.emplace_back(B);
                    tmpCoeffs.emplace_back(A);
                    Polynomial tmp;
                    //tmp.Create<CreateArg::Coefficients>(tmpCoeffs);
                    tmp.CreateFromCoefficients(tmpCoeffs);
                    tmp.FindRoots();
                    _poly->Roots.emplace_back(tmp.Roots.at(0));
                    _poly->Roots.emplace_back(tmp.Roots.at(1));
                    return;
                }

                // Tschirnhaus transformation
                auto p{ (3.0 * C - B * B) / 3.0 };
                auto q{ 2.0 * B * B * B / 27.0 - B * C / 3.0 + D };

                auto sqD{ sqrt(pow(p / 3.0, 3.0) + pow(q / 2.0, 2.0)) };

                std::vector<cplx> w{ { -q / 2.0 + sqD, -q / 2.0 - sqD } };
                for (auto& elem : w) {
                    if (abs(elem.imag()) <= 0.0) {
                        elem = ((abs(elem) <= 0.0) ? 0.0 : elem / abs(elem)) * pow(abs(elem), 1.0 / 3.0);
                    }
                    else {
                        elem = pow(elem, 1.0 / 3.0);
                    }
                }

                auto u{ w.at(0) + w.at(1) };
                auto v{ w.at(0) - w.at(1) };

                _poly->Roots.emplace_back(u - B / 3.0);
                _poly->Roots.emplace_back((-u + sqrt(3.0) * v * cplx(0.0, 1.0)) / 2.0 - B / 3.0);
                _poly->Roots.emplace_back((-u - sqrt(3.0) * v * cplx(0.0, 1.0)) / 2.0 - B / 3.0);

            }

            void FerrariMethod(Polynomial* _poly) {
                cplx A{ _poly->Coefficients.at(3) };
                if (abs(A) <= 0.0) {
                    return;
                }

                for (auto& elem : _poly->Coefficients) {
                    elem = elem / A;
                }

                A = 1.0;
                cplx B{ _poly->Coefficients.at(3) };
                cplx C{ _poly->Coefficients.at(2) };
                cplx D{ _poly->Coefficients.at(1) };
                cplx E{ _poly->Coefficients.at(0) };

                if (abs(B) + abs(C) + abs(D) + abs(E) <= 0.0) {
                    _poly->Roots.emplace_back(0.0);
                    _poly->Roots.emplace_back(0.0);
                    _poly->Roots.emplace_back(0.0);
                    _poly->Roots.emplace_back(0.0);
                    return;
                }

                if (abs(E) <= 0.0) {
                    _poly->Roots.emplace_back(0.0);

                    //aux poly of deg 3
                    std::vector<cplx> tmpCoeffs;
                    tmpCoeffs.emplace_back(D);
                    tmpCoeffs.emplace_back(C);
                    tmpCoeffs.emplace_back(B);
                    tmpCoeffs.emplace_back(A);
                    Polynomial tmp;
                    //tmp.Create<CreateArg::Coefficients>(tmpCoeffs);
                    tmp.CreateFromCoefficients(tmpCoeffs);
                    tmp.FindRoots();
                    _poly->Roots.emplace_back(tmp.Roots.at(0));
                    _poly->Roots.emplace_back(tmp.Roots.at(1));
                    _poly->Roots.emplace_back(tmp.Roots.at(3));
                    return;
                }

                auto p{ (8.0 * A * C - 3.0 * B * B) / (8.0 * A * A) };
                auto q{ 12.0 * A * E - 3.0 * B * D + C * C };
                auto s{ 27.0 * A * D * D - 72.0 * A * C * E + 27.0 * B * B * E - 9.0 * B * C * D + 2.0 * C * C * C };
                auto S{ (8.0 * A * A * D - 4.0 * A * B * C + B * B * B) / (8.0 * A * A * A) };
                auto Delta{ pow(((s + sqrt(s * s - 4.0 * q * q * q)) / 2.0), 1.0 / 3.0) };
                auto Q{ 1.0 / 2.0 * sqrt(-2.0 / 3.0 * p + 1.0 / (3.0 * A) * (Delta + q / Delta)) };
                auto SvsQ{ (abs(S) <= 0) ? 0.0 : S / Q };
                _poly->Roots.emplace_back(-B / (4.0 * A) - Q + 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p + SvsQ));
                _poly->Roots.emplace_back(-B / (4.0 * A) - Q - 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p + SvsQ));
                _poly->Roots.emplace_back(-B / (4.0 * A) + Q + 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p - SvsQ));
                _poly->Roots.emplace_back(-B / (4.0 * A) + Q - 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p - SvsQ));

            }
        }

        template<CreateArg arg>
        void Polynomial::Create(std::vector<cplx>) {
        }

        template<>
        void Polynomial::Create<CreateArg::Coefficients>(std::vector<cplx> _coefficients) {
            CreateFromCoefficients(_coefficients);
        }
        void Polynomial::CreateFromCoefficients(std::vector<cplx> _coefficients) {
            unsigned int deg{ 0 };
            for (auto& elem : _coefficients) {
                Coefficients.emplace_back(elem);
                deg++;
            }
            auto elem = Coefficients.back();
            while (abs(elem.real()) + abs(elem.imag()) <= 0.0) {
                deg--;
                Coefficients.erase(Coefficients.end() - 1);
                elem = Coefficients.back();
            }
            Type = static_cast<PolyType>(--deg);
            if (Type == PolyType::Quadratic) {
                FindRoots = [this]() { std::cout << "Solve PolyType::Quadratic" << std::endl; PolynomialRoots::MidNightFormula(this); };
            }
            if (Type == PolyType::Cubic) {
                FindRoots = [this]() { std::cout << "Solve PolyType::Cubic" << std::endl; PolynomialRoots::CardanoMethod(this); };
            }
            if (Type == PolyType::Quartic) {
                FindRoots = [this]() { std::cout << "Solve PolyType::Quartic" << std::endl; PolynomialRoots::FerrariMethod(this); };
            }
        }

        template<>
        void Polynomial::Create<CreateArg::Roots>(std::vector<cplx> _roots) {
            size_t numberOfRoots{ _roots.size() };
            std::vector<cplx> tmp;
            for (auto& elem : _roots) {
                tmp.emplace_back(-1.0 * elem);
            }
            //implement Vieta's theorem
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
            auto D{ -(z.at(0) * z.at(1) * z.at(2) + z.at(0) * z.at(2) * z.at(3) + z.at(1) * z.at(2) * z.at(3)) };
            auto E{ +(z.at(0) * z.at(1) * z.at(2) * z.at(3)) };

            B = cplx(A->real(), A->imag()) * B;
            C = cplx(A->real(), A->imag()) * C;
            D = cplx(A->real(), A->imag()) * D;
            E = cplx(A->real(), A->imag()) * E;

            unsigned int ofs{ static_cast<unsigned int>(Type) };
            ResultError = abs(w.at(ofs - 1) - E) + abs(w.at(ofs) - D) + abs(w.at(1 + ofs) - C) + abs(w.at(2 + ofs) - B);
        }
    }




}
