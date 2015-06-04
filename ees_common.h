#ifndef EES_COMMON_H
#define EES_COMMON_H

#include "nf_ees_lib1_global.h"
#include <string>
#include <vector>

// Structure for handling ees calling syntax
struct EesParamRec {
  double value;
  struct EesParamRec *next;
};

typedef double (__stdcall *fp_ees_dlf) (char s[256], int &mode, EesParamRec *input_rec);
typedef void (__stdcall *fp_ees_dlp) (char s[256], int &mode, EesParamRec *input_rec, EesParamRec *output_rec);
typedef void (__stdcall *fp_ees_fdl) (char s[256], int& clen, int& mode, int& NInputs, double inputs[], int& NOutputs, double outputs[]);

class EesCommonFunction {
protected:
  std::string name;
  std::string sCallSignature;
  std::string sInputUnits;
  std::string sOutputUnits;
public:
  static std::vector<double> ParamRec2Vector(EesParamRec const * const input_rec);
  static void Vector2ParamRec(std::vector<double> const & output_vec, EesParamRec * const output_rec);
public:
  EesCommonFunction(std::string Name, std::string CallSignature, std::string InputUnits, std::string OutputUnits);
  enum CALL_CODE {CODE_CALL_SIG = -1, CODE_INPUT_UNITS = -2, CODE_OUTPUT_UNITS = -3};
  std::string getCallSignature() const;
  std::string getInputUnits() const;
  std::string getOutputUnits() const;
};

class EesDLF: public EesCommonFunction {
public:
  EesDLF(std::string Name, std::string CallSignature, std::string InputUnits, std::string OutputUnits);
  virtual double funcDLF(std::string &s, std::vector<double> &inputs) = 0;
  double callDLF(char s[256], int &mode, struct EesParamRec *input_rec);
};

class EesDLP: public EesCommonFunction {
public:
  EesDLP(std::string Name, std::string CallSignature, std::string InputUnits, std::string OutputUnits);
  virtual void funcDLP(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs) = 0;
  void callDLP(char s[256], int &mode, EesParamRec *input_rec, EesParamRec *output_rec);
};

class EesFDL: public EesCommonFunction {
public:
  virtual void funcFDL(std::string &s, std::vector<double> &inputs, std::vector<double> &outputs) = 0;
  void callFDL(char s[256], int& clen, int& mode, int& NInputs, double inputs[], int& NOutputs, double outputs[]);
};

class EesDLL {
  // List of DLF format functions
  virtual void DLFNames(char* Names);
  // List of DLP format procedures
  virtual void DLPNames(char *Names);
  // List of FDL format procedures
  virtual void FDLNames(char* Names);
};

#endif // EES_COMMON_H
