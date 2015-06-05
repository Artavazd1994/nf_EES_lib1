#include "c_nftliq.h"
#include "nf_ees_lib1.h"

C_nftliq::C_nftliq() :
  ::EesDLP("NFTLIQ", "call NFTLIQ(P: t, rho_l, rho_v, xliq0, xvap0)", "kPa", "K,kg/m3,kg/m3,mol/mol,mol/mol")
{
  myLib::getofs() << name << ": object constructor" << std::endl;
  try {
    rp = refproper::factory(myLib::getofs());
  } catch (...) {
    myLib::getofs() << name << ": could not initialize refproper." << std::endl;
  }
}

C_nftliq::~C_nftliq()
{
  myLib::getofs() << name << ": object destructor" << std::endl;
  if (rp) {
    delete rp;
  }
}

void C_nftliq::funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs)
{
  if (rp == NULL) {
    std::string str = name + "refproper library not initialized";
    throw std::exception(str.c_str());
  }
  rp -> setupMyFluid();

  double P = inputs[0];
  double t, rho_l, rho_v;
  std::vector<double> v_xliq, v_xvap;
  v_xliq.resize(2);
  v_xvap.resize(2);
  std::vector<double> z;
  z.resize(2);
  z[0] = 0.40;     // Mixture mass composition
  z[1] = 0.60;
  rp->saturatedLiquidFromPressure(P, z, t, rho_l, rho_v, v_xliq, v_xvap);
  outputs.resize(0);
  outputs.push_back(t);
  outputs.push_back(rho_l);
  outputs.push_back(rho_v);
  outputs.push_back(v_xliq[0]);
  outputs.push_back(v_xvap[0]);
  myLib::getofs() << "C_nftliq::funcDLP: outputs.size = " << outputs.size() << std::endl;
}
