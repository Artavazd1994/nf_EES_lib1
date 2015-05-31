#include "nf_ees_lib1.h"

#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <exception>

#define UNICODE

std::ofstream *ofs;

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                       )
{
  if (ofs == NULL) {
    ofs = new std::ofstream();
    ofs->open("C:/EES32/Userlib/nf_EES_lib1/eessucks.log",
             std::ofstream::out | std::ofstream::app);
    *ofs << "Opening the file ..." << std::endl;
  }
  *ofs << "In DllMain() ... " << std::endl;
  return TRUE;
}

// Tell EES which functions and procedures are exported in the library :
// List of DLF format functions
void NF_CALLCODE DLFNames(char* Names)
{
  void * pnames = Names;
  *ofs << "DLFNames with Names = "
       << pnames
       << " \""
       << Names
       << "\""
       << std::endl;
strcpy(Names,"NFTLIQ");
}

// List of DLP format procedures
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE DLPNames(char *Names)
{
  void * pnames = Names;
  *ofs << "DLPNames with Names = "
       << pnames
       << "\""
       << Names
       << "\""
       << std::endl;
  strcpy(Names,"MYDLP");
}

// List of FDL format procedures
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE FDLNames(char* Names)
{
strcpy(Names,"");
}

NF_EES_LIB1SHARED_EXPORT double NF_CALLCODE MYDLF(char s[256], int &mode,
  struct EesParamRec *input_rec)
{
  static int counter = 0;
  if (counter < 10)
    counter++;
  return double(counter);
}

NF_EES_LIB1SHARED_EXPORT double NF_CALLCODE NFTLIQ(char s[256], int &mode,
  struct EesParamRec *input_rec)
{
  int slen;

  if (ofs == NULL) {
    ofs = new std::ofstream();
    ofs->open("C:/EES32/Userlib/nf_EES_lib1/eessucks.log",
             std::ofstream::out | std::ofstream::app);
    *ofs << "Opening the file ..." << std::endl;
  }
  try {
  time_t rawtime;
  struct tm * timeinfo;
  std::time (&rawtime);
  timeinfo = std::localtime (&rawtime);
  *ofs << "At " << std::asctime(timeinfo)
      << "I have been called with s = \"";
  if (s == NULL) {
    *ofs << "NULL";
  } else {
    slen = std::strlen(s);
    ofs->write(s,slen);
  }
  *ofs << "\", &mode = " << &mode
      << ", mode = ";
#if 0
  if (mode == NULL) {
    *ofs << "NULL";
  } else {
    *ofs << *mode;
  }
#else
  *ofs << mode;
#endif
  EesParamRec *inputs = input_rec;
  int NInputs = 0;
  while (inputs!=NULL) {
    NInputs++;
   inputs = inputs->next;
  }
  *ofs << ", and input records = " << input_rec
       << " of length " << NInputs
      << std::endl;
  ofs->flush();

  double T = 0;
  switch (mode) {
  case -1:
    strcpy(s,"P = NFTLIQ(P,x)");
    slen = std::strlen(s);
    *ofs << "I set s = \"";
    ofs->write(s,slen);
    *ofs << "\"" << std::endl;
    return 0;
  case -2:
    strcpy(s,"kPa,m");
    slen = std::strlen(s);
    *ofs << "I set s = \"";
    ofs->write(s,slen);
    *ofs << "\"" << std::endl;
    return 0;
  case -3:
    strcpy(s,"K");
    slen = std::strlen(s);
    *ofs << "I set s = \"";
    ofs->write(s,slen);
    *ofs << "\"" << std::endl;
    return 0;
  default:

    if (NInputs != 2) {
      strcpy(s,"NFTLIQ expects one (1) input, P");
      return 0;
    }
    double P = input_rec->value;
    input_rec = input_rec->next;
    double x = input_rec->value;
    T = P + x;
    return T;
  }
  } catch (...) {
    *ofs << "I have encountered a grue." << std::endl;
    return 0;
  }
}

NF_EES_LIB1SHARED_EXPORT double NF_CALLCODE NFTVAP(char s[256], int mode,
  struct EesParamRec *input_rec)
{
  double P = 0;
  switch (mode) {
  case -1:
    strcpy(s,"P = NFTVAP(P)");
    break;
  case -2:
    strcpy(s,"MPa");
    break;
  case -3:
    strcpy(s,"K");
    break;
  default:
    EesParamRec *inputs = input_rec;
    int NInputs = 0;
    while (inputs!=NULL) {
      NInputs++;
     inputs = inputs->next;
    }
    if (NInputs != 1) {
      strcpy(s,"NFTVAP expects one (1) input, P");
      mode = 1;
      return P;
    }
    P = 1;
    break;
  }
  return P;
}
#pragma comment(linker, "/export:NFTVAP")

// The procedure name must be in all capital letters.
//__declspec (dllexport) void NF_EES_LIB1(char s[256], int &mode,
//  struct EesParamRec *input_rec, struct EesParamRec *output_rec)
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE MYDLP(char s[256], int &mode,
  struct EesParamRec *input_rec, struct EesParamRec *output_rec)
{
  double v, v1, v2;
  int NInputs, NOutputs;
  EesParamRec *outputs, *inputs;

  if (mode==-1) {
    strcpy(s,"CALL myDLP(X,Y : M, D, A, S, P)");
    return;
  }
  if (mode==-2) {
    strcpy(s,"m,m");
    return;
  }
  if (mode==-3) {
    strcpy(s,"m^2, ,m,m,m");
    return;
  }
  inputs = input_rec;
  NInputs = 0;
  while (inputs!=NULL) {
    NInputs++;
   inputs = inputs->next;
  }
  if (NInputs != 2) {
    strcpy(s,"myDLP expects two inputs");
    mode = 1;
    return;
  };
  outputs=output_rec;
  NOutputs=0;
  while (outputs!=NULL) {
    NOutputs++;
    outputs=outputs->next;
  }
  if (NOutputs!=5) {
    strcpy(s,"myDLP requires 5 outputs which are the product, difference, sum, difference, and power of the two inputs.");
    mode=2;
    return ;
  }
  strcpy(s,"");
  inputs = input_rec;
  v1=inputs->value;
  inputs=inputs->next;
  v2=inputs->value;

  v=v1*v2;
  outputs=output_rec;
  outputs->value=v;
  outputs=outputs->next;
  if (v2==0) {
    strcpy(s,"attempt to divide by zero in myDLP");
    mode=3;
    return;
  }
  v=v1/v2;
  outputs->value=v;
  outputs=outputs->next;
  outputs->value=v1+v2;
  outputs=outputs->next;
  outputs->value=v1-v2;

  outputs=outputs->next;
  outputs->value = pow(v1, v2);

  mode=0;
}
