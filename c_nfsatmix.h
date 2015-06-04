#ifndef C_NFSATMIX_H
#define C_NFSATMIX_H

#include "ees_common.h"
#include "refproper.h"

class c_nfsatmix : public EesDLP
{
  refproper *rp;
public:
  c_nfsatmix();
  ~c_nfsatmix();
  void funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs);
public:
};

#endif // C_NFSATMIX_H
