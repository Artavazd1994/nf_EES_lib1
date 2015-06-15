/** @file c_nfadd.h
 * @brief a documented file
 */

#ifndef C_NFADD_H
#define C_NFADD_H

#include "ees_common.h"

/**
 * @brief The C_NFADD class
 * Example to demonstrate the DLF wrapper.
 */
class C_NFADD: public EesDLF {
public:
  C_NFADD();
  ~C_NFADD();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFADD_H
