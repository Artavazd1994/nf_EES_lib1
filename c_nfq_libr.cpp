#include "c_nfq_libr.h"

#include "c_libr_props.h"
#include <sstream>

c_nfq_libr::c_nfq_libr() :
  ::EesDLP("NFQ_LIBR","CALL NFQ_LIBR(H,P,Z:Q,T,X)","kJ/kg,kPa,kg/kg","kg/kg,C,kg/kg")
{

}

void c_nfq_libr::funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs)
{
  if (inputs.size() < 3) {
    std::ostringstream oss;
    oss << "NFQ_LIBR expects three inputs. You gave "
        << inputs.size() << ", which is wrong.";
    throw std::runtime_error(oss.str());
  }
  double h = inputs[0] * 1000.; // kJ/kg to J/kg
  double p = inputs[1] * 0.01; // kPa to bar
  double z = inputs[2];
  double q, t, x;
  if (inputs.size() == 4) {
    x = inputs[3];
  }

  c_libr_props::twoPhaseProps(h, p, z, q, t, x);
  outputs.resize(3);
  outputs[0] = q;
  outputs[1] = c_libr_props::K2C(t);
  outputs[2] = x;
}

