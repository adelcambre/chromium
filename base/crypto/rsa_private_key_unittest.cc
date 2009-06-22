// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/crypto/rsa_private_key.h"
#include "base/scoped_ptr.h"
#include "testing/gtest/include/gtest/gtest.h"

// Generate random private keys with two different sizes. Reimport, then
// export them again. We should get back the same exact bytes.
TEST(RSAPrivateKeyUnitTest, InitRandomTest) {
  scoped_ptr<base::RSAPrivateKey> keypair1(base::RSAPrivateKey::Create(1024));
  scoped_ptr<base::RSAPrivateKey> keypair2(base::RSAPrivateKey::Create(2048));
  ASSERT_TRUE(keypair1.get());
  ASSERT_TRUE(keypair2.get());

  std::vector<uint8> privkey1;
  std::vector<uint8> privkey2;
  std::vector<uint8> pubkey1;
  std::vector<uint8> pubkey2;

  ASSERT_TRUE(keypair1->ExportPrivateKey(&privkey1));
  ASSERT_TRUE(keypair2->ExportPrivateKey(&privkey2));
  ASSERT_TRUE(keypair1->ExportPublicKey(&pubkey1));
  ASSERT_TRUE(keypair2->ExportPublicKey(&pubkey2));

  scoped_ptr<base::RSAPrivateKey> keypair3(
      base::RSAPrivateKey::CreateFromPrivateKeyInfo(privkey1));
  scoped_ptr<base::RSAPrivateKey> keypair4(
      base::RSAPrivateKey::CreateFromPrivateKeyInfo(privkey2));
  ASSERT_TRUE(keypair3.get());
  ASSERT_TRUE(keypair4.get());

  std::vector<uint8> privkey3;
  std::vector<uint8> privkey4;
  ASSERT_TRUE(keypair3->ExportPrivateKey(&privkey3));
  ASSERT_TRUE(keypair4->ExportPrivateKey(&privkey4));

  ASSERT_EQ(privkey1.size(), privkey3.size());
  ASSERT_EQ(privkey2.size(), privkey4.size());
  ASSERT_TRUE(0 == memcmp(&privkey1.front(), &privkey3.front(),
                          privkey1.size()));
  ASSERT_TRUE(0 == memcmp(&privkey2.front(), &privkey4.front(),
                          privkey2.size()));
}


// Verify that generated public keys look good. This test data was generated
// with the openssl command line tool.
TEST(RSAPrivateKeyUnitTest, PublicKeyTest) {
  const uint8 private_key_info[] = {
    0x30, 0x82, 0x02, 0x78, 0x02, 0x01, 0x00, 0x30, 
    0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 
    0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x04, 0x82, 
    0x02, 0x62, 0x30, 0x82, 0x02, 0x5e, 0x02, 0x01, 
    0x00, 0x02, 0x81, 0x81, 0x00, 0xb8, 0x7f, 0x2b, 
    0x20, 0xdc, 0x7c, 0x9b, 0x0c, 0xdc, 0x51, 0x61, 
    0x99, 0x0d, 0x36, 0x0f, 0xd4, 0x66, 0x88, 0x08, 
    0x55, 0x84, 0xd5, 0x3a, 0xbf, 0x2b, 0xa4, 0x64, 
    0x85, 0x7b, 0x0c, 0x04, 0x13, 0x3f, 0x8d, 0xf4, 
    0xbc, 0x38, 0x0d, 0x49, 0xfe, 0x6b, 0xc4, 0x5a, 
    0xb0, 0x40, 0x53, 0x3a, 0xd7, 0x66, 0x09, 0x0f, 
    0x9e, 0x36, 0x74, 0x30, 0xda, 0x8a, 0x31, 0x4f, 
    0x1f, 0x14, 0x50, 0xd7, 0xc7, 0x20, 0x94, 0x17, 
    0xde, 0x4e, 0xb9, 0x57, 0x5e, 0x7e, 0x0a, 0xe5, 
    0xb2, 0x65, 0x7a, 0x89, 0x4e, 0xb6, 0x47, 0xff, 
    0x1c, 0xbd, 0xb7, 0x38, 0x13, 0xaf, 0x47, 0x85, 
    0x84, 0x32, 0x33, 0xf3, 0x17, 0x49, 0xbf, 0xe9, 
    0x96, 0xd0, 0xd6, 0x14, 0x6f, 0x13, 0x8d, 0xc5, 
    0xfc, 0x2c, 0x72, 0xba, 0xac, 0xea, 0x7e, 0x18, 
    0x53, 0x56, 0xa6, 0x83, 0xa2, 0xce, 0x93, 0x93, 
    0xe7, 0x1f, 0x0f, 0xe6, 0x0f, 0x02, 0x03, 0x01, 
    0x00, 0x01, 0x02, 0x81, 0x80, 0x03, 0x61, 0x89, 
    0x37, 0xcb, 0xf2, 0x98, 0xa0, 0xce, 0xb4, 0xcb, 
    0x16, 0x13, 0xf0, 0xe6, 0xaf, 0x5c, 0xc5, 0xa7, 
    0x69, 0x71, 0xca, 0xba, 0x8d, 0xe0, 0x4d, 0xdd, 
    0xed, 0xb8, 0x48, 0x8b, 0x16, 0x93, 0x36, 0x95, 
    0xc2, 0x91, 0x40, 0x65, 0x17, 0xbd, 0x7f, 0xd6, 
    0xad, 0x9e, 0x30, 0x28, 0x46, 0xe4, 0x3e, 0xcc, 
    0x43, 0x78, 0xf9, 0xfe, 0x1f, 0x33, 0x23, 0x1e, 
    0x31, 0x12, 0x9d, 0x3c, 0xa7, 0x08, 0x82, 0x7b, 
    0x7d, 0x25, 0x4e, 0x5e, 0x19, 0xa8, 0x9b, 0xed, 
    0x86, 0xb2, 0xcb, 0x3c, 0xfe, 0x4e, 0xa1, 0xfa, 
    0x62, 0x87, 0x3a, 0x17, 0xf7, 0x60, 0xec, 0x38, 
    0x29, 0xe8, 0x4f, 0x34, 0x9f, 0x76, 0x9d, 0xee, 
    0xa3, 0xf6, 0x85, 0x6b, 0x84, 0x43, 0xc9, 0x1e, 
    0x01, 0xff, 0xfd, 0xd0, 0x29, 0x4c, 0xfa, 0x8e, 
    0x57, 0x0c, 0xc0, 0x71, 0xa5, 0xbb, 0x88, 0x46, 
    0x29, 0x5c, 0xc0, 0x4f, 0x01, 0x02, 0x41, 0x00, 
    0xf5, 0x83, 0xa4, 0x64, 0x4a, 0xf2, 0xdd, 0x8c, 
    0x2c, 0xed, 0xa8, 0xd5, 0x60, 0x5a, 0xe4, 0xc7, 
    0xcc, 0x61, 0xcd, 0x38, 0x42, 0x20, 0xd3, 0x82, 
    0x18, 0xf2, 0x35, 0x00, 0x72, 0x2d, 0xf7, 0x89, 
    0x80, 0x67, 0xb5, 0x93, 0x05, 0x5f, 0xdd, 0x42, 
    0xba, 0x16, 0x1a, 0xea, 0x15, 0xc6, 0xf0, 0xb8, 
    0x8c, 0xbc, 0xbf, 0x54, 0x9e, 0xf1, 0xc1, 0xb2, 
    0xb3, 0x8b, 0xb6, 0x26, 0x02, 0x30, 0xc4, 0x81, 
    0x02, 0x41, 0x00, 0xc0, 0x60, 0x62, 0x80, 0xe1, 
    0x22, 0x78, 0xf6, 0x9d, 0x83, 0x18, 0xeb, 0x72, 
    0x45, 0xd7, 0xc8, 0x01, 0x7f, 0xa9, 0xca, 0x8f, 
    0x7d, 0xd6, 0xb8, 0x31, 0x2b, 0x84, 0x7f, 0x62, 
    0xd9, 0xa9, 0x22, 0x17, 0x7d, 0x06, 0x35, 0x6c, 
    0xf3, 0xc1, 0x94, 0x17, 0x85, 0x5a, 0xaf, 0x9c, 
    0x5c, 0x09, 0x3c, 0xcf, 0x2f, 0x44, 0x9d, 0xb6, 
    0x52, 0x68, 0x5f, 0xf9, 0x59, 0xc8, 0x84, 0x2b, 
    0x39, 0x22, 0x8f, 0x02, 0x41, 0x00, 0xb2, 0x04, 
    0xe2, 0x0e, 0x56, 0xca, 0x03, 0x1a, 0xc0, 0xf9, 
    0x12, 0x92, 0xa5, 0x6b, 0x42, 0xb8, 0x1c, 0xda, 
    0x4d, 0x93, 0x9d, 0x5f, 0x6f, 0xfd, 0xc5, 0x58, 
    0xda, 0x55, 0x98, 0x74, 0xfc, 0x28, 0x17, 0x93, 
    0x1b, 0x75, 0x9f, 0x50, 0x03, 0x7f, 0x7e, 0xae, 
    0xc8, 0x95, 0x33, 0x75, 0x2c, 0xd6, 0xa4, 0x35, 
    0xb8, 0x06, 0x03, 0xba, 0x08, 0x59, 0x2b, 0x17, 
    0x02, 0xdc, 0x4c, 0x7a, 0x50, 0x01, 0x02, 0x41, 
    0x00, 0x9d, 0xdb, 0x39, 0x59, 0x09, 0xe4, 0x30, 
    0xa0, 0x24, 0xf5, 0xdb, 0x2f, 0xf0, 0x2f, 0xf1, 
    0x75, 0x74, 0x0d, 0x5e, 0xb5, 0x11, 0x73, 0xb0, 
    0x0a, 0xaa, 0x86, 0x4c, 0x0d, 0xff, 0x7e, 0x1d, 
    0xb4, 0x14, 0xd4, 0x09, 0x91, 0x33, 0x5a, 0xfd, 
    0xa0, 0x58, 0x80, 0x9b, 0xbe, 0x78, 0x2e, 0x69, 
    0x82, 0x15, 0x7c, 0x72, 0xf0, 0x7b, 0x18, 0x39, 
    0xff, 0x6e, 0xeb, 0xc6, 0x86, 0xf5, 0xb4, 0xc7, 
    0x6f, 0x02, 0x41, 0x00, 0x8d, 0x1a, 0x37, 0x0f, 
    0x76, 0xc4, 0x82, 0xfa, 0x5c, 0xc3, 0x79, 0x35, 
    0x3e, 0x70, 0x8a, 0xbf, 0x27, 0x49, 0xb0, 0x99, 
    0x63, 0xcb, 0x77, 0x5f, 0xa8, 0x82, 0x65, 0xf6, 
    0x03, 0x52, 0x51, 0xf1, 0xae, 0x2e, 0x05, 0xb3, 
    0xc6, 0xa4, 0x92, 0xd1, 0xce, 0x6c, 0x72, 0xfb, 
    0x21, 0xb3, 0x02, 0x87, 0xe4, 0xfd, 0x61, 0xca, 
    0x00, 0x42, 0x19, 0xf0, 0xda, 0x5a, 0x53, 0xe3, 
    0xb1, 0xc5, 0x15, 0xf3
  };

  const uint8 expected_public_key_info[] = {
    0x30, 0x81, 0x9f, 0x30, 0x0d, 0x06, 0x09, 0x2a, 
    0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 
    0x05, 0x00, 0x03, 0x81, 0x8d, 0x00, 0x30, 0x81, 
    0x89, 0x02, 0x81, 0x81, 0x00, 0xb8, 0x7f, 0x2b, 
    0x20, 0xdc, 0x7c, 0x9b, 0x0c, 0xdc, 0x51, 0x61, 
    0x99, 0x0d, 0x36, 0x0f, 0xd4, 0x66, 0x88, 0x08, 
    0x55, 0x84, 0xd5, 0x3a, 0xbf, 0x2b, 0xa4, 0x64, 
    0x85, 0x7b, 0x0c, 0x04, 0x13, 0x3f, 0x8d, 0xf4, 
    0xbc, 0x38, 0x0d, 0x49, 0xfe, 0x6b, 0xc4, 0x5a, 
    0xb0, 0x40, 0x53, 0x3a, 0xd7, 0x66, 0x09, 0x0f, 
    0x9e, 0x36, 0x74, 0x30, 0xda, 0x8a, 0x31, 0x4f, 
    0x1f, 0x14, 0x50, 0xd7, 0xc7, 0x20, 0x94, 0x17, 
    0xde, 0x4e, 0xb9, 0x57, 0x5e, 0x7e, 0x0a, 0xe5, 
    0xb2, 0x65, 0x7a, 0x89, 0x4e, 0xb6, 0x47, 0xff, 
    0x1c, 0xbd, 0xb7, 0x38, 0x13, 0xaf, 0x47, 0x85, 
    0x84, 0x32, 0x33, 0xf3, 0x17, 0x49, 0xbf, 0xe9, 
    0x96, 0xd0, 0xd6, 0x14, 0x6f, 0x13, 0x8d, 0xc5, 
    0xfc, 0x2c, 0x72, 0xba, 0xac, 0xea, 0x7e, 0x18, 
    0x53, 0x56, 0xa6, 0x83, 0xa2, 0xce, 0x93, 0x93, 
    0xe7, 0x1f, 0x0f, 0xe6, 0x0f, 0x02, 0x03, 0x01, 
    0x00, 0x01
  };

  std::vector<uint8> input;
  input.resize(sizeof(private_key_info));
  memcpy(&input.front(), private_key_info, sizeof(private_key_info));

  scoped_ptr<base::RSAPrivateKey> key(
      base::RSAPrivateKey::CreateFromPrivateKeyInfo(input));
  ASSERT_TRUE(key.get());

  std::vector<uint8> output;
  ASSERT_TRUE(key->ExportPublicKey(&output));

  ASSERT_TRUE(
      memcmp(expected_public_key_info, &output.front(), output.size()) == 0);
}

// These two test keys each contain an integer that has 0x00 for its most
// significant byte. When encoded as ASN.1, this byte is dropped and there are
// two interesting sub-cases. When the sign bit of the integer is set, an extra
// null byte is added back to force the encoded value to be positive. When the
// sign bit is not set, the encoded integer is just left shorter than usual.
// See also: http://code.google.com/p/chromium/issues/detail?id=14877.
//
// Before we were handling this correctly, we would see one of two failures:
// * RSAPrivateKey::CreateFromPrivateKeyInfo would return null because the
//   underlying windows API failed to import the key.
// * The import would succeed, but incorrectly interpret the data. On export,
//   the key would contain different values.
//
// This test case verifies these two failures modes don't occur.
TEST(RSAPrivateKeyUnitTest, ShortIntegers) {
  const uint8 short_integer_with_high_bit[] = {
    0x30, 0x82, 0x02, 0x77, 0x02, 0x01, 0x00, 0x30, 
    0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 
    0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x04, 0x82, 
    0x02, 0x61, 0x30, 0x82, 0x02, 0x5d, 0x02, 0x01, 
    0x00, 0x02, 0x81, 0x81, 0x00, 0x92, 0x59, 0x32, 
    0x7d, 0x8e, 0xaf, 0x2e, 0xd5, 0xb2, 0x5c, 0x67, 
    0xc8, 0x7d, 0x48, 0xb7, 0x84, 0x12, 0xd0, 0x76, 
    0xda, 0xe1, 0xa3, 0x1e, 0x40, 0x01, 0x14, 0x5c, 
    0xef, 0x26, 0x6e, 0x28, 0xa2, 0xf7, 0xa5, 0xb4, 
    0x02, 0x37, 0xd0, 0x53, 0x10, 0xcb, 0x7c, 0x6a, 
    0xf4, 0x53, 0x9f, 0xb8, 0xe0, 0x83, 0x93, 0xd1, 
    0x19, 0xd8, 0x28, 0xd1, 0xd1, 0xd8, 0x87, 0x8f, 
    0x92, 0xfd, 0x73, 0xc0, 0x4d, 0x3e, 0x07, 0x22, 
    0x1f, 0xc1, 0x20, 0xb0, 0x70, 0xb2, 0x3b, 0xea, 
    0xb1, 0xe5, 0x0a, 0xfd, 0x56, 0x49, 0x5e, 0x39, 
    0x90, 0x91, 0xce, 0x04, 0x83, 0x29, 0xaa, 0xfd, 
    0x12, 0xa4, 0x42, 0x26, 0x6c, 0x6e, 0x79, 0x70, 
    0x77, 0x03, 0xb2, 0x07, 0x01, 0x3d, 0x85, 0x81, 
    0x95, 0x9e, 0xda, 0x5a, 0xa3, 0xf4, 0x2d, 0x38, 
    0x04, 0x58, 0xf5, 0x6b, 0xc9, 0xf1, 0xb5, 0x65, 
    0xfe, 0x66, 0x0d, 0xa2, 0xd5, 0x02, 0x03, 0x01, 
    0x00, 0x01, 0x02, 0x81, 0x80, 0x5e, 0x01, 0x5f, 
    0xb6, 0x59, 0x1d, 0xdc, 0x36, 0xb6, 0x60, 0x36, 
    0xe6, 0x08, 0xdb, 0xd9, 0xcd, 0xc3, 0x8c, 0x16, 
    0x9c, 0x98, 0x8d, 0x7f, 0xd3, 0xdb, 0x1d, 0xaa, 
    0x68, 0x8f, 0xc5, 0xf8, 0xe2, 0x5d, 0xb3, 0x19, 
    0xc2, 0xc6, 0xf9, 0x51, 0x32, 0x1b, 0x93, 0x6a, 
    0xdc, 0x50, 0x8e, 0xeb, 0x61, 0x84, 0x03, 0x42, 
    0x30, 0x98, 0xb1, 0xf7, 0xbd, 0x14, 0x9a, 0x57, 
    0x36, 0x33, 0x09, 0xd4, 0x3e, 0x90, 0xda, 0xef, 
    0x09, 0x6e, 0xef, 0x49, 0xb6, 0x60, 0x68, 0x5e, 
    0x54, 0x17, 0x25, 0x5b, 0x37, 0xe3, 0x35, 0x63, 
    0x5b, 0x60, 0x3c, 0xbd, 0x50, 0xdf, 0x46, 0x43, 
    0x08, 0xa4, 0x71, 0x21, 0xf1, 0x30, 0x71, 0xdc, 
    0xda, 0xd7, 0x6f, 0xd2, 0x18, 0xbd, 0x39, 0xf1, 
    0xe1, 0xbe, 0xa8, 0x8d, 0x62, 0xdf, 0xa2, 0x3e, 
    0xb6, 0x15, 0x26, 0xb6, 0x57, 0xbd, 0x63, 0xdb, 
    0xc1, 0x91, 0xec, 0xb8, 0x01, 0x02, 0x41, 0x00, 
    0xc6, 0x1a, 0x06, 0x48, 0xf2, 0x12, 0x1c, 0x9f, 
    0x74, 0x20, 0x5c, 0x85, 0xa2, 0xda, 0xe5, 0x62, 
    0x96, 0x8d, 0x22, 0x7b, 0x78, 0x73, 0xea, 0xbb, 
    0x9f, 0x59, 0x42, 0x13, 0x15, 0xc8, 0x11, 0x50, 
    0x6c, 0x55, 0xf6, 0xdf, 0x8b, 0xfe, 0xc7, 0xdd, 
    0xa8, 0xca, 0x54, 0x41, 0xe8, 0xce, 0xbe, 0x7d, 
    0xbd, 0xe2, 0x13, 0x4b, 0x5b, 0x61, 0xeb, 0x69, 
    0x6c, 0xb1, 0x9b, 0x28, 0x68, 0x5b, 0xd6, 0x01, 
    0x02, 0x41, 0x00, 0xbd, 0x1e, 0xfe, 0x51, 0x99, 
    0xb6, 0xe3, 0x84, 0xfe, 0xf1, 0x9e, 0xfd, 0x9c, 
    0xe7, 0x86, 0x43, 0x68, 0x7f, 0x2f, 0x6a, 0x2a, 
    0x4c, 0xae, 0xa6, 0x41, 0x1c, 0xf0, 0x10, 0x37, 
    0x54, 0x23, 0xba, 0x05, 0x0d, 0x18, 0x27, 0x8d, 
    0xb8, 0xe4, 0x8f, 0xf2, 0x25, 0x73, 0x8a, 0xd7, 
    0x05, 0x98, 0x6b, 0x3d, 0x55, 0xb7, 0x6f, 0x7c, 
    0xec, 0x77, 0x61, 0x54, 0x7b, 0xb6, 0x6b, 0x31, 
    0xec, 0x94, 0xd5, 0x02, 0x41, 0x00, 0x90, 0xa2, 
    0xa5, 0x9e, 0x12, 0xa7, 0x68, 0xa0, 0x7e, 0xdf, 
    0xb5, 0xcd, 0x98, 0x26, 0xab, 0xbd, 0xbc, 0x5f, 
    0xd5, 0x22, 0x42, 0xc2, 0x97, 0x4a, 0x5f, 0x40, 
    0x82, 0xfe, 0x7e, 0x33, 0xb1, 0x78, 0x7f, 0x70, 
    0x90, 0x2b, 0x8d, 0x01, 0xfb, 0x18, 0xfa, 0x48, 
    0xa7, 0x15, 0xec, 0x0d, 0x2e, 0x85, 0x8d, 0xe2, 
    0x86, 0xe5, 0xc9, 0x15, 0x88, 0x14, 0x53, 0xd8, 
    0xa4, 0x88, 0xef, 0x10, 0xc6, 0x01, 0x02, 0x41, 
    0x00, 0xba, 0xe4, 0xaf, 0x14, 0xfa, 0xdf, 0xf6, 
    0xd5, 0xce, 0x8f, 0xfe, 0xbb, 0xc8, 0x5c, 0x30, 
    0x9d, 0xda, 0xdd, 0x9d, 0x80, 0xc0, 0x0e, 0x89, 
    0xa5, 0xb8, 0xc1, 0x1d, 0x28, 0x19, 0x55, 0x67, 
    0xfd, 0x03, 0xd2, 0xdd, 0xe4, 0xf0, 0xb4, 0x20, 
    0x03, 0x74, 0x9b, 0xb8, 0x24, 0x23, 0xbb, 0xde, 
    0xd5, 0x53, 0x86, 0xaa, 0xc1, 0x5d, 0x65, 0xdd, 
    0xcf, 0xec, 0x8a, 0x59, 0x4a, 0x73, 0xca, 0xc5, 
    0x85, 0x02, 0x40, 0x00, 0xc4, 0x5e, 0x8d, 0xa4, 
    0xea, 0xbb, 0x6a, 0x9b, 0xe6, 0x3a, 0x4d, 0xc1, 
    0xdb, 0xe5, 0x52, 0x38, 0xf9, 0x59, 0x91, 0x2d, 
    0x90, 0x82, 0xe3, 0x31, 0x1b, 0x48, 0xb7, 0x42, 
    0xfa, 0x1d, 0x83, 0xd5, 0x3d, 0x02, 0xc2, 0x12, 
    0x71, 0x10, 0x3a, 0xbd, 0x92, 0x8f, 0x9b, 0xa2, 
    0x6b, 0x2d, 0x21, 0xa4, 0x65, 0xe9, 0xfa, 0x8c, 
    0x30, 0x2a, 0x89, 0xce, 0xd0, 0xa7, 0x67, 0xd8, 
    0x45, 0x84, 0xb0
  };

  const uint8 short_integer_without_high_bit[] = {
    0x30, 0x82, 0x02, 0x76, 0x02, 0x01, 0x00, 0x30, 
    0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 
    0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x04, 0x82, 
    0x02, 0x60, 0x30, 0x82, 0x02, 0x5c, 0x02, 0x01, 
    0x00, 0x02, 0x81, 0x81, 0x00, 0xc3, 0x9e, 0x8d, 
    0xc4, 0x6d, 0x38, 0xe8, 0x0e, 0x9f, 0x84, 0x03, 
    0x40, 0x8e, 0x81, 0x2e, 0x56, 0x67, 0x78, 0x11, 
    0x85, 0x27, 0x81, 0x52, 0xf2, 0x1b, 0x3e, 0x5b, 
    0xf8, 0xab, 0xfc, 0xaf, 0xca, 0x5c, 0x26, 0xd5, 
    0xfa, 0xd4, 0x55, 0x50, 0x38, 0xb9, 0x9d, 0x89, 
    0x92, 0x7e, 0x34, 0xcf, 0x37, 0x82, 0x48, 0x2d, 
    0xaa, 0xc4, 0x6a, 0x0e, 0x93, 0xea, 0xad, 0x8a, 
    0x33, 0xf0, 0x42, 0x23, 0xe0, 0x4c, 0x98, 0xbf, 
    0x01, 0x00, 0x1b, 0xfe, 0x06, 0x15, 0xc6, 0xe3, 
    0x80, 0x79, 0x6d, 0xfe, 0x48, 0xcd, 0x40, 0xbb, 
    0xf9, 0x58, 0xe6, 0xbf, 0xd5, 0x4c, 0x29, 0x48, 
    0x53, 0x78, 0x06, 0x03, 0x0d, 0x59, 0xf5, 0x20, 
    0xe0, 0xe6, 0x8c, 0xb2, 0xf5, 0xd8, 0x61, 0x52, 
    0x7e, 0x40, 0x83, 0xd7, 0x69, 0xae, 0xd7, 0x75, 
    0x02, 0x2d, 0x49, 0xd5, 0x15, 0x5b, 0xf1, 0xd9, 
    0x4d, 0x60, 0x7d, 0x62, 0xa5, 0x02, 0x03, 0x01, 
    0x00, 0x01, 0x02, 0x7f, 0x6d, 0x45, 0x23, 0xeb, 
    0x95, 0x17, 0x34, 0x88, 0xf6, 0x91, 0xc7, 0x3f, 
    0x48, 0x5a, 0xe0, 0x87, 0x63, 0x44, 0xae, 0x84, 
    0xb2, 0x8c, 0x8a, 0xc8, 0xb2, 0x6f, 0x22, 0xf0, 
    0xc5, 0x21, 0x61, 0x10, 0xa8, 0x69, 0x09, 0x1e, 
    0x13, 0x7d, 0x94, 0x52, 0x1b, 0x5c, 0xe4, 0x7b, 
    0xf0, 0x03, 0x8f, 0xbc, 0x72, 0x09, 0xdf, 0x78, 
    0x84, 0x3e, 0xb9, 0xe5, 0xe6, 0x31, 0x0a, 0x01, 
    0xf9, 0x32, 0xf8, 0xd6, 0x57, 0xa3, 0x87, 0xe6, 
    0xf5, 0x98, 0xbc, 0x8e, 0x41, 0xb9, 0x50, 0x17, 
    0x7b, 0xd3, 0x97, 0x5a, 0x44, 0x3a, 0xee, 0xff, 
    0x6b, 0xb3, 0x3a, 0x52, 0xe7, 0xa4, 0x96, 0x9a, 
    0xf6, 0x83, 0xc8, 0x97, 0x1c, 0x63, 0xa1, 0xd6, 
    0xb3, 0xa8, 0xb2, 0xc7, 0x73, 0x25, 0x0f, 0x58, 
    0x36, 0xb9, 0x7a, 0x47, 0xa7, 0x4d, 0x30, 0xfe, 
    0x4d, 0x74, 0x56, 0xe8, 0xfb, 0xd6, 0x50, 0xe5, 
    0xe0, 0x28, 0x15, 0x02, 0x41, 0x00, 0xeb, 0x15, 
    0x62, 0xb6, 0x37, 0x41, 0x7c, 0xc5, 0x00, 0x22, 
    0x2c, 0x5a, 0x5e, 0xe4, 0xb2, 0x11, 0x87, 0x89, 
    0xad, 0xf4, 0x57, 0x68, 0x90, 0xb7, 0x9f, 0xe2, 
    0x79, 0x20, 0x6b, 0x98, 0x00, 0x0d, 0x3a, 0x3b, 
    0xc1, 0xcd, 0x36, 0xf9, 0x27, 0xda, 0x40, 0x36, 
    0x1d, 0xb8, 0x5c, 0x96, 0xeb, 0x04, 0x08, 0xe1, 
    0x3f, 0xfa, 0x94, 0x8b, 0x0f, 0xa0, 0xff, 0xc1, 
    0x51, 0xea, 0x90, 0xad, 0x15, 0xc7, 0x02, 0x41, 
    0x00, 0xd5, 0x06, 0x45, 0xd7, 0x55, 0x63, 0x1a, 
    0xf0, 0x89, 0x81, 0xae, 0x87, 0x23, 0xa2, 0x39, 
    0xfe, 0x3d, 0x82, 0xc7, 0xcb, 0x15, 0xb9, 0xe3, 
    0xe2, 0x5b, 0xc6, 0xd2, 0x55, 0xdd, 0xab, 0x55, 
    0x29, 0x7c, 0xda, 0x0e, 0x1c, 0x09, 0xfc, 0x73, 
    0x0d, 0x01, 0xed, 0x6d, 0x2f, 0x05, 0xd0, 0xd5, 
    0x1d, 0xce, 0x18, 0x7f, 0xb0, 0xc8, 0x47, 0x77, 
    0xd2, 0xa9, 0x9e, 0xfc, 0x39, 0x4b, 0x3d, 0x94, 
    0x33, 0x02, 0x41, 0x00, 0x8f, 0x94, 0x09, 0x2d, 
    0x17, 0x44, 0x75, 0x0a, 0xf1, 0x10, 0xee, 0x1b, 
    0xe7, 0xd7, 0x2f, 0xf6, 0xca, 0xdc, 0x49, 0x15, 
    0x72, 0x09, 0x58, 0x51, 0xfe, 0x61, 0xd8, 0xee, 
    0xf7, 0x27, 0xe7, 0xe8, 0x2c, 0x47, 0xf1, 0x0f, 
    0x00, 0x63, 0x5e, 0x76, 0xcb, 0x3f, 0x02, 0x19, 
    0xe6, 0xda, 0xfa, 0x01, 0x05, 0xd7, 0x65, 0x37, 
    0x0b, 0x60, 0x7f, 0x94, 0x2a, 0x80, 0x8d, 0x22, 
    0x81, 0x68, 0x65, 0x63, 0x02, 0x41, 0x00, 0xc2, 
    0xd4, 0x18, 0xde, 0x47, 0x9e, 0xfb, 0x8d, 0x91, 
    0x05, 0xc5, 0x3c, 0x9d, 0xcf, 0x8a, 0x60, 0xc7, 
    0x9b, 0x2b, 0xe5, 0xc6, 0xba, 0x1b, 0xfc, 0xf3, 
    0xd9, 0x54, 0x97, 0xe9, 0xc4, 0x00, 0x80, 0x90, 
    0x4a, 0xd2, 0x6a, 0xbc, 0x8b, 0x62, 0x22, 0x3c, 
    0x68, 0x0c, 0xda, 0xdb, 0xe3, 0xd2, 0x76, 0x8e, 
    0xff, 0x03, 0x12, 0x09, 0x2a, 0xac, 0x21, 0x44, 
    0xb7, 0x3e, 0x91, 0x9c, 0x09, 0xf6, 0xd7, 0x02, 
    0x41, 0x00, 0xc0, 0xa1, 0xbb, 0x70, 0xdc, 0xf8, 
    0xeb, 0x17, 0x61, 0xd4, 0x8c, 0x7c, 0x3b, 0x82, 
    0x91, 0x58, 0xff, 0xf9, 0x19, 0xac, 0x3a, 0x73, 
    0xa7, 0x20, 0xe5, 0x22, 0x02, 0xc4, 0xf6, 0xb9, 
    0xb9, 0x43, 0x53, 0x35, 0x88, 0xe1, 0x05, 0xb6, 
    0x43, 0x9b, 0x39, 0xc8, 0x04, 0x4d, 0x2b, 0x01, 
    0xf7, 0xe6, 0x1b, 0x8d, 0x7e, 0x89, 0xe3, 0x43, 
    0xd4, 0xf3, 0xab, 0x28, 0xd4, 0x5a, 0x1f, 0x20, 
    0xea, 0xbe
  };

  std::vector<uint8> input1;
  std::vector<uint8> input2;

  input1.resize(sizeof(short_integer_with_high_bit));
  input2.resize(sizeof(short_integer_without_high_bit));

  memcpy(&input1.front(), short_integer_with_high_bit,
         sizeof(short_integer_with_high_bit));
  memcpy(&input2.front(), short_integer_without_high_bit,
         sizeof(short_integer_without_high_bit));

  scoped_ptr<base::RSAPrivateKey> keypair1(
      base::RSAPrivateKey::CreateFromPrivateKeyInfo(input1));
  scoped_ptr<base::RSAPrivateKey> keypair2(
      base::RSAPrivateKey::CreateFromPrivateKeyInfo(input2));
  ASSERT_TRUE(keypair1.get());
  ASSERT_TRUE(keypair2.get());

  std::vector<uint8> output1;
  std::vector<uint8> output2;
  ASSERT_TRUE(keypair1->ExportPrivateKey(&output1));
  ASSERT_TRUE(keypair2->ExportPrivateKey(&output2));

  ASSERT_EQ(input1.size(), output1.size());
  ASSERT_EQ(input2.size(), output2.size());
  ASSERT_TRUE(0 == memcmp(&output1.front(), &input1.front(),
                          input1.size()));
  ASSERT_TRUE(0 == memcmp(&output2.front(), &input2.front(),
                          input2.size()));
}
