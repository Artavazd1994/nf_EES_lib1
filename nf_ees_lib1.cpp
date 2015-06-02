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
  if (!ofs.is_open()) {
    //ofs = new std::ofstream();
    ofs.open("C:/EES32/Userlib/nf_EES_lib1/eessucks.log",
             std::ofstream::out | std::ofstream::app);
    logtimestamp(ofs);
    ofs << "Opening the file ..." << std::endl;
  }
  return ofs;
}

myLib::myLib() { ; }

myLib::~myLib() { ; }

EesDLF &myLib::getNfadd()
{
  return nfadder;
}

EesDLF &myLib::getNftliq()
{
  return nftliquor;
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
  strcpy(Names,"NFADD,NFTLIQ");
}

// List of DLP format procedures
NF_EES_LIB1SHARED_EXPORT void NF_CALLCODE DLPNames(char *Names)
{
  void * pnames = Names;
  myLib::getofs() << "DLPNames with Names = "
       << pnames
       << std::endl;
  strcpy(Names,"");
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

NF_EES_LIB1SHARED_EXPORT double NF_CALLCODE NFTLIQ(char s[256], int &mode,
  struct EesParamRec *input_rec)
{
  return getLib().getNftliq().callDLF(s, mode, input_rec);
}
