#include "c_nfadd.h"
#include "nf_ees_lib1.h"
#include <stdexcept>

C_NFADD::C_NFADD() :
  ::EesDLF("NFADD", "c = NFADD(a,b)", "m,m", "m")
{
  myLib::getofs() << "hello, beautiful world." << std::endl;
}

C_NFADD::~C_NFADD() {
  myLib::getofs() << "goodbye, cruel world." << std::endl;
}

double C_NFADD::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs[0] == 0) {
    throw std::runtime_error("I am your father.");
  }
  return inputs[0] + inputs[1];
}

