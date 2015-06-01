#include "ees_common.h"
#include <exception>
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
  EesParamRec *output = output_rec;
  for (std::vector<double>::const_iterator it = output_vec.begin(); it != output_vec.end(); ++it)
  {
    if (output == NULL) {
      throw std::exception("Output record too short. Good luck!");
    }
    output->value = *it;
    output = output->next;
  }
  if (output != NULL) {
    throw std::exception("Output record too long. Good luck!");
  }
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
      myLib::getofs() << "calldlf: converting string input ..." << std::endl;
      std::string str(s);
      myLib::getofs() << "calldlf: converting input records ..." << std::endl;
      std::vector<double> input_vec = ParamRec2Vector(input_rec);
      myLib::getofs() << "calldlf: str = \"" << str.substr(0,10) << "\" ... " << std::endl;
      myLib::getofs() << "calldlf: input_vec = ";
      for (std::vector<double>::const_iterator it = input_vec.begin(); it != input_vec.end(); ++it)
      {
        myLib::getofs() << *it << ",";
      }
      myLib::getofs() << std::endl;
      myLib::getofs() << "calldlf: calling funcDLF ..." << std::endl;
      double res = funcDLF(str, input_vec);
      strcpy(s,str.c_str());
      return res;
    } catch (std::exception &e) {
      mode = -10;
      std::string ss = name + ": " + e.what();
      strcpy(s,ss.c_str());
      return 0;
    }
  }
}
