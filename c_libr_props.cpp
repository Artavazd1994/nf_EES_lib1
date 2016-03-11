#include "c_libr_props.h"

#include <CoolProp.h>
#include <AbstractState.h>
#include <cmath>
#include "nf_ees_lib1.h"
#include <exception>
#include <boost/math/tools/roots.hpp>
#include <memory>
#include "ees_common.h"
#include <iomanip>
#include <cstdio>

namespace nf {
int isnan(double x) { return x != x; }
int isinf(double x) { return !isnan(x) && isnan(x - x); }
}

const double c_libr_props::MW_LiBr = 0.08685; // [kg/mol]
const double c_libr_props::MW_H2O = 0.018015268; // [kg/mol]

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
    throw std::runtime_error("CoolProp doesn't know that fluid.");
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

double c_libr_props::theta(double T, double x, double * dThdT, double * dThdx )
{
  myLib::getofs() << "c_libr_props::theta(T=" << T << ",x=" << x << ") ";
  double a[] = {-2.41303e2, 1.91750e7, -1.75521e8, 3.25432e7, 3.92571e2, -2.12626e3, 1.85127e8, 1.91216e3};
  int m[] = {3,4,4,8,1,1,4,6};
  int n[] = {0,5,6,3,0,2,6,0};
  int t[] = {0,0,0,0,1,1,1,1};
  double T_c = 647.096; // [K]
  //double h_c = 37548.5; // [J/gmol] "Enthalpy at the critical point for pure water"
  // TK = convertTemp(T$,K,T)	"convert to K"
  double TK = T;
  // if (UnitSystem('mass')=1) then x=molefraction_LiBrH2O(x)
  double x_N = moleFraction(x);

  double s = 0;
  for (int i = 0; i < 8; i++) {
    s = s + a[i] * pow(x_N,m[i]) * pow(0.4-x_N,n[i]) * pow((TK/T_c),t[i]);
  }
  double Theta = TK - s;

  if (dThdT) {
    s = 0;
    for (int i = 4; i < 8; i++) {
      s = s + a[i] * pow(x_N, m[i]) * pow(0.4 - x_N, n[i]) / T_c;
    }
    * dThdT = 1 - s;
  }

  if (dThdx) {
    double s1 = 0, s2 = 0;
    for (int i = 0 ; i < 8; i++) {
      s1 = s1 + a[i] * m[i] * pow(x_N, m[i] - 1) * pow(0.4 - x_N, n[i])
          * pow(TK / T_c, t[i]);
      if (n[i] > 0) {
        s2 = s2 + a[i] * pow(x_N, m[i]) * n[i] * pow(0.4 - x_N, n[i] - 1)
            * pow(TK / T_c, t[i]);
      }
    }
    * dThdx = s2 - s1;
  }
  myLib::getofs() << "returns " << Theta << std::endl;

  return Theta;
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
  double Theta = theta(T, x);
  double Q = 0.0;
  double pressurePa = CoolProp::PropsSI("P","T",Theta,"Q",Q,"Water"); // Pa
  if (nf::isinf(pressurePa)) {
    throw std::runtime_error("CoolProp is unhappy. Temperature out of range?");
  }
  double pressureBar = pressurePa * 1e-5;

  return pressureBar;
}

/**
 * @brief c_libr_props::temperature
 * @param P = vapor pressure above liquid solution [bar]
 * @param x = LiBr mass fraction in liquid solution
 * @param T initial guess for solver [K]
 * @return T = temperature
 */
double c_libr_props::temperature(double P, double x, double T)
{
  static double Tguess = 646.;
  LiBr_TFunctor f(P, x);
  boost::uintmax_t maxiters = 100;
  int binarydigits = 16;
  if (T > 0) {
    Tguess = T;
  }
  T = boost::math::tools::newton_raphson_iterate
      <LiBr_TFunctor, double>(f, Tguess, 273.16, 647.096,
                              binarydigits, maxiters);
  Tguess = T;
  return T;
}

/**
 * @brief c_libr_props::massFraction
 * @param T = temperature [K]
 * @param P = pressure [bar]
 * @param x = guess
 * @return x = mass fraction LiBr
 * Gives the composition of a lithium bromide-water mixture at
 * the given the temprature and pressure using the formulation presented by
 * Patek and Klomfar, Int. J. of Refrigeration, Vol 29, pp. 566-578, (2006)
 * Notes: "above" the mixture: is completely water vapor. So there are only
 * two relevant properties to find equilibrium vapor pressure.
 */
double c_libr_props::massFraction(double P, double T, double x)
{
  static double xguess = 0.5;
  LiBr_XFunctor f(P, T);
  boost::uintmax_t maxiters = 20;
  int binarydigits = 32;
  if (x >= 0 && x <= 1) {
    xguess = x;
  }
  x = boost::math::tools::newton_raphson_iterate
      <LiBr_XFunctor, double>(f, xguess, 0, 1,
                              binarydigits, maxiters);
  xguess = x;
  return x;
}

/**
 * @brief c_libr_props::massSpecificEnthalpy
 * @param T = Temperature / [Kelvin]
 * @param x = mass fraction LiBr
 * @return h = mass specific enthalpy / [J/kg]
 *
 * Based on table 7 and equation (4) in reference.
 */
double c_libr_props::massSpecificEnthalpy(double T, double x)
{
  double a[] = {2.27431,-7.99511, 385.239,-16394,-422.562,0.113314,-8.33474,-17383.3,
  6.49763,3245.52,-13464.3,39932.2,-258877,-0.00193046,2.80616,-40.4479,
  145.342,-2.74873,-449.743,-12.1794,-0.00583739,0.233910,0.341888,8.85259,
  -17.8731,0.0735179,-0.000179430,0.00184261,-0.00624282,0.00684765};
  int m[] = {1,1,2,3,6,1,3,5,4,5,5,6,6,1,2,2,2,5,6,7,1,1,2,2,2,3,1,1,1,1};
  int n[] = {0,1,6,6,2,0,0,4,0,4,5,5,6,0,3,5,7,0,3,1,0,4,2,6,7,0,0,1,2,3};
  int t[] = {0,0,0,0,0,1,1,1,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5};
  double T_crit = CoolProp::Props1SI("water","Tcrit"); // [K]
  double P_crit = CoolProp::Props1SI("water","pcrit"); // [Pa]
  // This one had a problem starting around CoolProp version 5.0.8
  //double h_crit = PropsSI('H','T',T_crit,'P',P_crit,'water'); // J/kg
  // Instead, use the low-level interface
  std::unique_ptr<CoolProp::AbstractState> state(
        CoolProp::AbstractState::factory("HEOS","Water"));
  state->specify_phase(CoolProp::iphase_critical_point);
  state->update(CoolProp::PT_INPUTS, P_crit, T_crit);
  double h_c = state->hmolar(); // [J/mol]
  double T_c = T_crit; // [K]
  double T_0 = 221.; // [K] "is a nonlinear parameter of the equations"

  double TK = T;
  double x_N = moleFraction(x);

  double s = 0;
  for (int i = 0; i < 30; i++) {
      s = s + a[i] * pow(x_N, m[i]) * pow(0.4-x_N, n[i]) * pow((T_c/(TK-T_0)),t[i]);
  }
  double Qu = 0.0;
  double h_w_molar = CoolProp::PropsSI("Hmolar","T",TK,"Q",Qu,"water"); // [J/mol]
  double h_molar = (1 - x_N) * h_w_molar + h_c * s; // [J/mol] mixture
  double MW = x_N * MW_LiBr + (1 - x_N) * MW_H2O; // [kg/mol]

  double result = h_molar / MW; // [J/kg]
  myLib::getofs() << "h_c, h_w_molar, h_molar = " << h_c << ", " << h_w_molar << ", " << h_molar << std::endl;
  return result;
}

/**
 * @brief c_libr_props::massSpecificEntropy
 * @param T = Temperature / [Kelvin]
 * @param x = mass fraction LiBr
 * @return s = mass specific entropy / [J/kg-K]
 *
 * Based on table 8 and equation (5) in reference.
 */
double c_libr_props::massSpecificEntropy(double T, double x)
{
  double a[] = {1.53091,-4.52564, 698.302,-21666.4,-1475.33,0.0847012,-6.59523,
         -29533.1,0.00956314,-0.188679,9.31752,5.78104,13893.1,-17176.2,
         415.108,-55564.7,-0.00423409,30.5242,-1.67620,14.8283,0.00303055,
         -0.0401810,0.149252,2.59240,-0.177421,-0.0000699650,0.000605007,
         -0.00165228,0.00122966};
  int m[] = {1,1,2,3,6,1,3,5,1,2,2,4,5,5,6,6,1,3,5,7,1,1,1,2,3,1,1,1,1};
  int n[] = {0,1,6,6,2,0,0,4,0,0,4,0,4,5,2,5,0,4,0,1,0,2,4,7,1,0,1,2,3};
  int t[] = {0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5};
  double T_0 = 221; // [K] "is a nonlinear parameter of the equations"
  double T_crit = CoolProp::Props1SI("water","T_critical"); // [K]
  double P_crit = CoolProp::Props1SI("water","p_critical"); // [Pa]
  std::unique_ptr<CoolProp::AbstractState> state(
        CoolProp::AbstractState::factory("HEOS","Water"));
  state->specify_phase(CoolProp::iphase_critical_point);
  state->update(CoolProp::PT_INPUTS, P_crit, T_crit);
  double s_crit_molar = state->smolar(); // [J/mol-K]
  double s_c = s_crit_molar;

  double TK = T;
  double x_N = moleFraction(x);
  double s = 0;
  for (int i = 0; i < 29; i++) {
    s = s + a[i] * pow(x_N, m[i]) * pow(0.4 - x_N, n[i])
           * pow((T_crit / (TK - T_0)), t[i]);
  }
  double Qu_water = 0.0;
  double s_w_molar = CoolProp::PropsSI("Smolar","T",TK,"Q",Qu_water,"water"); // J/mol-K
  double s_molar = (1 - x_N) * s_w_molar + s_c * s;
  double MW = x_N * MW_LiBr + (1 - x_N) * MW_H2O;
  double result = s_molar / MW;
  return result;
}

/**
 * @brief c_libr_props::massSpecificHeat
 * @param T = Temperature / [Kelvin]
 * @param x = mass fraction LiBr
 * @return cp = mass specific heat / [J/kg-K]
 *
 * Based on Table 6 and equation (3) of reference.
 */
double c_libr_props::massSpecificHeat(double T, double x)
{
  double a[] = {-14.2094,40.4943,111.135,229.980,
           1345.26,-0.0141010,0.0124977,-0.000683209};
  int m[] = {2,3,3,3,3,2,1,1};
  int n[] = {0,0,1,2,3,0,3,2};
  int t[] = {0,0,0,0,0,2,3,4};
  double Cp_t = 76.0226; // [J/mol-K]
  double T_c =  647.096; // [K]
  double T_0 = 221; // [K] "is a nonlinear parameter of the equations"
  double TK = T;
  double x_N = moleFraction(x);
  double s=0;
  for (int i = 0; i < 8; i++) {
    s = s + a[i] * pow(x_N, m[i]) * pow(0.4 - x_N, n[i])
        * pow(T_c / (TK - T_0), t[i]);
  }
  double Qu_water = 0.0;
  double Cp_w_molar = CoolProp::PropsSI("Cpmolar","T",TK,"Q",Qu_water,"water"); // J/kg-K
  double Cp_molar = (1 - x_N) * Cp_w_molar + Cp_t * s;
  double MW = x_N * MW_LiBr + (1 - x_N) * MW_H2O;
  double result = Cp_molar / MW;
  return result;
}

/**
 * @brief c_libr_props::twoPhaseProps
 * @param h = mass basis enthalpy      [J/kg-K] as input
 * @param P = pressure                 [bar]     as input
 * @param z = overall LiBr composition [kg/kg]  as input
 * @param Q = quality (vapor fraction) [kg/kg]  as output
 * @param T = temperature              [K]      as output
 * @param x = liquid LiBr composition  [kg/kg]  as output
 *
 * This function returns the quality, temperature and liquid composition of a
 * 2-phase mixture of liquid lithium bromide-water and water vapor at specific
 * enthalpy h, pressure P, and overall composition, z.
 *
 * We observe that all the lithium bromide mass is in the liquid phase.
 * Therefore, a mass balance requires (1 - Q) x = z.
 * An enthalpy balance gives simply h = (1-Q) h_liquid + Q h_vapor.
 * Rearranging, (h - h_liquid) = Q (h_vapor - h_liquid).
 * Therefore we have two equations to solve for Q and x.
 * Equilibrium requires T_liquid = T_vapor, so we can use exisiting functions.
 */
void c_libr_props::twoPhaseProps(double h, double P, double z, double &Q, double &T, double &x)
{
  myLib::getofs() << "twoPhaseProps[0] h, p ,z = " << h << ", " << P << ", " << z << std::endl;
  // P_pascal = P * 1e5
  Q = 0;
  T = 0;

  Q = -100; // initial guess: subcooled.
  x = z;
  T = temperature(P, x);
  myLib::getofs() << "twoPhaseProps[1] T = " << T << std::endl;

  double hL = massSpecificEnthalpy(T,x);
  myLib::getofs() << "twoPhaseProps[2] hL = " << hL << std::endl;
  if (h == hL) Q = 0;  // saturated liquid
  if (h <= hL) return; // subcooled was right.

  Q = 0.1;
  for (int iter = 0; iter < 100; iter++) {
    double Qlast = Q;
    x = z / (1. - Q);
    T = temperature(P, x);
    hL = massSpecificEnthalpy(T,x);
    myLib::getofs() << "twoPhaseProps[3] T = " << T << std::endl;
    myLib::getofs() << "twoPhaseProps[4] hL = " << hL << std::endl;
    double hv = 0;
    if (h > hL) {
        double Q_vapor = 1.;
        hv = CoolProp::PropsSI("Hmass","T",T,"Q",Q_vapor,"Water");
        double hfg = hv - hL;
        Q = (h - hL) / (hfg);
        // double qq = (x - z) / x;
    } else {
        Q = 0.;
    }
    //print("{},h={},P={},z={},Q={},x={},T={},hL={},hv={}"
    //    .format(iter,h,P,z,Q,x,T,hL,hv))
    if ((abs(Q - Qlast) < 0.00001) && (iter > 5)) {
      break;
    }
  }
  return;
}

/**
 * @brief c_libr_props::massSpecificGibbs
 * @param T = Temperature [K]
 * @param x = liquid solution LiBr mass fraction [kg/kg]
 * @return g = mass specific Gibbs free energy [J/kg]
 */
double c_libr_props::massSpecificGibbs(double T, double x)
{
  double h = massSpecificEnthalpy(T,x); // [J/kg]
  double s = massSpecificEntropy(T,x); // [J/kg-K]
  double g = h - T * s; // [J/kg]
  return g;
}

/**
 * @brief c_libr_props::massDensity
 * @param T = temperature [K]
 * @param x = liquid solution mass fraction LiBr [kg/kg]
 * @return rho = mass volumetric density [kg/m3]
 *
 * Based on equation 2 and table 5 in the reference.
 */
double c_libr_props::massDensity(double T, double x)
{
  double a[] = {1.746,4.709};
  double m[] = {1,1};
  double t[] = {0,6};

  //rho_crit_mass = PropsSI('water','rhomass_critical') # [kg/m3]
  //rho_crit_molar = rho_crit_mass / MW_H2O # [mol/m3]
  double rho_crit_molar = CoolProp::Props1SI("water","rhomolar_critical"); // [mol/m3]
  double T_crit = CoolProp::Props1SI("water","T_critical"); // [K]

  double T_c = T_crit; // [K]
  double x_N = moleFraction(x);
  // saturated liquid water density
  double Qu_water = 0.0;
  double rhomolar_sat = CoolProp::PropsSI("Dmolar", "T", T, "Q", Qu_water, "water"); // [mol/m3]

  double s=0;
  for (int i = 0; i < 2; i++) {
      s = s + a[i] * pow(x_N, m[i]) * pow((T / T_c), t[i]);
  }
  double d_molar = (1 - x_N) * rhomolar_sat + rho_crit_molar * s;
  double MW = x_N * MW_LiBr + (1 - x_N) * MW_H2O;

  double result = d_molar * MW; // [kg/m^3]
  return result;
}

LiBr_TFunctor::LiBr_TFunctor(const double &Pbar, const double &X)
  : x(X)
{
  double pressurePa = Pbar * 1e5;
  theta = CoolProp::PropsSI("T","P",pressurePa,"Q",0.0,"water");
}

boost::math::tuple<double, double> LiBr_TFunctor::operator()(const double &Tguess)
{
  double dThdT;
  double thetaOut = c_libr_props::theta(Tguess,x,&dThdT);
  double f = (thetaOut - theta) * (thetaOut - theta); // the objective function
  double fprime = 2.0 * (thetaOut - theta) * dThdT;
  return boost::math::make_tuple(f, fprime);
}

LiBr_XFunctor::LiBr_XFunctor(double const& Pbar, double const& T)
  : T(T), iter(0)
{
  myLib::getofs() << "Entering LiBr_XFunctor constructor ..." << std::endl;
  myLib::getofs() << "Note some limits: "
                  << CoolProp::Props1SI("water","Tmin") << ", "
                  << CoolProp::Props1SI("water","Tmax") << "; "
                  << CoolProp::Props1SI("water","pmin") << ", "
                  << CoolProp::Props1SI("water","pmax") << std::endl;
  double pressurePa = Pbar * 1e5;
  myLib::logPvalue(pressurePa);
  if (pressurePa < CoolProp::Props1SI("water","pmin")) {
    throw std::runtime_error("Pressure is below limit.");
  } else if (pressurePa > CoolProp::Props1SI("water","pmax")) {
    throw std::runtime_error("Pressure is above limit.");
  } else {
    myLib::getofs() << "Pressure within limits at "
                    << std::setprecision(14) << pressurePa << " Pa." << std::endl;

  }
  try {
    double Qu = 0;
    theta = CoolProp::PropsSI("T","P",pressurePa,"Q",Qu,"water");
    myLib::getofs() << "Unexceptional." << std::endl;
  } catch (...) {
    myLib::getofs() << "Exceptional." << std::endl;
    throw std::runtime_error("Failed to get theta from P,Q!");
  }

  myLib::getofs() << "Given pressure " << pressurePa << " Pa"
                  << ", we want theta = " << std::endl;

  if (nf::isinf(theta)) {
    myLib::getofs() << "inf" << std::endl;
  } else if (nf::isnan(theta)) {
    myLib::getofs() << "nan" << std::endl;
  } else {
    myLib::getofs() << theta << "K" << std::endl;
  }
}

boost::math::tuple<double, double> LiBr_XFunctor::operator()(const double &Xguess)
{
  myLib::getofs() << "Entering LiBr_XFunctor::operator() ..." << std::endl;
  // It is bad to guess outside of the limits
  //if (Xguess < 0 || Xguess > 1) Xguess = 0.5;
  double dThdx;
  double thetaOut = c_libr_props::theta(T,Xguess,NULL,&dThdx);
  double f = (thetaOut - theta) * (thetaOut - theta); // the objective function
  double fprime = 2.0 * (thetaOut - theta) * dThdx;
  myLib::getofs() << "Xfunc: iter, Xguess, f, fprime = "
                    << iter++ << "," << Xguess << "," << f << "," << fprime << std::endl;
  return boost::math::make_tuple(f, fprime);
}
