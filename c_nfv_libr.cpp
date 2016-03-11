#include "c_nfv_libr.h"
#include "c_libr_props.h"

c_nfv_libr::c_nfv_libr() :
  ::EesDLF("NFV_LIBR","v = NFV_LIBR(T, x)", "C, kg/kg","m3/kg")
{

}

double c_nfv_libr::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs.size() != 2) {
    throw std::runtime_error("Are you high? NFV_LIBR expects two inputs.");
  }
  double T = c_libr_props::C2K(inputs[0]);
  double x = inputs[1];
  double rho = c_libr_props::massDensity(T, x);
  double v = 1. / rho;
  return v;
}
