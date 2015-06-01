#include "c_nfadd.h"
#include "nf_ees_lib1.h"

C_NFADD::C_NFADD() {
  myLib::getofs() << "hello, beautiful world." << std::endl;
  name = "NFADD";
}

C_NFADD::~C_NFADD() {
  myLib::getofs() << "goodbye, cruel world." << std::endl;
}

std::string C_NFADD::getCallSignature() const
{
  return "c = NFADD(a,b)";
}

std::string C_NFADD::getInputUnits() const
{
  return "m,m";
}

std::string C_NFADD::getOutputUnits() const
{
  return "m";
}

double C_NFADD::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs[0] == 0) {
    throw std::exception("I am your father.");
  }
  return inputs[0] + inputs[1];
}

