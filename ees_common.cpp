#include "ees_common.h"
#include <stdexcept>
#include "nf_ees_lib1.h"

// This is guaranteed not to fail.
std::vector<double> EesCommonFunction::ParamRec2Vector(EesParamRec const * const input_rec)
{
  std::vector<double> result;
  EesParamRec const *input = input_rec;
  while (input != NULL) {
    result.push_back(input->value);
    input = input->next;
  }
  return result;
}

// Inputs: output record should have already been allocated.
// If it does not match the length of the vector, an exception should be raised.
void EesCommonFunction::Vector2ParamRec(std::vector<double> const & output_vec, EesParamRec * const output_rec)
{
  EesParamRec * output = output_rec;
  int givenLength = 0;
  while (output != NULL) {
    output = output->next;
    givenLength++;
  }
  if (givenLength < output_vec.size()) {
    throw std::runtime_error("Output record too short. Good luck!");
  }
  output = output_rec;
  for (std::vector<double>::const_iterator it = output_vec.begin(); it != output_vec.end(); ++it)
  {
    output->value = *it;
    output = output->next;
  }
  /*
  if (output != NULL) {
    throw std::runtime_error("Output record too long. Good luck!");
  }
  */
}

EesCommonFunction::EesCommonFunction(std::string Name, std::string CallSignature, std::string InputUnits, std::string OutputUnits) :
  name(Name),
  sCallSignature(CallSignature),
  sInputUnits(InputUnits),
  sOutputUnits(OutputUnits)
{
  // nothing to do here.
}

std::string EesCommonFunction::getCallSignature() const
{
  return sCallSignature;
}

std::string EesCommonFunction::getInputUnits() const
{
  return sInputUnits;
}

std::string EesCommonFunction::getOutputUnits() const
{
  return sOutputUnits;
}

EesDLF::EesDLF(std::string Name, std::string CallSignature, std::string InputUnits, std::string OutputUnits) :
 ::EesCommonFunction(Name, CallSignature, InputUnits, OutputUnits)
{

}

double EesDLF::callDLF(char s[256], int &mode, struct EesParamRec *input_rec)
{
  switch (mode)
  {
  case CODE_CALL_SIG:
    strcpy(s, getCallSignature().c_str());
    return 0;
  case CODE_INPUT_UNITS:
    strcpy(s, getInputUnits().c_str());
    return 0;
  case CODE_OUTPUT_UNITS:
    strcpy(s, getOutputUnits().c_str());
    return 0;
  default:
    try {
      myLib::logtimestamp(myLib::getofs());
      //myLib::getofs() << "calldlf: converting string input ..." << std::endl;
      std::string str(s);
      //myLib::getofs() << "calldlf: converting input records ..." << std::endl;
      std::vector<double> input_vec = ParamRec2Vector(input_rec);
      //myLib::getofs() << "calldlf: str = \"" << str.substr(0,10) << "\" ... " << std::endl;
      myLib::getofs() << "calldlf: " << name << "(";
      for (std::vector<double>::const_iterator it = input_vec.begin(); it != input_vec.end(); ++it)
      {
        myLib::getofs() << *it << ",";
      }
      myLib::getofs() << ")" << std::endl;
      //myLib::getofs() << "calldlf: calling funcDLF ..." << std::endl;
      double res = funcDLF(str, input_vec);
      myLib::getofs() << "calldlf: returning " << res << std::endl;
      //myLib::getofs() << "calldlf: \"" << str << "\"" << std::endl;
      //myLib::getofs() << "calldlf: " << res << std::endl;
      strcpy(s,str.c_str());
      return res;
    } catch (std::exception &e) {
      mode = 10;
      std::string ss = name + ": " + e.what();
      strcpy(s,ss.c_str());
      return 0;
    }
  }
}

EesDLP::EesDLP(std::string Name, std::string CallSignature, std::string InputUnits, std::string OutputUnits) :
  ::EesCommonFunction(Name, CallSignature, InputUnits, OutputUnits)
{
  // nothing to do here.
}

void EesDLP::callDLP(char s[256], int &mode, EesParamRec *input_rec, EesParamRec *output_rec)
{
  switch (mode)
  {
  case CODE_CALL_SIG:
    strcpy(s, getCallSignature().c_str());
    return;
  case CODE_INPUT_UNITS:
    strcpy(s, getInputUnits().c_str());
    return;
  case CODE_OUTPUT_UNITS:
    strcpy(s, getOutputUnits().c_str());
    return;
  default:
    try {
      //myLib::logtimestamp(myLib::getofs());
      //myLib::getofs() << "calldlp: converting string input ..." << std::endl;
      std::string str(s);
      //myLib::getofs() << "calldlp: converting input records ..." << std::endl;
      std::vector<double> input_vec = ParamRec2Vector(input_rec);
      // myLib::getofs() << "calldlp: str = \"" << str.substr(0,10) << "\" ... " << std::endl;
      myLib::getofs() << "call " << name << "(";
      for (std::vector<double>::const_iterator it = input_vec.begin(); it != input_vec.end(); ++it)
      {
        myLib::getofs() << *it << ",";
      }
      myLib::getofs() << ")" << std::endl;
      //myLib::getofs() << "calldlp: calling funcDLP ..." << std::endl;
      std::vector<double> output_vec;
      funcDLP(str, input_vec, output_vec);

      myLib::getofs() << "calldlp: outputs were:" << std::endl;
      for (std::vector<double>::const_iterator it = output_vec.begin(); it != output_vec.end(); ++it)
      {
        myLib::getofs() << *it << ",";
      }
      myLib::getofs() << std::endl;

      strcpy(s,str.c_str());
      Vector2ParamRec(output_vec, output_rec);
      return;
    } catch (std::exception &e) {
      mode = 10;
      myLib::getofs() << name << ": " << e.what() << std::endl;
      std::string ss = name + ": " + e.what();
      strcpy(s,ss.c_str());
      return;
    }
  }
}
