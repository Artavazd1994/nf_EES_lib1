#include "c_nft_libr.h"
#include "c_libr_props.h"

c_nft_libr::c_nft_libr() :
  ::EesDLF("NFT_LIBR","T = NFT_LIBR(P, x)", "bar, kg/kg","K")
{
}

double c_nft_libr::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs.size() != 2) {
    throw std::exception("You jerk! NFT_LIBR expects two inputs.");
  }
  double P = inputs[0];
  double x = inputs[1];
  return c_libr_props::temperature(P, x);
}
