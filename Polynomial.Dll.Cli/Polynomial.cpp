#include "Polynomial.h"
#include "..\Polynomial.Dll\Polynomial.h"

Polynomial::Dll::CLI::Polynomial::Polynomial(double _are, double _aim, double _bre, double _bim, double _cre, double _cim, double _dre, double _dim, double _ere, double _eim)
{
	_impl = new Dll::Polynomial();
	std::vector<cplx> v{ cplx(_are, _aim), cplx(_bre, _bim), cplx(_cre, _cim), cplx(_dre, _dim), cplx(_ere, _eim) };
	_impl->Create<CreateArg::Coefficients>(v);
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


