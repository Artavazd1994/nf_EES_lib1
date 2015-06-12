#include "c_libr_props.h"

#include "CoolProp.h"
#include <cmath>

namespace nf {
int isnan(double x) { return x != x; }
int isinf(double x) { return !isnan(x) && isnan(x - x); }
}

c_libr_props::c_libr_props()
{
}

double c_libr_props::underPressure(std::string fluid)
{
  double result = CoolProp::Props1SI(fluid,"Pcrit");
  if (nf::isinf(result)) {
    throw std::exception("CoolProp doesn't know that fluid.");
  }
  return result;
}
