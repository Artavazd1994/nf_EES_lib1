#include "c_nftliq.h"
#include "nf_ees_lib1.h"

C_nftliq::C_nftliq() :
  ::EesDLF("NFTLIQ", "T_liq = NFTLIQ(P)", "kPa", "K"),
  rp(myLib::getofs())
{
  myLib::getofs() << name << ": object constructor" << std::endl;
  rp.setupMyFluid();
}

C_nftliq::~C_nftliq()
{
  myLib::getofs() << name << ": object destructor" << std::endl;
}

double C_nftliq::funcDLF(std::string &s, std::vector<double> &inputs)
{
  double P = inputs[0];
  return rp.tliq(P);
}
