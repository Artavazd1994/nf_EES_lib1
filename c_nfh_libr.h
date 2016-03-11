#ifndef C_NFH_LIBR_H
#define C_NFH_LIBR_H

#include "ees_common.h"

class c_nfh_libr : public EesDLF
{
public:
  c_nfh_libr();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFH_LIBR_H
