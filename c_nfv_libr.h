#ifndef C_NFV_LIBR_H
#define C_NFV_LIBR_H

#include "ees_common.h"

class c_nfv_libr : public EesDLF
{
public:
  c_nfv_libr();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFV_LIBR_H
