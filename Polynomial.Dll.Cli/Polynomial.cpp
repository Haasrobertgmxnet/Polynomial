#include "Polynomial.h"
#include "..\Polynomial.Dll\Polynomial.h"

Polynomial::Dll::CLI::Polynomial::Polynomial(double _are, double _aim, double _bre, double _bim, double _cre, double _cim, double _dre, double _dim, double _ere, double _eim)
{
	_impl = new Dll::Polynomial();
	_impl->Create(4);
	_impl->Coefficients.at(0) = cplx(_ere, _eim);
	_impl->Coefficients.at(1) = cplx(_dre, _dim);
	_impl->Coefficients.at(2) = cplx(_cre, _cim);
	_impl->Coefficients.at(3) = cplx(_bre, _bim);
	_impl->Coefficients.at(4) = cplx(_are, _aim);
}

Polynomial::Dll::CLI::Polynomial::~Polynomial()
{
	Destroy();
}

void Polynomial::Dll::CLI::Polynomial::Destroy()
{
	if (_impl != nullptr)
	{
		delete _impl;
		_impl = nullptr;
	}
}

void Polynomial::Dll::CLI::Polynomial::FindRoots()
{
	_impl->FindRoots();
}

void Polynomial::Dll::CLI::Polynomial::ValidateRoots()
{
	_impl->ValidateRoots();
}

double Polynomial::Dll::CLI::Polynomial::GetRoot(unsigned rootNo, unsigned part)
{
	cplx result;
	if (_impl == nullptr) {
		return 0.0;
	}
	if (rootNo > 3) {
		return 0.0;
	}
	if (part > 1) {
		return 0.0;
	}

	//something more tbd!
	result = _impl->Roots.at(rootNo);

	if (part == 0) {
		return result.real();
	}
	if (part == 1) {
		return result.imag();
	}
	return 0.0;
}

double Polynomial::Dll::CLI::Polynomial::GetResultError()
{
	if (_impl == nullptr) {
		return DBL_MAX;
	}
	return _impl->ResultError;
}


