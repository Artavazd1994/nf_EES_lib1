#ifndef C_NFQ_LIBR_H
#define C_NFQ_LIBR_H

#include "ees_common.h"

class c_nfq_libr : public EesDLP
{
public:
  c_nfq_libr();
  void funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs);
};

#endif // C_NFQ_LIBR_H
