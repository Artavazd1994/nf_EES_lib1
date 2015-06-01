#ifndef C_NFTLIQ_H
#define C_NFTLIQ_H

#include "ees_common.h"
#include "refproper.h"

class C_nftliq : public EesDLF
{
  refproper rp;
public:
  C_nftliq();
  ~C_nftliq();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFTLIQ_H
