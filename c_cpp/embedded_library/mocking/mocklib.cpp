#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

#include <fuzzer/FuzzedDataProvider.h>


extern "C" {
    #include "GPS_module_1.h"
    #include "crypto_module_1.h"
    #include "key_management_module_1.h"
    #include "time_module_1.h"
}



static FuzzedDataProvider *fuzz_data;

// Wrapper function for FuzzedDataProvider.h
// Writes |num_bytes| of input data to the given destination pointer. If there
// is not enough data left, writes all remaining bytes and fills the rest with zeros.
// Return value is the number of bytes written.
void ConsumeDataAndFillRestWithZeros(void *destination, size_t num_bytes, FuzzedDataProvider *fuzz_data) {
  if (destination != nullptr) {
    size_t num_bytes_with_fuzz_data = fuzz_data->ConsumeData(destination, num_bytes);
    if (num_bytes > num_bytes_with_fuzz_data) {
      size_t num_bytes_with_zeros = num_bytes - num_bytes_with_fuzz_data;
      std::memset((char*)destination+num_bytes_with_fuzz_data, 0, num_bytes_with_zeros);
    }
  }
}

// This function received the fuzzer generated data from the fuzz target.
// It needs to be called at the beginning of the LLVMFuzzerTestOneInput function.
void mocklib_set_data(void *fuzzed_data_provider) {
    fuzz_data = (FuzzedDataProvider *) fuzzed_data_provider;
}


uint8_t GPS_driver_obtain_current_position(uint8_t * position_as_bytes, uint8_t * hmac_as_bytes) {
    ConsumeDataAndFillRestWithZeros(position_as_bytes, 12, fuzz_data);
    ConsumeDataAndFillRestWithZeros(hmac_as_bytes, 64, fuzz_data);
    return fuzz_data->ConsumeIntegral<uint8_t>();
}

uint8_t HSM_get_random_byte() {
    return fuzz_data->ConsumeIntegral<uint8_t>();
}

int driver_get_current_time() {
    return fuzz_data->ConsumeIntegral<int>();
}

uint8_t third_party_library_calc_hmac(uint8_t * const message, int len, char * const key, char * const nonce, uint8_t * hmac) {
    ConsumeDataAndFillRestWithZeros(message, len, fuzz_data);
    ConsumeDataAndFillRestWithZeros(key, 64, fuzz_data);
    ConsumeDataAndFillRestWithZeros(nonce, 64, fuzz_data);
    ConsumeDataAndFillRestWithZeros(hmac, 64, fuzz_data);
    return fuzz_data->ConsumeIntegral<uint8_t>();
}
