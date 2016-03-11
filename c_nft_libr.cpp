#include "c_nft_libr.h"
#include "c_libr_props.h"
#include <stdexcept>

c_nft_libr::c_nft_libr() :
  ::EesDLF("NFT_LIBR","T = NFT_LIBR(P, x)", "kPa, kg/kg","C")
{
}

double c_nft_libr::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs.size() < 2) {
    throw std::runtime_error("You jerk! NFT_LIBR expects approximately two inputs.");
  }
  double P = inputs[0] * 0.01; // kPa to bar
  double x = inputs[1];
  double T;
  if (inputs.size() == 2) {
    T = c_libr_props::temperature(P, x);
  } else {
    double Tguess = inputs[2];
    T = c_libr_props::temperature(P, x, Tguess);
  }
  return c_libr_props::K2C(T);
}
