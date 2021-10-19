#include <stdint.h>
#include <stddef.h>

#include <fuzzer/FuzzedDataProvider.h>


extern "C" {
    #include "GPS_module_1.h"
    #include "crypto_module_1.h"
    #include "crypto_module_2.h"
    #include "key_management_module_1.h"
}

void mocklib_set_data(void *fuzzed_data_provider);
void ConsumeDataAndFillRestWithZeros(void *destination, size_t num_bytes, FuzzedDataProvider *fuzz_data);

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {
    
    crypto_init();
    
    // Ensure a minimum data length
    if(Size < 100) return 0;

    // Setup FuzzedDataProvider and initialize the mocklib
    FuzzedDataProvider fuzz_data_provider(Data, Size);
    FuzzedDataProvider *fuzz_data = &fuzz_data_provider;
    mocklib_set_data(fuzz_data);

    int number_of_functions = fuzz_data->ConsumeIntegralInRange<int>(1,100);
    for (int i=0; i<number_of_functions; i++) {
      int func_id = fuzz_data->ConsumeIntegralInRange<int>(0, 13);
      switch(func_id) {
         case 0: {
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            crypto_hmac struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            crypto_calculate_hmac(fuzz_data_0.data(), fuzz_size_0, &struct_0);
            break;
          }
         case 1: {
            crypto_get_state();
            break;
          }
         case 2: {
            crypto_init();
            break;
          }
         case 3: {
            crypto_key struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            crypto_set_key(struct_0);
            break;
          }
         case 4: {
            crypto_nonce struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            crypto_set_nonce(struct_0);
            break;
          }
         case 5: {
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            crypto_hmac struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            crypto_verify_hmac(fuzz_data_0.data(), fuzz_size_0, &struct_0);
            break;
          }
         case 6: {
            crypto_key struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            crypto_verify_key(struct_0);
            break;
          }
         case 7: {
            crypto_nonce struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            crypto_verify_nonce(&struct_0);
            break;
          }
         case 8: {
            GPS_position struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            get_current_position(&struct_0);
            break;
          }
         case 9: {
            get_destination_position();
            break;
          }
         case 10: {
            init_crypto_module();
            break;
          }
         case 11: {
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            key_management_create_key(fuzz_data_0.data(), fuzz_size_0);
            break;
          }
         case 12: {
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            key_management_create_nonce(fuzz_data_0.data(), fuzz_size_0);
            break;
          }
         case 13: {
            GPS_position struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            set_destination_postition(struct_0);
            break;
          }
      }
    }

    return 0;
}
