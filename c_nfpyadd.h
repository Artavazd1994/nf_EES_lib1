#ifndef C_NFPYADD_H
#define C_NFPYADD_H

#include "ees_common.h"

class c_nfpyadd : public EesDLF
{
public:
  c_nfpyadd();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFPYADD_H
