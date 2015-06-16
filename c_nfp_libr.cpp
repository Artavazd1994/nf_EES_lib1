#include "c_nfp_libr.h"

#include <stdexcept>
#include "c_libr_props.h"
#include "nf_ees_lib1.h"

c_nfp_libr::c_nfp_libr() :
  ::EesDLF("NFP_LIBR","P = NFP_LIBR(T, x)", "K, kg/kg","bar")
{
}

double c_nfp_libr::funcDLF(std::string &, std::vector<double> &inputs)
{
  try {
    if (inputs.size() != 2) {
      throw std::runtime_error("NFP_LIBR expects two arguments: one with Chuck Norris and one about where to bury the body.");
    }
    double T = inputs[0];
    double x = inputs[1];
    double pressure = c_libr_props::pressure(T, x);
    return pressure;
  } catch (std::exception &e) {
    throw e;
  } catch (...) {
    throw std::runtime_error("An unknown kind of thing ... perhaps a Balrog?");
  }
}
