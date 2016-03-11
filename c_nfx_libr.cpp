#include "c_nfx_libr.h"
#include "c_libr_props.h"

c_nfx_libr::c_nfx_libr() :
  EesDLF("NFX_LIBR","x = NFX_LIBR(T,P)","C,kPa","kg/kg")
{

}

double c_nfx_libr::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs.size() < 2) {
    throw std::runtime_error("Your code has taken a turn for the worst. NFX_LIBR expects ~two arguments.");
  }
  double T = c_libr_props::C2K(inputs[0]);
  double P = inputs[1] * 0.01; // kPa to bar
  if (inputs.size() == 2) {
    return c_libr_props::massFraction(P,T);
  }
  double xGuess = inputs[2];
  return c_libr_props::massFraction(P,T,xGuess);
}

