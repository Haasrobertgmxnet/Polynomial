#pragma once

#include "..\Polynomial.Core\Polynomial.h"

#ifdef POLYNOMIAL_NOLIB
#define POLYNOMIAL_API
#else
#ifdef POLYNOMIAL_EXPORTS
#define POLYNOMIAL_API __declspec(dllexport)
#else
#define POLYNOMIAL_API __declspec(dllimport)
#endif
#endif

namespace Polynomial {
    namespace Dll {
		class POLYNOMIAL_API Polynomial : ::Polynomial::Core::Polynomial{};
    }
}

