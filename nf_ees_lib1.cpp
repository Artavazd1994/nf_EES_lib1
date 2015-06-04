#include "nf_ees_lib1.h"

#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <exception>

#define UNICODE

myLib &getLib()
{
  static myLib lib;
  return lib;
}

void myLib::logtimestamp(std::ofstream &ofs)
{
  time_t rawtime;
  struct tm * timeinfo;
  std::time (&rawtime);
  timeinfo = std::localtime (&rawtime);
  ofs << "At " << std::asctime(timeinfo);
}

std::ofstream & myLib::getofs()
{
  static std::ofstream ofs;
  // Do you want to make noise, or not?
  // TODO: debug level instead of boolean.
  bool quiet = true;
  if (quiet) {
    ofs.close();
  } else {
    if (!ofs.is_open()) {
      //ofs = new std::ofstream();
      ofs.open("C:/EES32/Userlib/nf_EES_lib1/eessucks.log",
               std::ofstream::out | std::ofstream::app);
      logtimestamp(ofs);
      ofs << "Opening the file ..." << std::endl;
    }
  }
  return ofs;
}

myLib::myLib() { ; }

myLib::~myLib() { ; }

EesDLF &myLib::getNfadd()
{
  return nfadder;
}

EesDLP &myLib::getNftliq()
{
  return nftliquor;
}

EesDLP &myLib::getNfsatmix()
{
  return nfsatmix;
}

EesDLP &myLib::getNftherm()
{
  return nfmixtherm;
}

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                       )
{
  myLib::getofs() << "In DllMain() ... ";
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    myLib::getofs() << "attaching" << std::endl;
    return TRUE;
  } else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
    myLib::getofs() << "detaching" << std::endl;
    return TRUE;
  } else if (ul_reason_for_call == DLL_THREAD_ATTACH) {
    myLib::getofs() << "thread attaching" << std::endl;
    return TRUE;
  } else if (ul_reason_for_call == DLL_THREAD_DETACH) {
    myLib::getofs() << "thread detaching" << std::endl;
    return TRUE;
  } else {
    myLib::getofs() << "unrecognized bologna" << std::endl;
    return TRUE;
  }
}

// Tell EES which functions and procedures are exported in the library :
// List of DLF format functions
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE DLFNames(char* Names)
{
  void * pnames = Names;
  myLib::getofs() << "DLFNames with Names = "
       << pnames
       << std::endl;
  strcpy(Names,"NFADD");
}

// List of DLP format procedures
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE DLPNames(char *Names)
{
  void * pnames = Names;
  myLib::getofs() << "DLPNames with Names = "
       << pnames
       << std::endl;
  strcpy(Names,"NFTLIQ,NFSATMIX,NFMIXTHERM");
}

// List of FDL format procedures
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE FDLNames(char* Names)
{
  void * pnames = Names;
  myLib::getofs() << "FDLNames with Names = "
       << pnames
       << std::endl;
  strcpy(Names,"");
}

NF_EES_LIB1SHARED_EXPORT double NF_CALLCODE NFADD(char s[256], int &mode,
  struct EesParamRec *input_rec)
{
  return getLib().getNfadd().callDLF(s, mode, input_rec);
}

NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE NFTLIQ(char s[256], int &mode,
  struct EesParamRec *input_rec, struct EesParamRec *output_rec)
{
  getLib().getNftliq().callDLP(s, mode, input_rec, output_rec);
  return;
}
#pragma comment(linker, "/EXPORT:NFTLIQ=?NFTLIQ@@YGXQADAAHPAUEesParamRec@@2@Z")

NF_CLASS_EXPORT void NF_CALLCODE NFSATMIX(char s[256], int &mode,
  struct EesParamRec *input_rec, struct EesParamRec *output_rec)
{
  getLib().getNfsatmix().callDLP(s, mode, input_rec, output_rec);
  return;
}
#pragma comment(linker, "/EXPORT:NFSATMIX=?NFSATMIX@@YGXQADAAHPAUEesParamRec@@2@Z")

NF_CLASS_EXPORT void NF_CALLCODE NFMIXTHERM(char s[256], int &mode,
  struct EesParamRec *input_rec, struct EesParamRec *output_rec)
{
  getLib().getNftherm().callDLP(s, mode, input_rec, output_rec);
  return;
}
#pragma comment(linker, "/EXPORT:NFMIXTHERM=?NFMIXTHERM@@YGXQADAAHPAUEesParamRec@@2@Z")
