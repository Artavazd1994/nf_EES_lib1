#ifndef C_LIBR_PROPS_H
#define C_LIBR_PROPS_H

#include <string>

// requires CoolProp
class c_libr_props
{
public:
  static const double MW_LiBr ; // kg/kmol
  static const double MW_H2O ; // kg/kmol

  c_libr_props();
  // a test case
  double C2K(double);
  double K2C(double);
  double underPressure(std::string fluid);
  double mole2massFraction(double x);
  double moleFraction(double w);
  double pressure(double T, double x);
  double objectiveT(double T, double P, double x);
  double temperature(double P, double x);
  double objectiveX(double x, double T, double P);
  double massFraction(double T, double P);
  double massSpecificEnthalpy(double T, double x);
  double massSpecificEntropy(double T, double x);
  double massSpecificHeat(double T, double x);
  void twoPhaseProps(double h, double P, double z,
                     double &Q, double &T, double &x);
  double massSpecificGibbs(double T, double x);
  double massDensity(double T, double x);
  double testMe();

};

#endif // C_LIBR_PROPS_H
