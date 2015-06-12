#ifndef C_NFPCRIT_H
#define C_NFPCRIT_H

#include "ees_common.h"
#include "c_libr_props.h"

class c_nfpcrit: public EesDLF
{
  c_libr_props libr_props;
public:
  c_nfpcrit();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFPCRIT_H
