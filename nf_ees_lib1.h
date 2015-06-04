#ifndef NF_EES_LIB1_H
#define NF_EES_LIB1_H

#include "nf_ees_lib1_global.h"
#include "ees_common.h"
#include <fstream>
#include "c_nfadd.h"
#include "c_nftliq.h"
#include "c_nfsatmix.h"
#include "c_nfmixtherm.h"

class myLib {
  C_NFADD nfadder;
  C_nftliq nftliquor;
  c_nfsatmix nfsatmix;
  c_nfmixtherm nfmixtherm;
public:
  static void logtimestamp(std::ofstream &ofs);
  static std::ofstream & getofs();
  myLib();
  ~myLib();
  EesDLF & getNfadd();
  EesDLP &getNftliq();
  EesDLP &getNfsatmix();
  EesDLP &getNftherm();
};

myLib & getLib();

// Tell EES which functions and procedures are exported in the library :
// List of DLF format functions.
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE DLFNames(char* Names);
// List of DLP format procedures.
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE DLPNames(char *Names);
// List of FDL format procedures.
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE FDLNames(char* Names);
// A very boring function.
NF_EES_LIB1SHARED_EXPORT double NF_CALLCODE NFADD(char s[256], int &mode,
  struct EesParamRec *input_rec);
// A less boring function.
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE NFTLIQ(char s[256], int &mode,
  struct EesParamRec *input_rec, struct EesParamRec *output_rec);

NF_CLASS_EXPORT void NF_CALLCODE NFSATMIX(char s[256], int &mode,
  struct EesParamRec *input_rec, struct EesParamRec *output_rec);

NF_CLASS_EXPORT void NF_CALLCODE NFMIXTHERM(char s[256], int &mode,
  struct EesParamRec *input_rec, struct EesParamRec *output_rec);

#endif // NF_EES_LIB1_H
