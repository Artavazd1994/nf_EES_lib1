#ifndef NF_EES_LIB1_H
#define NF_EES_LIB1_H

#include "nf_ees_lib1_global.h"
#include "ees_common.h"
#include <fstream>
#include "c_nfadd.h"
#include "c_nftliq.h"

class myLib {
  C_NFADD nfadder;
  C_nftliq nftliquor;
public:
  static void logtimestamp(std::ofstream &ofs);
  static std::ofstream & getofs();
  myLib();
  ~myLib();
  EesDLF & getNfadd();
  EesDLF & getNftliq();
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
NF_EES_LIB1SHARED_EXPORT double NF_CALLCODE NFTLIQ(char s[256], int &mode,
  struct EesParamRec *input_rec);

#endif // NF_EES_LIB1_H
