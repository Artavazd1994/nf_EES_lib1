
// refproper.h
// 2015-05-31, Nicholas Fette
// Blueprint for object-oriented interface to refprop C library functions.

#ifndef REFPROPER_H
#define REFPROPER_H

#include "REFPROP2.H"
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class refproper
{
  static const int refpropcharlength = 255;
  static const int filepathlength = 255;
  static const int lengthofreference = 3;
  static const int errormessagelength = 255;
  // Note: ncmax is the max number of components
  static const int ncmax = 20;
  static const int numparams = 72;
  static const int maxcoefs = 50;

public:
  static refproper * factory(std::ostream &ofs);

public:
  refproper(std::ostream &ofs = std::cout,
            std::string LibPath = "C:\\Program Files (x86)\\REFPROP\\refprop.dll",
            std::string FluidPath = "C:\\Program Files (x86)\\REFPROP\\fluids\\");
  ~refproper();
  void demo();
  void setupMyFluid();
  void critp();
  void saturatedLiquidFromPressure(double p, std::vector<double> x,
                                   double &t,
                                               double &rho_l, double &rho_v,
                                               std::vector<double> &v_xliq,
                                               std::vector<double> &v_xvap);
  // subroutine PQFLSH (p,q,z,kq,t,D,Dl,Dv,x,y,e,h,s,cv,cp,w,ierr,herr)
  void saturatedStateFromPressure2(double p, double q, std::vector<double> x,
                                   double &t, double &D,
                                   double &h, double &s);
  void thermalProperties(double t, double rho, std::vector<double> x,
                         double &p, double &e, double &h, double &s);


  // Log output stream
  std::ostream &mofs;
  // DLL path and module
  const std::string mLibPath;
  HINSTANCE RefpropdllInstance;
  // Explicitely set the fluid file PATH
  const std::string mFLD_PATH;

public:
  fp_ABFL1dllTYPE ABFL1dll;
  fp_ABFL2dllTYPE ABFL2dll;
  fp_ACTVYdllTYPE ACTVYdll;
  fp_AGdllTYPE AGdll;
  fp_CCRITdllTYPE CCRITdll;
  fp_CP0dllTYPE CP0dll;
  fp_CRITPdllTYPE CRITPdll;
  fp_CSATKdllTYPE CSATKdll;
  fp_CV2PKdllTYPE CV2PKdll;
  fp_CVCPKdllTYPE CVCPKdll;
  fp_CVCPdllTYPE CVCPdll;
  fp_DBDTdllTYPE DBDTdll;
  fp_DBFL1dllTYPE DBFL1dll;
  fp_DBFL2dllTYPE DBFL2dll;
  fp_DDDPdllTYPE DDDPdll;
  fp_DDDTdllTYPE DDDTdll;
  fp_DEFLSHdllTYPE DEFLSHdll;
  fp_DHD1dllTYPE DHD1dll;
  fp_DHFLSHdllTYPE DHFLSHdll;
  fp_DIELECdllTYPE DIELECdll;
  fp_DOTFILLdllTYPE DOTFILLdll;
  fp_DPDD2dllTYPE DPDD2dll;
  fp_DPDDKdllTYPE DPDDKdll;
  fp_DPDDdllTYPE DPDDdll;
  fp_DPDTKdllTYPE DPDTKdll;
  fp_DPDTdllTYPE DPDTdll;
  fp_DPTSATKdllTYPE DPTSATKdll;
  fp_DSFLSHdllTYPE DSFLSHdll;
  fp_ENTHALdllTYPE ENTHALdll;
  fp_ENTROdllTYPE ENTROdll;
  fp_ESFLSHdllTYPE ESFLSHdll;
  fp_FGCTYdllTYPE FGCTYdll;
  fp_FPVdllTYPE FPVdll;
  fp_GERG04dllTYPE GERG04dll;
  fp_GETFIJdllTYPE GETFIJdll;
  fp_GETKTVdllTYPE GETKTVdll;
  fp_GIBBSdllTYPE GIBBSdll;
  fp_HSFLSHdllTYPE HSFLSHdll;
  fp_INFOdllTYPE INFOdll;
  fp_LIMITKdllTYPE LIMITKdll;
  fp_LIMITSdllTYPE LIMITSdll;
  fp_LIMITXdllTYPE LIMITXdll;
  fp_MELTPdllTYPE MELTPdll;
  fp_MELTTdllTYPE MELTTdll;
  fp_MLTH2OdllTYPE MLTH2Odll;
  fp_NAMEdllTYPE NAMEdll;
  fp_PDFL1dllTYPE PDFL1dll;
  fp_PDFLSHdllTYPE PDFLSHdll;
  fp_PEFLSHdllTYPE PEFLSHdll;
  fp_PHFL1dllTYPE PHFL1dll;
  fp_PHFLSHdllTYPE PHFLSHdll;
  fp_PQFLSHdllTYPE PQFLSHdll;
  fp_PREOSdllTYPE PREOSdll;
  fp_PRESSdllTYPE PRESSdll;
  fp_PSFL1dllTYPE PSFL1dll;
  fp_PSFLSHdllTYPE PSFLSHdll;
  fp_PUREFLDdllTYPE PUREFLDdll;
  fp_QMASSdllTYPE QMASSdll;
  fp_QMOLEdllTYPE QMOLEdll;
  fp_SATDdllTYPE SATDdll;
  fp_SATEdllTYPE SATEdll;
  fp_SATHdllTYPE SATHdll;
  fp_SATPdllTYPE SATPdll;
  fp_SATSdllTYPE SATSdll;
  fp_SATTdllTYPE SATTdll;
  fp_SETAGAdllTYPE SETAGAdll;
  fp_SETKTVdllTYPE SETKTVdll;
  fp_SETMIXdllTYPE SETMIXdll;
  fp_SETMODdllTYPE SETMODdll;
  fp_SETREFdllTYPE SETREFdll;
  fp_SETUPdllTYPE SETUPdll;
  fp_SPECGRdllTYPE SPECGRdll;
  fp_SUBLPdllTYPE SUBLPdll;
  fp_SUBLTdllTYPE SUBLTdll;
  fp_SURFTdllTYPE SURFTdll;
  fp_SURTENdllTYPE SURTENdll;
  fp_TDFLSHdllTYPE TDFLSHdll;
  fp_TEFLSHdllTYPE TEFLSHdll;
  fp_THERM0dllTYPE THERM0dll;
  fp_THERM2dllTYPE THERM2dll;
  fp_THERM3dllTYPE THERM3dll;
  fp_THERMdllTYPE THERMdll;
  fp_THFLSHdllTYPE THFLSHdll;
  fp_TPFLSHdllTYPE TPFLSHdll;
  fp_TPRHOdllTYPE TPRHOdll;
  fp_TQFLSHdllTYPE TQFLSHdll;
  fp_TRNPRPdllTYPE TRNPRPdll;
  fp_TSFLSHdllTYPE TSFLSHdll;
  fp_VIRBdllTYPE VIRBdll;
  fp_VIRCdllTYPE VIRCdll;
  fp_WMOLdllTYPE WMOLdll;
  fp_XMASSdllTYPE XMASSdll;
  fp_XMOLEdllTYPE XMOLEdll;
};


#endif // REFPROPER_H
