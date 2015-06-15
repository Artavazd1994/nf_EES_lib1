#include "c_libr_props.h"

#include "CoolProp.h"
#include <cmath>
#include "nf_ees_lib1.h"
#include <exception>
#include <boost/math/tools/roots.hpp>

namespace nf {
int isnan(double x) { return x != x; }
int isinf(double x) { return !isnan(x) && isnan(x - x); }
}

const double c_libr_props::MW_LiBr = 86.85;
const double c_libr_props::MW_H2O = 18.015;

double c_libr_props::C2K(double tc)
{
  return tc + 273.15;
}

double c_libr_props::K2C(double tk)
{
  return tk - 273.15;
}

double c_libr_props::underPressure(std::string fluid)
{
  double result = CoolProp::Props1SI(fluid,"Pcrit");
  if (nf::isinf(result)) {
    throw std::exception("CoolProp doesn't know that fluid.");
  }
  return result;
}

/** input: mole fraction, x, of LiBr */
double c_libr_props::mole2massFraction(double x)
{
  return x * MW_LiBr / (x * MW_LiBr + (1. - x) * MW_H2O);
}

/** input: mass fraction, w, of LiBr */
double c_libr_props::moleFraction(double w)
{
  return (w / MW_LiBr) / (w/MW_LiBr + (1. - w) / MW_H2O);
}

/**
 * Return pressure above a lithium bromide-water mixture
 * at the given temperature and composition using the formulation
 * presented by
 * Patek and Klomfar, Int. J. Refrig., Vol 29, pp 566-578 (2006)
 *
 * Notes: "above" the mixture: is completely water vapor. So there are only
 * two relevant properties to find equilibrium vapor pressure (?).
 *
 * Based on Table 4 and Equation (1) in reference.
 *
 * @brief c_libr_props::pressure
 * @param T = temperature [K]
 * @param x = mass fraction LiBr
 * @return P [bar]
 */
double c_libr_props::pressure(double T, double x)
{
  double a[] = {-2.41303e2, 1.91750e7, -1.75521e8, 3.25432e7, 3.92571e2, -2.12626e3, 1.85127e8, 1.91216e3};
  int m[] = {3,4,4,8,1,1,4,6};
  int n[] = {0,5,6,3,0,2,6,0};
  int t[] = {0,0,0,0,1,1,1,1};
  double T_c = 647.096; // [K]
  double h_c = 37548.5; // [J/gmol] "Enthalpy at the critical point for pure water"
  // TK = convertTemp(T$,K,T)	"convert to K"
  double TK = T;
  // if (UnitSystem('mass')=1) then x=molefraction_LiBrH2O(x)
  double x_N = moleFraction(x);

  double s = 0;
  for (int i = 0; i < 8; i++) {
    s = s + a[i] * pow(x_N,m[i]) * pow(abs(0.4-x_N),n[i]) * pow((TK/T_c),t[i]);
  }
  double Theta = TK - s;
  //Ts=convertTemp(K,T$,Theta)
  double Ts = Theta;
  double Q = 0.0;
  // print("Ts, Q = {}, {}".format(Ts, Q))
  double pressurePa = CoolProp::PropsSI("P","T",Ts,"Q",Q,"Water"); // Pa
  getLib().getofs() << "Ts, Q = " << Ts << ", " << Q << std::endl;
  getLib().getofs() << "still here" << std::endl;
  if (nf::isinf(pressurePa)) {
    getLib().getofs() << "preparing to throw a fit" << std::endl;
    throw std::exception("CoolProp is unhappy with you for SO MANY REASONS. But I can't name any.");
  }
  getLib().getofs() << "but not here" << std::endl;
  //myLib().getofs() << "pressurePa = " << pressurePa << std::endl;
  // print("pressurePa = {}".format(pressurePa)) // ()
  double pressureBar = pressurePa * 1e-5;

  return pressureBar;
}

/**
 * @brief c_libr_props::objectiveT
 * @param T
 * @param P
 * @param x
 * @return Error in provided pressure.
 */
double c_libr_props::objectiveT(double T, double P, double x)
{
  return pow(P - pressure(T,x), 2);
}

double c_libr_props::temperature(double P, double x)
{
  LiBr_TFunctor f(P, x);
  double T = boost::math::tools::newton_raphson_iterate
      <LiBr_TFunctor, double>(f, 646., 274, 647, 20);
  return T;
}

LiBr_TFunctor::LiBr_TFunctor(const double &P, const double &X, double deltaT)
  : p(P), x(X), deltaT(deltaT)
{
}

boost::math::tuple<double, double> LiBr_TFunctor::operator()(const double &Tguess)
{
  double P0 = c_libr_props::pressure(Tguess, x);
  double P1 = c_libr_props::pressure(Tguess + deltaT, x);
  double dPdT = (P1 - P0) / deltaT;
  double f = (P0 - p) * (P0 - p); // the objective function
  double fprime = 2.0 * (P0 - p) * dPdT;
  return boost::math::make_tuple(f, fprime);
}
