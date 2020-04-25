#pragma once
#include "Polynomial.h"

namespace Polynomial {
	namespace Dll {

		namespace PolynomialRoots {
			int MidNightFormula(Polynomial* _poly) {
				cplx A{ _poly->Coefficients[2] };
				cplx B{ _poly->Coefficients[1] };
				cplx C{ _poly->Coefficients[0] };

				if (abs(A) <= 0.0) {
					return -1;
				}

				if (abs(B) + abs(C) <= 0.0) {
					_poly->Roots.emplace_back(0.0);
					_poly->Roots.emplace_back(0.0);
					_poly->RootsCalculated = true;
					return 0;
				}

				if (abs(B) <= 0.0) {
					_poly->Roots.emplace_back((+sqrt(C)) / A);
					_poly->Roots.emplace_back((-sqrt(C)) / A);
					_poly->RootsCalculated = true;
					return 0;
				}

				if (abs(C) <= 0.0) {
					_poly->Roots.emplace_back(0.0);
					_poly->Roots.emplace_back(-B / A);
					_poly->RootsCalculated = true;
					return 0;
				}

				_poly->Roots.emplace_back((-B + sqrt(B * B - 4.0 * A * C)) / (2.0 * A));
				_poly->Roots.emplace_back((-B - sqrt(B * B - 4.0 * A * C)) / (2.0 * A));
				_poly->RootsCalculated = true;
				return 0;
			}

			int CardanoMethod(Polynomial* _poly) {
				cplx A{ _poly->Coefficients.at(3) };
				if (abs(A) <= 0.0) {
					return -1;
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
					_poly->RootsCalculated = true;
					return 0;
				}

				if (abs(D) <= 0.0) {
					_poly->Roots.emplace_back(0.0);

					//aux poly of deg 2
					Polynomial tmp;
					tmp.Create(2);
					tmp.Coefficients.emplace_back(C);
					tmp.Coefficients.emplace_back(B);
					tmp.Coefficients.emplace_back(A);
					tmp.FindRoots();
					_poly->Roots.emplace_back(tmp.Roots.at(0));
					_poly->Roots.emplace_back(tmp.Roots.at(1));
					_poly->RootsCalculated = true;
					return 0;
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
				_poly->RootsCalculated = true;
				return 0;
			}

			int FerrariMethod(Polynomial* _poly) {

				//Prepare Coefficients
				cplx A{ _poly->Coefficients.at(4) };
				if (abs(A) <= 0.0) {
					return -1;
				}

				for (auto& elem : _poly->Coefficients) {
					elem = elem / A;
				}

				A = 1.0;
				cplx B{ _poly->Coefficients.at(3) };
				cplx C{ _poly->Coefficients.at(2) };
				cplx D{ _poly->Coefficients.at(1) };
				cplx E{ _poly->Coefficients.at(0) };

				//Case 1: Only A is nonzero
				if (abs(B) + abs(C) + abs(D) + abs(E) <= 0.0) {
					_poly->Roots.emplace_back(0.0);
					_poly->Roots.emplace_back(0.0);
					_poly->Roots.emplace_back(0.0);
					_poly->Roots.emplace_back(0.0);
					_poly->RootsCalculated = true;
					return 0;
				}

				//Case 2: Only A and E are nonzero
				if (abs(B) + abs(C) + abs(D) <= 0.0) {
					cplx primRoot{ pow(-E,1.0 / 4.0) };
					auto Root1 = cplx(0.0, 1.0) * primRoot;
					auto Root2 = -primRoot;
					_poly->Roots.emplace_back(Root1);
					_poly->Roots.emplace_back(Root2);
					_poly->Roots.emplace_back(-Root1);
					_poly->Roots.emplace_back(-Root2);
					_poly->RootsCalculated = true;
					return 0;
				}

				//Case 3: E is zero. One zero root and a remaining cubic poly to solve
				if (abs(E) <= 0.0) {
					_poly->Roots.emplace_back(0.0);

					//aux poly of deg 3                   
					Polynomial tmp;
					tmp.Create(3);
					tmp.Coefficients.at(0) = D;
					tmp.Coefficients.at(1) = C;
					tmp.Coefficients.at(2) = B;
					tmp.Coefficients.at(3) = A;
					tmp.FindRoots();
					_poly->Roots.emplace_back(tmp.Roots.at(0));
					_poly->Roots.emplace_back(tmp.Roots.at(1));
					_poly->Roots.emplace_back(tmp.Roots.at(2));
					_poly->RootsCalculated = true;
					return 0;
				}

				//Case 4: Equation has the form (z-z0)^4 == 0
				auto z0{ -B / 4.0 };
				if (abs(C - 6.0 * z0 * z0) + abs(D + 4.0 * z0 * z0 * z0) + abs(E - z0 * z0 * z0 * z0) <= 0.0) {
					_poly->Roots.emplace_back(z0);
					_poly->Roots.emplace_back(z0);
					_poly->Roots.emplace_back(z0);
					_poly->Roots.emplace_back(z0);
					return 0;
				}

				//Case 5: Default and general case
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
				_poly->RootsCalculated = true;
				return 0;
			}
		}
	}
}
