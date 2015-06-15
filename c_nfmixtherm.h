/** @file c_nfmixtherm.h
 * @brief a documented file
 */

#ifndef C_NFMIXTHERM_H
#define C_NFMIXTHERM_H

#include "ees_common.h"
#include "refproper.h"

/**
 * @brief The c_nfmixtherm class
 *
 * Wraps REFPROP THERM functionality in a DLP.
 */
class c_nfmixtherm : public EesDLP
{
  refproper * rp;
public:
  c_nfmixtherm();
  ~c_nfmixtherm();
  void funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs);
};

#endif // C_NFMIXTHERM_H
