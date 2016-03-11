#ifndef C_NFX_LIBR_H
#define C_NFX_LIBR_H

#include "ees_common.h"

class c_nfx_libr : public EesDLF
{
public:
  c_nfx_libr();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFX_LIBR_H
