#include "c_nfmixtherm.h"
#include "nf_ees_lib1.h"

c_nfmixtherm::c_nfmixtherm() :
  ::EesDLP("NFMIXTHERM", "call NFMIXTHERM(t, D: p, e, h, s)", "K,kg/m3", "kPa,kJ/kg,kJ/kg,kJ/kg-K")
{
  myLib::getofs() << name << ": object constructor" << std::endl;
}

c_nfmixtherm::~c_nfmixtherm()
{
  myLib::getofs() << name << ": object destructor" << std::endl;
  if (rp) {
    delete rp;
  }
}

void c_nfmixtherm::funcDLP(std::string &, std::vector<double> &inputs, std::vector<double> &outputs)
{
  if (rp == NULL) {
    // throws std::exception
    rp = refproper::factory(myLib::getofs());
  }
  rp -> setupMyFluid();

  std::vector<double> z;
  z.resize(2);
  z[0] = 0.40;     // Mixture mass composition
  z[1] = 0.60;
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
