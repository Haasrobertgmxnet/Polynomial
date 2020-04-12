#pragma once

namespace Polynomial {
	namespace Dll {
		class Polynomial;
		namespace CLI {
			public ref class Polynomial
			{
			public:
				Polynomial(double _are, double _aim, double _bre, double _bim, double _cre, double _cim, double _dre, double _dim, double _ere, double _eim);
				~Polynomial();
				void Destroy();

				void FindRoots();
				void ValidateRoots();
				double GetRoot(unsigned rootNo, unsigned part);
				double GetResultError();

			private:
				Dll::Polynomial* _impl;
			};
		}
	}
}


