#ifndef C_NFP_LIBR_H
#define C_NFP_LIBR_H

#include "ees_common.h"

class c_nfp_libr : public EesDLF
{
public:
  c_nfp_libr();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFP_LIBR_H
