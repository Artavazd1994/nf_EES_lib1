/** @file c_nfpcrit.h
 * @brief a documented file
 */

#ifndef C_NFPCRIT_H
#define C_NFPCRIT_H

#include "ees_common.h"
#include "c_libr_props.h"

/**
 * @brief The c_nfpcrit class
 *
 * Wraps CoolProp Pcrit functionality for EES.
 */
class c_nfpcrit: public EesDLF
{
  c_libr_props libr_props;
public:
  c_nfpcrit();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFPCRIT_H
