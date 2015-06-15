/** @file c_nfp_libr.h
 * @brief a documented file
 */

#ifndef C_NFP_LIBR_H
#define C_NFP_LIBR_H

#include "ees_common.h"

/**
 * @brief The c_nfp_libr class
 *
 * EES wrapper for implementation of P_LIBR.
 */
class c_nfp_libr : public EesDLF
{
public:
  c_nfp_libr();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFP_LIBR_H
