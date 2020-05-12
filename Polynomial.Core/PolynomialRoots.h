#pragma once

#include "Polynomial.h"

namespace Polynomial {
	namespace Core {

		namespace PolynomialRoots {

			// Calculate polynomial coefficientes from
			// calculated roots via Vieta's theorem
			std::vector<cplx> Vieta(std::vector<cplx> w) {
				if (w.size() == 1) {
					return w;
				}

				cplx lastElem = w[w.size() - 1];
				w.erase(w.end() - 1);
				w = Vieta(w);
				std::vector<cplx> result;
				std::vector<cplx>::iterator it = w.begin();
				result.push_back((*it) + lastElem);
				for (++it; it != w.end(); ++it) {
					result.push_back(*it + *(it - 1) * lastElem);
				}
				result.push_back(*(it - 1) * lastElem);
				return result;
			}

			template<typename T>
			int ValidateRoots(T* _poly) {
				if (_poly->RootsCalculated) {
					// This will store the Coefficients in reverse order
					// The leading coefficient is assumed to be 1 and not stored here
					std::vector<cplx> FlippedCoefficients;
					// But first, the calculated roots will be stored here
					// to apply Vieta's theorem
					for (std::vector<cplx>::iterator it = _poly->Roots.begin(); it != _poly->Roots.end(); ++it) {
						FlippedCoefficients.push_back(-1.0 * (*it));
					}
					FlippedCoefficients = Vieta(FlippedCoefficients);
					_poly->ResultError = 0.0;
					for (unsigned int j = 1; j <= FlippedCoefficients.size(); ++j) {
						unsigned int idx = FlippedCoefficients.size() - j;
						_poly->ResultError += abs(FlippedCoefficients[j - 1] - _poly->Coefficients[idx]);
					}
				}
				return 0;
			}

			template<typename T>
			int MidNightFormula(T* _poly) {
				cplx A = _poly->Coefficients[2];
				cplx B = _poly->Coefficients[1];
				cplx C = _poly->Coefficients[0];

				if (abs(A) <= 0.0) {
					return -1;
				}

				if (abs(B) + abs(C) <= 0.0) {
					_poly->Roots.push_back(0.0);
					_poly->Roots.push_back(0.0);
					_poly->RootsCalculated = true;
					return 0;
				}

				if (abs(B) <= 0.0) {
					_poly->Roots.push_back((+sqrt(C)) / A);
					_poly->Roots.push_back((-sqrt(C)) / A);
					_poly->RootsCalculated = true;
					return 0;
				}

				if (abs(C) <= 0.0) {
					_poly->Roots.push_back(0.0);
					_poly->Roots.push_back(-B / A);
					_poly->RootsCalculated = true;
					return 0;
				}

				_poly->Roots.push_back((-B + sqrt(B * B - 4.0 * A * C)) / (2.0 * A));
				_poly->Roots.push_back((-B - sqrt(B * B - 4.0 * A * C)) / (2.0 * A));
				_poly->RootsCalculated = true;
				return 0;
			}

			template<typename T>
			int CardanoMethod(T* _poly) {
				cplx A = _poly->Coefficients[3];
				if (abs(A) <= 0.0) {
					return -1;
				}

				for (int j = 0; j < 3; j++) {
					_poly->Coefficients[j] = _poly->Coefficients[j] / A;
				}

				A = 1.0;
				cplx B = _poly->Coefficients[2];
				cplx C = _poly->Coefficients[1];
				cplx D = _poly->Coefficients[0];

				if (abs(B) + abs(C) + abs(D) <= 0.0) {
					_poly->Roots.push_back(0.0);
					_poly->Roots.push_back(0.0);
					_poly->Roots.push_back(0.0);
					_poly->RootsCalculated = true;
					return 0;
				}

				if (abs(D) <= 0.0) {
					_poly->Roots.push_back(0.0);

					//aux poly of deg 2
					Polynomial tmp2;
					tmp2.Create(2);
					tmp2.Coefficients[0] = C;
					tmp2.Coefficients[1] = B;
					tmp2.Coefficients[2] = A;
					tmp2.FindRoots();
					_poly->Roots.push_back(tmp2.Roots[0]);
					_poly->Roots.push_back(tmp2.Roots[1]);
					_poly->RootsCalculated = true;
					return 0;
				}

				// Tschirnhaus transformation
				cplx p = (3.0 * C - B * B) / 3.0;
				cplx q = 2.0 * B * B * B / 27.0 - B * C / 3.0 + D;

				cplx sqD = sqrt(pow(p / 3.0, 3.0) + pow(q / 2.0, 2.0));

				std::vector<cplx> w;
				w.push_back( - q / 2.0 + sqD);
				w.push_back( - q / 2.0 - sqD);

				for (int j = 0; j < 2 ;j++ ) {
					if (abs(w[j].imag()) <= 0.0) {
						w[j] = ((abs(w[j]) <= 0.0) ? 0.0 : w[j] / abs(w[j])) * pow(abs(w[j]), 1.0 / 3.0);
					}
					else {
						w[j] = pow(w[j], 1.0 / 3.0);
					}
				}

				cplx u = w[0] + w[1];
				cplx v = w[0] - w[1];

				_poly->Roots.push_back(u - B / 3.0);
				_poly->Roots.push_back((-u + sqrt(3.0) * v * cplx(0.0, 1.0)) / 2.0 - B / 3.0);
				_poly->Roots.push_back((-u - sqrt(3.0) * v * cplx(0.0, 1.0)) / 2.0 - B / 3.0);
				_poly->RootsCalculated = true;
				return 0;
			}

			template<typename T>
			int FerrariMethod(T* _poly) {

				//Prepare Coefficients
				cplx A = _poly->Coefficients[4];
				if (abs(A) <= 0.0) {
					return -1;
				}

				for (int j = 0; j < 4;j++) {
					_poly->Coefficients[j] = _poly->Coefficients[j] / A;
				}

				A = 1.0;
				cplx B = _poly->Coefficients[3];
				cplx C = _poly->Coefficients[2];
				cplx D = _poly->Coefficients[1];
				cplx E = _poly->Coefficients[0];

				//Case 1: Only A is nonzero
				if (abs(B) + abs(C) + abs(D) + abs(E) <= 0.0) {
					_poly->Roots.push_back(0.0);
					_poly->Roots.push_back(0.0);
					_poly->Roots.push_back(0.0);
					_poly->Roots.push_back(0.0);
					_poly->RootsCalculated = true;
					return 0;
				}

				//Case 2: Only A and E are nonzero
				if (abs(B) + abs(C) + abs(D) <= 0.0) {
					cplx primRoot = pow(-E, 1.0 / 4.0);
					cplx Root1 = cplx(0.0, 1.0) * primRoot;
					cplx Root2 = -primRoot;
					_poly->Roots.push_back(Root1);
					_poly->Roots.push_back(Root2);
					_poly->Roots.push_back(-Root1);
					_poly->Roots.push_back(-Root2);
					_poly->RootsCalculated = true;
					return 0;
				}

				//Case 3: E is zero. One zero root and a remaining cubic poly to solve
				if (abs(E) <= 0.0) {
					_poly->Roots.push_back(0.0);

					//aux poly of deg 3                   
					Polynomial tmp3;
					tmp3.Create(3);
					tmp3.Coefficients[0] = D;
					tmp3.Coefficients[1] = C;
					tmp3.Coefficients[2] = B;
					tmp3.Coefficients[3] = A;
					tmp3.FindRoots();
					_poly->Roots.push_back(tmp3.Roots.at(0));
					_poly->Roots.push_back(tmp3.Roots.at(1));
					_poly->Roots.push_back(tmp3.Roots.at(2));
					_poly->RootsCalculated = true;
					return 0;
				}

				//Case 4: Equation has the form (z-z0)^4 == 0
				cplx z0 = -B / 4.0;
				if (abs(C - 6.0 * z0 * z0) + abs(D + 4.0 * z0 * z0 * z0) + abs(E - z0 * z0 * z0 * z0) <= 0.0) {
					_poly->Roots.push_back(z0);
					_poly->Roots.push_back(z0);
					_poly->Roots.push_back(z0);
					_poly->Roots.push_back(z0);
					_poly->RootsCalculated = true;
					return 0;
				}

				//Case 5: Default and general case
				cplx p= (8.0 * A * C - 3.0 * B * B) / (8.0 * A * A);
				cplx q= 12.0 * A * E - 3.0 * B * D + C * C;
				cplx s= 27.0 * A * D * D - 72.0 * A * C * E + 27.0 * B * B * E - 9.0 * B * C * D + 2.0 * C * C * C;
				cplx S= (8.0 * A * A * D - 4.0 * A * B * C + B * B * B) / (8.0 * A * A * A);
				cplx Delta= pow(((s + sqrt(s * s - 4.0 * q * q * q)) / 2.0), 1.0 / 3.0);
				cplx Q= 1.0 / 2.0 * sqrt(-2.0 / 3.0 * p + 1.0 / (3.0 * A) * (Delta + q / Delta));
				cplx SvsQ= (abs(S) <= 0) ? 0.0 : S / Q;
				_poly->Roots.push_back(-B / (4.0 * A) - Q + 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p + SvsQ));
				_poly->Roots.push_back(-B / (4.0 * A) - Q - 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p + SvsQ));
				_poly->Roots.push_back(-B / (4.0 * A) + Q + 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p - SvsQ));
				_poly->Roots.push_back(-B / (4.0 * A) + Q - 1 / 2.0 * sqrt(-4.0 * Q * Q - 2.0 * p - SvsQ));
				_poly->RootsCalculated = true;
				return 0;
			}
		}
	}
}

