/** @file c_nfsatmix.h
 * @brief a documented file
 */

#ifndef C_NFSATMIX_H
#define C_NFSATMIX_H

#include "ees_common.h"
#include "refproper.h"

/**
 * @brief The c_nfsatmix class
 *
 * Wraps functionality of PQFLSH from REFPROP for EES.
 */
class c_nfsatmix : public EesDLP
{
  refproper *rp;
public:
  c_nfsatmix();
  ~c_nfsatmix();
  void funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs);
public:
};

#endif // C_NFSATMIX_H
