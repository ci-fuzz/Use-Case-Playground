#include <stdint.h>
#include <stddef.h>

#include <string.h>
#include <iostream>
#include "crypto_module_1.h"
#include "crypto_module_2.h"
#include "crypto_module_types.h"

#include <fuzzer/FuzzedDataProvider.h>

uint8_t third_party_library_calc_hmac(const uint8_t *const message, size_t len, char *const key, char *const nonce, uint8_t *hmac);

// extern "C" int FUZZ_INIT_WITH_ARGS(int *argc, char ***argv) {
extern "C" int FUZZ_INIT() {

  // Add global setup code here - called once before fuzzing starts

  return 0;
}

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {

  // process fuzzer input (*Data) and setup local objects necessary to call the function under test
  FuzzedDataProvider fuzz_data(Data, Size);

  //Create input parameters with fuzzing data
  std::vector<uint8_t> message = fuzz_data.ConsumeBytes<uint8_t>(fuzz_data.ConsumeIntegral<uint8_t>()); 
  std::vector<char> key = fuzz_data.ConsumeBytes<char>(KEY_LENGTH);
  std::vector<char> nonce = fuzz_data.ConsumeBytes<char>(NONCE_LENGTH);
  //This is only an output parameter
  uint8_t hmac[HMAC_LENGTH] = {0};

  //Execute API function with prepared parameters
  third_party_library_calc_hmac(message.data(), message.size(), key.data(), nonce.data(), hmac);

  // reset state and free all locally allocated resources

  return 0;
}
