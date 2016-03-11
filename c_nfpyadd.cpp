#include "c_nfpyadd.h"
#include <stdexcept>
#ifdef ENABLE_PYTHONS
#include <Python.h>
#include <helloworld.h>
#endif

c_nfpyadd::c_nfpyadd() :
  ::EesDLF("NFPYADD", "c = NFPYADD(a,b)", "m,m", "m")
{

}

double c_nfpyadd::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs.size() != 2) {
    throw std::runtime_error("Wrong number of arguments to nfpyadd.");
  }
  double a = inputs[0], b = inputs[1];
  double c;
#ifdef ENABLE_PYTHONS
  Py_Initialize();
  inithelloworld();
  c = add(a,b);
  Py_Finalize();
#else
  throw std::runtime_error("This function was disabled at compile time. Sorry!");
#endif

  return c;
}
