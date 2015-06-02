// refproper.cpp
// 2015-05-31, Nicholas Fette

// Based on code from:
// EX_C2.c written by:
// Ian Bell
// Herrick Labs
// Purdue University
// ibell@purdue.edu
// August 31, 2010

// heavily based on example file EX_C1.cpp by

// Chris Muzny
// N.I.S.T.
// Chemical Science and Technology Laboratory
// Physical and Chemical Properties of Fluids Division
// (303) 497-5549
// chris.muzny@nist.gov

//This program demonstrates explicitly linking the subroutines available in
// refprop.dll.  In order to link this code refprop1.h
// must be available in the current directory.  When executing refprop.dll must be in the dll
// search path (current directory and $PATH).

#include "refproper.h"
#include <windows.h>
#include <stdio.h>
#include <iomanip>

#undef UNICODE

refproper::refproper(std::ostream &ofs, std::string LibPath, std::string FluidPath) :
mofs(ofs),
mFLD_PATH(FluidPath),
mLibPath(LibPath)
{

  // First create a pointer to an instance of the library
  // Then have windows load the library.
  //HINSTANCE RefpropdllInstance;
  // This looks only in the current directory for refprop.dll
  char const * const cLibPath = mLibPath.c_str();
  RefpropdllInstance = LoadLibraryA(cLibPath);
  mofs << "refproper: in constructor." << std::endl;
  if (RefpropdllInstance) {
    mofs << "refproper: Loaded the library!" << std::endl;
  } else {
    mofs << "refproper: Did not load the library! Watch out now." << std::endl;
    throw std::exception("refproper: Failed to load the library! Giants, flames, death and despair.");
  }

  // Then get pointers into the dll to the actual functions.
  ABFL1dll = (fp_ABFL1dllTYPE) GetProcAddress(RefpropdllInstance,"ABFL1dll");
  ABFL2dll = (fp_ABFL2dllTYPE) GetProcAddress(RefpropdllInstance,"ABFL2dll");
  ACTVYdll = (fp_ACTVYdllTYPE) GetProcAddress(RefpropdllInstance,"ACTVYdll");
  AGdll = (fp_AGdllTYPE) GetProcAddress(RefpropdllInstance,"AGdll");
  CCRITdll = (fp_CCRITdllTYPE) GetProcAddress(RefpropdllInstance,"CCRITdll");
  CP0dll = (fp_CP0dllTYPE) GetProcAddress(RefpropdllInstance,"CP0dll");
  CRITPdll = (fp_CRITPdllTYPE) GetProcAddress(RefpropdllInstance,"CRITPdll");
  CSATKdll = (fp_CSATKdllTYPE) GetProcAddress(RefpropdllInstance,"CSATKdll");
  CV2PKdll = (fp_CV2PKdllTYPE) GetProcAddress(RefpropdllInstance,"CV2PKdll");
  CVCPKdll = (fp_CVCPKdllTYPE) GetProcAddress(RefpropdllInstance,"CVCPKdll");
  CVCPdll = (fp_CVCPdllTYPE) GetProcAddress(RefpropdllInstance,"CVCPdll"); //**
  DBDTdll = (fp_DBDTdllTYPE) GetProcAddress(RefpropdllInstance,"DBDTdll");
  DBFL1dll = (fp_DBFL1dllTYPE) GetProcAddress(RefpropdllInstance,"DBFL1dll");
  DBFL2dll = (fp_DBFL2dllTYPE) GetProcAddress(RefpropdllInstance,"DBFL2dll");
  DDDPdll = (fp_DDDPdllTYPE) GetProcAddress(RefpropdllInstance,"DDDPdll");
  DDDTdll = (fp_DDDTdllTYPE) GetProcAddress(RefpropdllInstance,"DDDTdll");
  DEFLSHdll = (fp_DEFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"DEFLSHdll");
  DHD1dll = (fp_DHD1dllTYPE) GetProcAddress(RefpropdllInstance,"DHD1dll");
  DHFLSHdll = (fp_DHFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"DHFLSHdll");
  DIELECdll = (fp_DIELECdllTYPE) GetProcAddress(RefpropdllInstance,"DIELECdll");
  DOTFILLdll = (fp_DOTFILLdllTYPE) GetProcAddress(RefpropdllInstance,"DOTFILLdll");
  DPDD2dll = (fp_DPDD2dllTYPE) GetProcAddress(RefpropdllInstance,"DPDD2dll");
  DPDDKdll = (fp_DPDDKdllTYPE) GetProcAddress(RefpropdllInstance,"DPDDKdll");
  DPDDdll = (fp_DPDDdllTYPE) GetProcAddress(RefpropdllInstance,"DPDDdll");
  DPDTKdll = (fp_DPDTKdllTYPE) GetProcAddress(RefpropdllInstance,"DPDTKdll");
  DPDTdll = (fp_DPDTdllTYPE) GetProcAddress(RefpropdllInstance,"DPDTdll");
  DPTSATKdll = (fp_DPTSATKdllTYPE) GetProcAddress(RefpropdllInstance,"DPTSATKdll");
  DSFLSHdll = (fp_DSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"DSFLSHdll");
  ENTHALdll = (fp_ENTHALdllTYPE) GetProcAddress(RefpropdllInstance,"ENTHALdll"); //**
  ENTROdll = (fp_ENTROdllTYPE) GetProcAddress(RefpropdllInstance,"ENTROdll");
  ESFLSHdll = (fp_ESFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"ESFLSHdll");
  FGCTYdll = (fp_FGCTYdllTYPE) GetProcAddress(RefpropdllInstance,"FGCTYdll");
  FPVdll = (fp_FPVdllTYPE) GetProcAddress(RefpropdllInstance,"FPVdll");
  GERG04dll = (fp_GERG04dllTYPE) GetProcAddress(RefpropdllInstance,"GERG04dll");
  GETFIJdll = (fp_GETFIJdllTYPE) GetProcAddress(RefpropdllInstance,"GETFIJdll");
  GETKTVdll = (fp_GETKTVdllTYPE) GetProcAddress(RefpropdllInstance,"GETKTVdll");
  GIBBSdll = (fp_GIBBSdllTYPE) GetProcAddress(RefpropdllInstance,"GIBBSdll");
  HSFLSHdll = (fp_HSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"HSFLSHdll");
  INFOdll = (fp_INFOdllTYPE) GetProcAddress(RefpropdllInstance,"INFOdll");
  LIMITKdll = (fp_LIMITKdllTYPE) GetProcAddress(RefpropdllInstance,"LIMITKdll");
  LIMITSdll = (fp_LIMITSdllTYPE) GetProcAddress(RefpropdllInstance,"LIMITSdll");
  LIMITXdll = (fp_LIMITXdllTYPE) GetProcAddress(RefpropdllInstance,"LIMITXdll");
  MELTPdll = (fp_MELTPdllTYPE) GetProcAddress(RefpropdllInstance,"MELTPdll");
  MELTTdll = (fp_MELTTdllTYPE) GetProcAddress(RefpropdllInstance,"MELTTdll");
  MLTH2Odll = (fp_MLTH2OdllTYPE) GetProcAddress(RefpropdllInstance,"MLTH2Odll");
  NAMEdll = (fp_NAMEdllTYPE) GetProcAddress(RefpropdllInstance,"NAMEdll");
  PDFL1dll = (fp_PDFL1dllTYPE) GetProcAddress(RefpropdllInstance,"PDFL1dll");
  PDFLSHdll = (fp_PDFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PDFLSHdll");
  PEFLSHdll = (fp_PEFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PEFLSHdll");
  PHFL1dll = (fp_PHFL1dllTYPE) GetProcAddress(RefpropdllInstance,"PHFL1dll");
  PHFLSHdll = (fp_PHFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PHFLSHdll");
  PQFLSHdll = (fp_PQFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PQFLSHdll");
  PREOSdll = (fp_PREOSdllTYPE) GetProcAddress(RefpropdllInstance,"PREOSdll");
  PRESSdll = (fp_PRESSdllTYPE) GetProcAddress(RefpropdllInstance,"PRESSdll");
  PSFL1dll = (fp_PSFL1dllTYPE) GetProcAddress(RefpropdllInstance,"PSFL1dll");
  PSFLSHdll = (fp_PSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PSFLSHdll");
  PUREFLDdll = (fp_PUREFLDdllTYPE) GetProcAddress(RefpropdllInstance,"PUREFLDdll");
  QMASSdll = (fp_QMASSdllTYPE) GetProcAddress(RefpropdllInstance,"QMASSdll");
  QMOLEdll = (fp_QMOLEdllTYPE) GetProcAddress(RefpropdllInstance,"QMOLEdll");
  SATDdll = (fp_SATDdllTYPE) GetProcAddress(RefpropdllInstance,"SATDdll");
  SATEdll = (fp_SATEdllTYPE) GetProcAddress(RefpropdllInstance,"SATEdll");
  SATHdll = (fp_SATHdllTYPE) GetProcAddress(RefpropdllInstance,"SATHdll");
  SATPdll = (fp_SATPdllTYPE) GetProcAddress(RefpropdllInstance,"SATPdll");
  SATSdll = (fp_SATSdllTYPE) GetProcAddress(RefpropdllInstance,"SATSdll");
  SATTdll = (fp_SATTdllTYPE) GetProcAddress(RefpropdllInstance,"SATTdll");
  SETAGAdll = (fp_SETAGAdllTYPE) GetProcAddress(RefpropdllInstance,"SETAGAdll");
  SETKTVdll = (fp_SETKTVdllTYPE) GetProcAddress(RefpropdllInstance,"SETKTVdll");
  SETMIXdll = (fp_SETMIXdllTYPE) GetProcAddress(RefpropdllInstance,"SETMIXdll");
  SETMODdll = (fp_SETMODdllTYPE) GetProcAddress(RefpropdllInstance,"SETMODdll");
  SETREFdll = (fp_SETREFdllTYPE) GetProcAddress(RefpropdllInstance,"SETREFdll");
  SETUPdll = (fp_SETUPdllTYPE) GetProcAddress(RefpropdllInstance,"SETUPdll");
  SPECGRdll = (fp_SPECGRdllTYPE) GetProcAddress(RefpropdllInstance,"SPECGRdll");
  SUBLPdll = (fp_SUBLPdllTYPE) GetProcAddress(RefpropdllInstance,"SUBLPdll");
  SUBLTdll = (fp_SUBLTdllTYPE) GetProcAddress(RefpropdllInstance,"SUBLTdll");
  SURFTdll = (fp_SURFTdllTYPE) GetProcAddress(RefpropdllInstance,"SURFTdll");
  SURTENdll = (fp_SURTENdllTYPE) GetProcAddress(RefpropdllInstance,"SURTENdll");
  TDFLSHdll = (fp_TDFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TDFLSHdll");
  TEFLSHdll = (fp_TEFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TEFLSHdll");
  THERM0dll = (fp_THERM0dllTYPE) GetProcAddress(RefpropdllInstance,"THERM0dll");
  THERM2dll = (fp_THERM2dllTYPE) GetProcAddress(RefpropdllInstance,"THERM2dll");
  THERM3dll = (fp_THERM3dllTYPE) GetProcAddress(RefpropdllInstance,"THERM3dll");
  THERMdll = (fp_THERMdllTYPE) GetProcAddress(RefpropdllInstance,"THERMdll");
  THFLSHdll = (fp_THFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"THFLSHdll");
  TPFLSHdll = (fp_TPFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TPFLSHdll");
  TPRHOdll = (fp_TPRHOdllTYPE) GetProcAddress(RefpropdllInstance,"TPRHOdll");
  TQFLSHdll = (fp_TQFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TQFLSHdll");
  TRNPRPdll = (fp_TRNPRPdllTYPE) GetProcAddress(RefpropdllInstance,"TRNPRPdll");
  TSFLSHdll = (fp_TSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TSFLSHdll");
  VIRBdll = (fp_VIRBdllTYPE) GetProcAddress(RefpropdllInstance,"VIRBdll");
  VIRCdll = (fp_VIRCdllTYPE) GetProcAddress(RefpropdllInstance,"VIRCdll");
  WMOLdll = (fp_WMOLdllTYPE) GetProcAddress(RefpropdllInstance,"WMOLdll");
  XMASSdll = (fp_XMASSdllTYPE) GetProcAddress(RefpropdllInstance,"XMASSdll");
  XMOLEdll = (fp_XMOLEdllTYPE) GetProcAddress(RefpropdllInstance,"XMOLEdll");

}

refproper::~refproper()
{
  mofs << "refproper: In object destructor" << std::endl;
  if (FreeLibrary(RefpropdllInstance)) {
    mofs << "refproper: Successfully unloaded the library." << std::endl;
  } else {
    mofs << "refproper: Failed to unload the library." << std::endl;
  }
}

void refproper::demo()
{
  // Now use the functions.

  // Refprop variables that need to be defined
  //
  // nc = Number of components in the mixture
  // x[NumberOfComponentsInMixtures] = Mole fraction of each component
  // ierr =  An integer flag defining an error
  // hf[] = a character array defining the fluids in a mixture
  // hrf[] = a character array denoting the reference state
  // herr[] = a character array for storing a string - Error message
  // hfmix[] a character array defining the path to the mixture file

  double x[ncmax],xliq[ncmax],xvap[ncmax],f[ncmax];

  long i,ierr;
  char hf[refpropcharlength*ncmax], hrf[lengthofreference+1],
      herr[errormessagelength+1],hfmix[refpropcharlength+1];

  double wm,ttp,tnbp,tc,pc,dc,zc,acf,dip,rgas;
  long info_index;
  double t;
  double p,dl,dv;
  long j;
  double d,q,e,h,s,cv,cp,w,b,c,
      dpdrho,d2pdd2,dpdt,dhdt_d,dhdt_p,dhdp_t,dhdp_d,
      sigma,dhdd_t,dhdd_p,eta,tcx,pp,tt,hjt,h1,dd;
  long tmp_int;
  long kr;

  ierr=0;
  info_index=1;
  t=100.0;
  j=1;
  d=0.0,q=0.0,e=0.0,h=0.0,s=0.0,cv=0.0,cp=0.0,w=0.0,b=0.0,c=0.0;
  tmp_int=0;
  kr=1;

  //...For a mixture, use the following setup.
  // Use "|" as the file name delimiter for mixtures
  i=3;
  std::string str_hf = mFLD_PATH + "nitrogen.fld|" + mFLD_PATH + "argon.fld|" + mFLD_PATH + "oxygen.fld";
  strncpy(hf, str_hf.c_str(), refpropcharlength*ncmax);
  std::string str_hfmix = mFLD_PATH + "hmx.bnc";
  strncpy(hfmix,str_hfmix.c_str(), refpropcharlength+1);
  strncpy(hrf,"DEF", lengthofreference+1);
  strncpy(herr,"Ok", errormessagelength+1);
  x[0]=.7812;     //Air composition
  x[1]=.0092;
  x[2]=.2096;

  mofs << "some blank lines "  << std::endl << std::endl;
  mofs << "hf = "    << hf     << std::endl;
  mofs << "hfmix = " << hfmix  << std::endl;
  mofs << "hrf = "   << hrf    << std::endl;
  mofs << "herr = "  << herr   << std::endl;

  //...Call SETUP to initialize the program
  SETUPdll(&i, hf, hfmix, hrf, &ierr, herr,
      refpropcharlength*ncmax,refpropcharlength,
      lengthofreference,errormessagelength);
  //long ,char*,char*,char*,long ,char*,long ,long ,long ,long
  if (ierr != 0) {
    mofs << herr << std::endl;
    return;
    // TODO: throw something
  }

  INFOdll(&info_index,&wm,&ttp,&tnbp,&tc,&pc,&dc,&zc,&acf,&dip,&rgas);
  mofs << "WM,ACF,DIP,TTP,TNBP   "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << wm << ","
          << std::setw(10) << std::setprecision(4) << acf << ","
          << std::setw(10) << std::setprecision(4) << dip << ","
          << std::setw(10) << std::setprecision(4) << ttp << ","
          << std::setw(10) << std::setprecision(4) << tnbp
          << std::endl;
  mofs << "TC,PC,DC,RGAS         "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << tc << ","
          << std::setw(10) << std::setprecision(4) << pc << ","
          << std::setw(10) << std::setprecision(4) << dc << ","
          << std::setw(10) << std::setprecision(4) << rgas
          << std::endl;

  //...Calculate molecular weight of a mixture
  //wm=WMOLdll(x)

  //...Get saturation properties given t,x; for i=1: x is liquid phase
  //.....                                   for i=2: x is vapor phase
  i=1;
  SATTdll(&t,x,&i,&p,&dl,&dv,xliq,xvap,&ierr,herr,errormessagelength);
  mofs << "P,Dl,Dv,xl[0],xv[0]   "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << p << ","
          << std::setw(10) << std::setprecision(4) << dl << ","
          << std::setw(10) << std::setprecision(4) << dv << ","
          << std::setw(10) << std::setprecision(4) << xliq[0] << ","
          << std::setw(10) << std::setprecision(4) << xvap[0]
          << std::endl;
  i=2;
  SATTdll(&t,x,&i,&p,&dl,&dv,xliq,xvap,&ierr,herr,errormessagelength);
  mofs << "P,Dl,Dv,xl[0],xv[0]   "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << p << ","
          << std::setw(10) << std::setprecision(4) << dl << ","
          << std::setw(10) << std::setprecision(4) << dv << ","
          << std::setw(10) << std::setprecision(4) << xliq[0] << ","
          << std::setw(10) << std::setprecision(4) << xvap[0]
          << std::endl;

  //...Calculate saturation properties at a given p. i is same as SATT
  i=2;
  SATPdll(&p,x,&i,&t,&dl,&dv,xliq,xvap,&ierr,herr,errormessagelength);
  // TOOD: This string may not be in agreement with the output variables...
  mofs << "T,Dl,Dv,xl(1),xv(1)   "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << t << ","
          << std::setw(10) << std::setprecision(4) << dl << ","
          << std::setw(10) << std::setprecision(4) << dv << ","
          << std::setw(10) << std::setprecision(4) << xliq[0] << ","
          << std::setw(10) << std::setprecision(4) << xvap[0]
          << std::endl;

  //...Other saturation routines are given in SAT_SUB.FOR
  t=300.0;
  p=20000.0;

  //...Calculate d from t,p,x
  //...If phase is known: (j=1: Liquid, j=2: Vapor)
  TPRHOdll(&t,&p,x,&j,&tmp_int,&d,&ierr,herr,errormessagelength);
  mofs << "T,P,D                 "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << t << ","
       << std::setw(10) << std::setprecision(4) << p << ","
       << std::setw(10) << std::setprecision(4) << d
       << std::endl;

  //...If phase is not known, call TPFLSH
  //...Calls to TPFLSH are much slower than TPRHO since SATT must be called first.
  //.....(If two phase, quality is returned as q)

  TPFLSHdll(&t,&p,x,&d,&dl,&dv,xliq,xvap,&q,&e,&h,&s,&cv,&cp,&w,&ierr,herr,errormessagelength);
  mofs << "T,P,D,H,CP            "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << t << ","
       << std::setw(10) << std::setprecision(4) << p << ","
       << std::setw(10) << std::setprecision(4) << d << ","
       << std::setw(10) << std::setprecision(4) << h << ","
       << std::setw(10) << std::setprecision(4) << cp
       << std::endl;

  //...Calculate pressure (p), internal energy (e), enthalpy (h), entropy (s),
  //.....isochoric (cv) and isobaric (cp) heat capacities, speed of sound (w),
  //.....and Joule-Thomson coefficient (hjt) from t,d,x
  //.....(subroutines THERM2 and THERM3 contain more properties, see PROP_SUB.FOR)
  THERMdll(&t,&d,x,&p,&e,&h,&s,&cv,&cp,&w,&hjt);

  //...Calculate pressure
  PRESSdll(&t,&d,x,&p);

  //...Calculate fugacity
  FGCTYdll(&t,&d,x,f);

  //...Calculate second and third virial coefficients
  VIRBdll (&t,x,&b);
  VIRCdll (&t,x,&c);
  mofs << "F,B,C                 "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << f[0] << ","
       << std::setw(10) << std::setprecision(4) << b << ","
       << std::setw(10) << std::setprecision(4) << c
       << std::endl;

  //
  //...Calculate the derivatives: dP/dD, d^2P/dD^2, dP/dT  (D indicates density)
  //...(dD/dP, dD/dT, and dB/dT are also available, see PROP_SUB.FOR)
  DPDDdll (&t,&d,x,&dpdrho);
  DPDD2dll (&t,&d,x,&d2pdd2);
  DPDTdll (&t,&d,x,&dpdt);
  mofs << "dP/dD,d2P/dD2,dP/dT   "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << dpdrho << ","
       << std::setw(10) << std::setprecision(4) << d2pdd2 << ","
       << std::setw(10) << std::setprecision(4) << dpdt
       << std::endl;

  //...Calculate derivatives of enthalpy with respect to T, P, and D
  DHD1dll(&t,&d,x,&dhdt_d,&dhdt_p,&dhdd_t,&dhdd_p,&dhdp_t,&dhdp_d);
  mofs << "Enthalpy derivatives  "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << dhdt_d << ","
       << std::setw(10) << std::setprecision(4) << dhdt_p << ","
       << std::setw(10) << std::setprecision(4) << dhdd_t << ","
       << std::setw(10) << std::setprecision(4) << dhdd_p/1000.0 << ","
       << std::setw(10) << std::setprecision(4) << dhdp_t
       << std::endl;

  //...Calculate surface tension
  SURFTdll (&t,&dl,x,&sigma,&ierr,herr,errormessagelength);
  mofs << "T,SURF. TN.           "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << t << ","
       << std::setw(10) << std::setprecision(4) << sigma
       << std::endl;

  //...Calculate viscosity (eta) and thermal conductivity (tcx)
  TRNPRPdll (&t,&d,x,&eta,&tcx,&ierr,herr,errormessagelength);
  mofs << "VIS.,TH.CND.          "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << eta << ","
       << std::setw(10) << std::setprecision(4) << tcx*1000.0
       << std::endl;

  //...General property calculation with inputs of t,d,x
  TDFLSHdll (&t,&d,x,&pp,&dl,&dv,xliq,xvap,&q,&e,&h1,&s,&cv,&cp,&w,&ierr,herr,errormessagelength);
  mofs << "T, D, P from TDFLSH   "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << t << ","
       << std::setw(10) << std::setprecision(4) << d << ","
       << std::setw(10) << std::setprecision(4) << pp/1000.0
       << std::endl;

  //...General property calculation with inputs of p,d,x
  PDFLSHdll (&p,&d,x,&tt,&dl,&dv,xliq,xvap,&q,&e,&h1,&s,&cv,&cp,&w,&ierr,herr,errormessagelength);
  mofs << "T, D, P from PDFLSH   "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << tt << ","
       << std::setw(10) << std::setprecision(4) << d << ","
       << std::setw(10) << std::setprecision(4) << p/1000.0
       << std::endl;

  //...General property calculation with inputs of p,h,x
  PHFLSHdll (&p,&h,x,&tt,&dd,&dl,&dv,xliq,xvap,&q,&e,&s,&cv,&cp,&w,&ierr,herr,errormessagelength);
  mofs << "T, D, P from PHFLSH   "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << tt << ","
       << std::setw(10) << std::setprecision(4) << dd << ","
       << std::setw(10) << std::setprecision(4) << p/1000.0
       << std::endl;

  //...General property calculation with inputs of p,s,x
  PSFLSHdll (&p,&s,x,&tt,&dd,&dl,&dv,xliq,xvap,&q,&e,&h1,&cv,&cp,&w,&ierr,herr,errormessagelength);
  mofs << "T, D, P from PSFLSH   "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << tt << ","
       << std::setw(10) << std::setprecision(4) << dd << ","
       << std::setw(10) << std::setprecision(4) << p/1000.0
       << std::endl;

  //...General property calculation with inputs of d,h,x
  DHFLSHdll (&d,&h,x,&tt,&pp,&dl,&dv,xliq,xvap,&q,&e,&s,&cv,&cp,&w,&ierr,herr,errormessagelength);
  mofs << "T, D, P from DHFLSH   "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << tt << ","
       << std::setw(10) << std::setprecision(4) << d << ","
       << std::setw(10) << std::setprecision(4) << pp/1000.0
       << std::endl;

  //...General property calculation with inputs of t,h,x
  //     kr--flag specifying desired root for multi-valued inputs:
  //         1=return lower density root
  //         2=return higher density root

  THFLSHdll (&t,&h,x,
              &kr,&pp,&dd,&dl,&dv,xliq,xvap,&q,&e,&s,&cv,&cp,&w,&ierr,herr,errormessagelength);
  mofs << "T, D, P from THFLSH   "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << t << ","
       << std::setw(10) << std::setprecision(4) << dd << ","
       << std::setw(10) << std::setprecision(4) << pp/1000.0
       << std::endl;

  //...Other general property calculation routines are given in FLSH_SUB.FOR
  //...and FLASH2.FOR

  //...Calculate melting pressure
  t=100.0;
  MELTTdll (&t,x,&p,&ierr,herr,errormessagelength);
  mofs << "Melting pressure(MPa) "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << p/1000.0 << ","
       << std::setw(10) << std::setprecision(4) << t
       << std::endl;

  //...Calculate melting temperature
  MELTPdll (&p,x,&tt,&ierr,herr,errormessagelength);
  mofs << "Melting temperature(K)"
       << std::fixed
       << std::setw(10) << std::setprecision(4) << tt << ","
       << std::setw(10) << std::setprecision(4) << p/1000.0
       << std::endl;

  //...Calculate sublimation pressure
  t=200.0;
  SUBLTdll (&t,x,&p,&ierr,herr,errormessagelength);
  mofs << "Sublimation pr.(kPa)  "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << p << ","
       << std::setw(10) << std::setprecision(4) << t
       << std::endl;

  //...Calculate sublimation temperature
  SUBLPdll (&p,x,&tt,&ierr,herr,errormessagelength);
  mofs << "Sublimation temp.(K)  "
       << std::fixed
       << std::setw(10) << std::setprecision(4) << tt << ","
       << std::setw(10) << std::setprecision(4) << p
       << std::endl;

  //...Get limits of the equations and check if t,d,p is a valid point
  //...Equation of state
  //     call LIMITK ('EOS',1,t,d,p,tmin,tmax,Dmax,pmax,ierr,herr)
  //...Viscosity equation
  //     call LIMITK ('ETA',1,t,d,p,tmin,tmax,Dmax,pmax,ierr,herr)
  //...Thermal conductivity equation
  //     call LIMITK ('TCX',1,t,d,p,tmin,tmax,Dmax,pmax,ierr,herr)

  //...Other routines are given in UTILITY.FOR

}

void refproper::setupMyFluid()
{
  long ierr;
  char hf[refpropcharlength*ncmax], hrf[lengthofreference+1],
      herr[errormessagelength+1],hfmix[refpropcharlength+1];
  double x[ncmax];

  //...For a mixture, use the following setup.
  // Use "|" as the file name delimiter for mixtures
  long nc = 2;
  std::string str_hf = mFLD_PATH + "ETHANOL.FLD|" + mFLD_PATH + "WATER.FLD";
  strncpy(hf, str_hf.c_str(), refpropcharlength*ncmax);
  std::string str_hfmix = mFLD_PATH + "hmx.bnc";
  strncpy(hfmix,str_hfmix.c_str(), refpropcharlength);
  strncpy(hrf,"DEF", lengthofreference);
  strncpy(herr,"Ok", errormessagelength);
  x[0] = 0.206791740960598;     // Mixture molar composition
  x[1] = 0.793208259039402;
  x[2] = 0;

  mofs << "some blank lines "  << std::endl << std::endl;
  mofs << "hf = "    << hf     << std::endl;
  mofs << "hfmix = " << hfmix  << std::endl;
  mofs << "hrf = "   << hrf    << std::endl;
  mofs << "herr = "  << herr   << std::endl;

  //...Call SETUP to initialize the program
  SETUPdll(&nc, hf, hfmix, hrf, &ierr, herr,
      refpropcharlength*ncmax,refpropcharlength,
      lengthofreference,errormessagelength);
  //long ,char*,char*,char*,long ,char*,long ,long ,long ,long
  if (ierr != 0) {
    mofs << herr << std::endl;
    throw std::exception("refproper: error: failed to initialize mixture.");
  }
}

void refproper::critp()
{
  double x[ncmax],xliq[ncmax],xvap[ncmax],f[ncmax];

  long i,ierr;
  char hf[refpropcharlength*ncmax], hrf[lengthofreference+1],
      herr[errormessagelength+1],hfmix[refpropcharlength+1];

  double wm,ttp,tnbp,tc,pc,dc,zc,acf,dip,rgas;
  long info_index;
  double t;
  double p,dl,dv;
  long j;
  double d,q,e,h,s,cv,cp,w,b,c,
      dpdrho,d2pdd2,dpdt,dhdt_d,dhdt_p,dhdp_t,dhdp_d,
      sigma,dhdd_t,dhdd_p,eta,tcx,pp,tt,hjt,h1,dd;
  long tmp_int;
  long kr;

  ierr=0;
  info_index=1;
  t=100.0;
  j=1;
  d=0.0,q=0.0,e=0.0,h=0.0,s=0.0,cv=0.0,cp=0.0,w=0.0,b=0.0,c=0.0;
  tmp_int=0;
  kr=1;

  mofs << "According to INFOdll:" << std::endl;
  INFOdll(&info_index,&wm,&ttp,&tnbp,&tc,&pc,&dc,&zc,&acf,&dip,&rgas);
  mofs << "WM,ACF,DIP,TTP,TNBP   "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << wm << ","
          << std::setw(10) << std::setprecision(4) << acf << ","
          << std::setw(10) << std::setprecision(4) << dip << ","
          << std::setw(10) << std::setprecision(4) << ttp << ","
          << std::setw(10) << std::setprecision(4) << tnbp
          << std::endl;
  mofs << "TC,PC,DC,RGAS         "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << tc << ","
          << std::setw(10) << std::setprecision(4) << pc << ","
          << std::setw(10) << std::setprecision(4) << dc << ","
          << std::setw(10) << std::setprecision(4) << rgas
          << std::endl;

  mofs << "According to CRITPdll:" << std::endl;
  // (double *,double *,double *,double *,long *,char*,long );
  CRITPdll(x, &tc, &pc, &dc, &ierr, herr, errormessagelength);
  mofs << "TC,PC,DC              "
          << std::fixed
          << std::setw(10) << std::setprecision(4) << tc << ","
          << std::setw(10) << std::setprecision(4) << pc << ","
          << std::setw(10) << std::setprecision(4) << dc << ","
          << std::endl;
  if (ierr != 0) {
    mofs << "Call to CRITPdll gave an error code " << ierr << std::endl;
    mofs << "and a message: " << herr << std::endl;
    mofs << "Be wary of the following calculation." << std::endl;
  }
  // (double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *);
  THERMdll(&tc, &dc, x, &pc, &e, &h, &s, &cv, &cp, &w, &hjt);
  mofs << "According to THERMdll, that state point is:" << std::endl;
  mofs
      << "t(in)= " << std::setw(10) << std::setprecision(4) << tc   << std::endl
      << "d(in)= " << std::setw(10) << std::setprecision(4) << dc   << std::endl
      << "pc   = " << std::setw(10) << std::setprecision(4) << pc  << std::endl
      << "e    = " << std::setw(10) << std::setprecision(4) << e   << std::endl
      << "h    = " << std::setw(10) << std::setprecision(4) << h   << std::endl
      << "s    = " << std::setw(10) << std::setprecision(4) << s   << std::endl
      << "cv   = " << std::setw(10) << std::setprecision(4) << cv  << std::endl
      << "cp   = " << std::setw(10) << std::setprecision(4) << cp  << std::endl
      << "w    = " << std::setw(10) << std::setprecision(4) << w   << std::endl
      << "hjt  = " << std::setw(10) << std::setprecision(4) << hjt << std::endl;
}

double refproper::tliq(const double P)
{
  double t = 100;
  return t;
}

