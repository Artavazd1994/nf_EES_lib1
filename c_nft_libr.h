#ifndef C_NFT_LIBR_H
#define C_NFT_LIBR_H

#include "ees_common.h"

class c_nft_libr : public EesDLF
{
public:
  c_nft_libr();
  double funcDLF(std::string &s, std::vector<double> &inputs);
};

#endif // C_NFT_LIBR_H
