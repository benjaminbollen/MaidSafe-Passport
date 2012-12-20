/***************************************************************************************************
 *  Copyright 2012 maidsafe.net limited                                                            *
 *                                                                                                 *
 *  The following source code is property of MaidSafe.net limited and is not meant for external    *
 *  use. The use of this code is governed by the licence file licence.txt found in the root of     *
 *  this directory and also on www.maidsafe.net.                                                   *
 *                                                                                                 *
 *  You are not free to copy, amend or otherwise use this source code without the explicit written *
 *  permission of the board of directors of MaidSafe.net.                                          *
 **************************************************************************************************/


#include <string>

#include "maidsafe/common/log.h"
#include "maidsafe/common/rsa.h"
#include "maidsafe/common/test.h"

#include "maidsafe/passport/detail/fob.h"
#include "maidsafe/passport/detail/passport_pb.h"
#include "maidsafe/passport/types.h"


namespace maidsafe {

namespace passport {

namespace test {

TEST(FobTest, BEH_FobGenerationAndValidation) {
  Anmid anmid;
  Ansmid ansmid;
  Antmid antmid;
  Anmaid anmaid;
  Maid maid(anmaid);
  Pmid pmid(maid);
  Anmpid anmpid;
  Mpid mpid(anmpid);

  Anmid anmid1(anmid);
  Ansmid ansmid1(ansmid);
  Antmid antmid1(antmid);
  Anmaid anmaid1(anmaid);
  Maid maid1(maid);
  Pmid pmid1(pmid);
  Anmpid anmpid1(anmpid);
  Mpid mpid1(mpid);

  Anmid anmid2(std::move(anmid1));
  Ansmid ansmid2(std::move(ansmid1));
  Antmid antmid2(std::move(antmid1));
  Anmaid anmaid2(std::move(anmaid1));
  Maid maid2(std::move(maid1));
  Pmid pmid2(std::move(pmid1));
  Anmpid anmpid2(std::move(anmpid1));
  Mpid mpid2(std::move(mpid1));

  anmid1 = anmid;
  ansmid1 = ansmid;
  antmid1 = antmid;
  anmaid1 = anmaid;
  maid1 = maid;
  pmid1 = pmid;
  anmpid1 = anmpid;
  mpid1 = mpid;

  anmid2 = std::move(anmid1);
  ansmid2 = std::move(ansmid1);
  antmid2 = std::move(antmid1);
  anmaid2 = std::move(anmaid1);
  maid2 = std::move(maid1);
  pmid2 = std::move(pmid1);
  anmpid2 = std::move(anmpid1);
  mpid2 = std::move(mpid1);

  static_assert(is_short_term_cacheable<Anmid::name_type>::value, "");
  static_assert(is_short_term_cacheable<Ansmid::name_type>::value, "");
  static_assert(is_short_term_cacheable<Antmid::name_type>::value, "");
  static_assert(is_short_term_cacheable<Anmaid::name_type>::value, "");
  static_assert(is_short_term_cacheable<Maid::name_type>::value, "");
  static_assert(is_short_term_cacheable<Pmid::name_type>::value, "");
  static_assert(is_short_term_cacheable<Anmpid::name_type>::value, "");
  static_assert(is_short_term_cacheable<Mpid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Anmid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Ansmid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Antmid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Anmaid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Maid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Pmid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Anmpid::name_type>::value, "");
  static_assert(!is_long_term_cacheable<Mpid::name_type>::value, "");
}

template<typename Fobtype>
bool CheckSerialisationAndParsing(Fobtype fob) {
  maidsafe::passport::detail::protobuf::Fob proto_fob;
  fob.ToProtobuf(&proto_fob);
  Fobtype fob2(proto_fob);
  if (fob.validation_token() != fob2.validation_token()) {
    LOG(kError) << "Validation tokens don't match.";
    return false;
  }
  if (!rsa::MatchingKeys(fob.private_key(), fob2.private_key())) {
    LOG(kError) << "Private keys don't match.";
    return false;
  }
  if (!rsa::MatchingKeys(fob.public_key(), fob2.public_key())) {
    LOG(kError) << "Public keys don't match.";
    return false;
  }
  return true;
}

TEST(FobTest, BEH_FobSerialisationAndParsing) {
  Anmid anmid;
  Ansmid ansmid;
  Antmid antmid;
  Anmaid anmaid;
  Maid maid(anmaid);
  Pmid pmid(maid);
  Anmpid anmpid;
  Mpid mpid(anmpid);

  CheckSerialisationAndParsing(anmid);
  CheckSerialisationAndParsing(ansmid);
  CheckSerialisationAndParsing(antmid);
  CheckSerialisationAndParsing(anmaid);
  CheckSerialisationAndParsing(maid);
  CheckSerialisationAndParsing(pmid);
  CheckSerialisationAndParsing(anmpid);
  CheckSerialisationAndParsing(mpid);
}

}  // namespace test

}  // namespace passport

}  // namespace maidsafe