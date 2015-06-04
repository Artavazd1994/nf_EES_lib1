#ifndef C_NFMIXTHERM_H
#define C_NFMIXTHERM_H

#include "ees_common.h"
#include "refproper.h"

class c_nfmixtherm : public EesDLP
{
  refproper * rp;
public:
  c_nfmixtherm();
  ~c_nfmixtherm();
  void funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs);
};

#endif // C_NFMIXTHERM_H
