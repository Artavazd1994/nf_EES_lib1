/** @file c_libr_props.h
 * @brief a documented file
 */

#ifndef C_LIBR_PROPS_H
#define C_LIBR_PROPS_H

#include <string>
#include <boost/math/tools/tuple.hpp>

/**
 * @brief The c_libr_props class
 *
 * Requires CoolProp.h to build. Implements LiBr-water properties
 * per Patek and Klomfar.
 */
class c_libr_props
{
public:
  static const double MW_LiBr ; // kg/kmol
  static const double MW_H2O ; // kg/kmol

  // let's be static.
  //c_libr_props();

  static double C2K(double);
  static double K2C(double);
  static double underPressure(std::string fluid);
  static double mole2massFraction(double x);
  static double moleFraction(double w);
  static double theta(double T, double x, double *dThdT = NULL, double *dThdx = NULL);
  static double pressure(double T, double x);
  static double temperature(double P, double x, double Tguess = 0);
  static double massFraction(double P, double T, double Xguess = -1);
  static double massSpecificEnthalpy(double T, double x);
  static double massSpecificEntropy(double T, double x);
  static double massSpecificHeat(double T, double x);
  static void twoPhaseProps(double h, double P, double z,
                     double &Q, double &T, double &x);
  static double massSpecificGibbs(double T, double x);
  static double massDensity(double T, double x);
  // a test case
  static double testMe();

};

struct LiBr_TFunctor
{
  // Constructor stores value to be matched.
  LiBr_TFunctor(double const& Pbar, double const& X);
  // Tguess is estimate so far.
  boost::math::tuple<double, double> operator()(double const& Tguess);
private:
  double theta; // reduced temperature to be matched.
  double x; // concentration
};

struct LiBr_XFunctor
{
  // Constructor stores value to be matched.
  LiBr_XFunctor(double const& Pbar, double const& T);
  // Xguess is estimate so far.
  boost::math::tuple<double, double> operator()(double const& Xguess);
private:
  unsigned int iter;
  double theta; // reduced temperature to be matched.
  double T; // temperature
};
#endif // C_LIBR_PROPS_H
