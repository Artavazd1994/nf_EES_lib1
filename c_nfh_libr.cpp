#include "c_nfh_libr.h"
#include "c_libr_props.h"

c_nfh_libr::c_nfh_libr() :
  ::EesDLF("NFH_LIBR","h = NFH_LIBR(T, x)", "C, kg/kg","kJ/kg")
{
}

double c_nfh_libr::funcDLF(std::string &s, std::vector<double> &inputs)
{
  if (inputs.size() != 2) {
    throw std::runtime_error("You jerk! NFH_LIBR expects two inputs.");
  }
  double T = c_libr_props::C2K(inputs[0]);
  double x = inputs[1];
  return 0.001 * c_libr_props::massSpecificEnthalpy(T,x); // J/kg to kJ/kg
}

