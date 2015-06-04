#include "c_nfsatmix.h"
#include "nf_ees_lib1.h"

c_nfsatmix::c_nfsatmix() :
  ::EesDLP("NFSATMIX", "call NFSATMIX(p, q: t, D, h, s)", "kPa,kg/kg", "K,kg/m3,kJ/kg,kJ/kg-K")
{
  myLib::getofs() << name << ": object constructor" << std::endl;
  try {
    rp = refproper::factory(myLib::getofs());
  } catch (...) {
    myLib::getofs() << name << ": could not initialize refproper." << std::endl;
  }
}

c_nfsatmix::~c_nfsatmix()
{
  myLib::getofs() << name << ": object destructor" << std::endl;
  if (rp) {
    delete rp;
  }
}

void c_nfsatmix::funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs)
{
  if (rp == NULL) {
    std::string str = name + "refproper library not initialized";
    throw std::exception(str.c_str());
  }
  rp -> setupMyFluid();

  double p = inputs[0];
  double q = inputs[1];
  double t, D, h, entropy;
  std::vector<double> z;
  z.resize(2);
  z[0] = 0.206791740960598;     // Mixture molar composition
  z[1] = 0.793208259039402;
  rp->saturatedStateFromPressure2(p, q, z, t, D, h, entropy);
  outputs.resize(0);
  outputs.push_back(t);
  outputs.push_back(D);
  outputs.push_back(h);
  outputs.push_back(entropy);
  myLib::getofs() << name << ": funcDLP: outputs.size = " << outputs.size() << std::endl;
}
