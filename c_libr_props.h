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

  //c_libr_props();
  // a test case
  static double C2K(double);
  static double K2C(double);
  static double underPressure(std::string fluid);
  static double mole2massFraction(double x);
  static double moleFraction(double w);
  static double pressure(double T, double x);
  static double objectiveT(double T, double P, double x);
  static double temperature(double P, double x, double Tguess = 0);
  static double objectiveX(double x, double T, double P);
  static double massFraction(double T, double P);
  static double massSpecificEnthalpy(double T, double x);
  static double massSpecificEntropy(double T, double x);
  static double massSpecificHeat(double T, double x);
  static void twoPhaseProps(double h, double P, double z,
                     double &Q, double &T, double &x);
  static double massSpecificGibbs(double T, double x);
  static double massDensity(double T, double x);
  static double testMe();

};

struct LiBr_TFunctor
{
  // Constructor stores value to be matched.
  LiBr_TFunctor(double const& P, double const& X, double deltaT = 1e-5);
  // Tguess is estimate so far.
  boost::math::tuple<double, double> operator()(double const& Tguess);
private:
  double p; // pressure to be matched.
  double x; // concentration
  double deltaT;
};

#endif // C_LIBR_PROPS_H
