#include <Python.h>
#include <map>

#define VC9_PYTHON27
//#include "..\Polynomial.Core\Polynomial.h"
#include <C:\Users\Robert\source\repos\Polynomial\Polynomial.Core\Polynomial.h>

static PyObject*
calculateRoots(PyObject* self, PyObject* args)
{
    Py_complex defaultVal;
    defaultVal.real = 0.0;

    std::map<char, Py_complex> coeffs;
    coeffs['A'].real = 0.0;
    coeffs['B'].real = 0.0;
    coeffs['C'].real = 0.0;
    coeffs['D'].real = 0.0;
    coeffs['E'].real = 0.0;

    if (!PyArg_ParseTuple(args, "DDDDD",
        &coeffs['A'],
        &coeffs['B'],
        &coeffs['C'],
        &coeffs['D'],
        &coeffs['E']))
        return NULL;

    Polynomial::Core::Polynomial poly;
    //poly.Create(4);

    //for (int j = 0; j < 5; ++j) {
    //    char c = static_cast<char>(65 + j);
    //    poly.Coefficients[j].real(coeffs[c].real);
    //    poly.Coefficients[j].imag(coeffs[c].imag);
    //}

    //poly.FindRoots();
    //poly.ValidateRoots();

    //std::array<Py_complex, 4> results{ { defaultVal , defaultVal , defaultVal , defaultVal } };

    Py_complex results[4];

    for (unsigned int j = 0; j < 4; ++j) {
        results[j].real = 0.1;// poly.Roots[j].real();
        results[j].imag = 0.1;// poly.Roots[j].imag();
    }

    PyObject* tuple;
    tuple = Py_BuildValue("(DDDD)", results, &results[1], &results[2], &results[3]);
    return tuple;

}

static PyMethodDef PolyMethods[] = {
     {"calc_roots",  calculateRoots, METH_VARARGS,
     "Calculate Roots of 4th order polynomial."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initcalcrootsmodule(void)
{
    (void)Py_InitModule("calcrootsmodule", PolyMethods);
}

