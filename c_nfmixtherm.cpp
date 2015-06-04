#include "c_nfmixtherm.h"
#include "nf_ees_lib1.h"

c_nfmixtherm::c_nfmixtherm() :
  ::EesDLP("NFMIXTHERM", "call NFMIXTHERM(t, D: p, e, h, s)", "K,kg/m3", "kPa,kJ/kg,kJ/kg,kJ/kg-K")
{
  myLib::getofs() << name << ": object constructor" << std::endl;
  try {
    rp = refproper::factory(myLib::getofs());
  } catch (...) {
    myLib::getofs() << name << ": could not initialize refproper." << std::endl;
  }
}

c_nfmixtherm::~c_nfmixtherm()
{
  myLib::getofs() << name << ": object destructor" << std::endl;
  if (rp) {
    delete rp;
  }
}

void c_nfmixtherm::funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs)
{
  if (rp == NULL) {
    std::string str = name + "refproper library not initialized";
    throw std::exception(str.c_str());
  }
  rp -> setupMyFluid();

  std::vector<double> z;
  z.resize(2);
  z[0] = 0.206791740960598;     // Mixture molar composition
  z[1] = 0.793208259039402;
  double t = inputs[0];
  double rho = inputs[1];
  double p, e, h, entropy;
  rp -> thermalProperties(t, rho, z, p, e, h, entropy);
  outputs.resize(4);
  outputs[0] = p;
  outputs[1] = e;
  outputs[2] = h;
  outputs[3] = entropy;
}
