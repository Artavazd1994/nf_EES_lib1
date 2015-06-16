#include "c_nfpyadd.h"
#include <stdexcept>
#include <Python.h>
#include <helloworld.h>

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
  Py_Initialize();
  inithelloworld();
  double c = add(a,b);
  Py_Finalize();

  return c;
}
