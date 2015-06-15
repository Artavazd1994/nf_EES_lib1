#include "c_nfpyadd.h"
#include <exception>
#include <Python.h>

c_nfpyadd::c_nfpyadd() :
  ::EesDLF("NFPYADD", "c = NFPYADD(a,b)", "m,m", "m")
{

}

double c_nfpyadd::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs.size() != 2) {
    throw std::exception("Wrong number of arguments to nfpyadd.");
  }
  Py_Initialize();
  double a = inputs[0], b = inputs[1];
  PyObject * pa = PyFloat_FromDouble(a);
  PyObject * pb = PyFloat_FromDouble(b);
  PyObject * pcode = PyString_FromString("def add(a,b):"
                                         "    return a + b"
                                         "");
  PyObject * pglobals = PyDict_New();
  PyObject * pfunc = PyFunction_New(pcode,pglobals);
  Py_Finalize();

  return 0;
}
