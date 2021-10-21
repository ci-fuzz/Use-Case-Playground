#include <stdint.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
    #include "GPS_module_1.h"
    #include "crypto_module_1.h"
    #include "crypto_module_2.h"
    #include "key_management_module_1.h"
}

//Helper functions
void mocklib_set_data(void *fuzzed_data_provider);
void ConsumeDataAndFillRestWithZeros(void *destination, size_t num_bytes, FuzzedDataProvider *fuzz_data);

//This fuzz test tests all defined functions in a "random" order with "random" inputs
extern "C" int FUZZ(const uint8_t *Data, size_t Size) {
    
    //Make sure that the target software is always reset into the same state with every new input that is tested
    crypto_init();
    
    // Ensure a minimum data length
    if(Size < 100) return 0;

    // Setup FuzzedDataProvider and initialize the mocklib
    FuzzedDataProvider fuzz_data_provider(Data, Size);
    FuzzedDataProvider *fuzz_data = &fuzz_data_provider;
    mocklib_set_data(fuzz_data);

    //With every input tested we will execute 1-100 functions. The fuzzing input determines how many functions and which functions are called with which parameters. 
    int number_of_functions = fuzz_data->ConsumeIntegralInRange<int>(1,100);
    for (int i=0; i<number_of_functions; i++) {
      int func_id = fuzz_data->ConsumeIntegralInRange<int>(0, 13);
      switch(func_id) {
         case 0: {
            //Prepare parameters
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            crypto_hmac struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);

            //Call function with prepared parameters
            crypto_calculate_hmac(fuzz_data_0.data(), fuzz_size_0, &struct_0);
            break;
          }
         case 1: {
            //Call function
            crypto_get_state();
            break;
          }
         case 2: {
            //Call function
            crypto_init();
            break;
          }
         case 3: {
            //Prepare parameters
            crypto_key struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            
            //Call function with prepared parameters
            crypto_set_key(struct_0);
            break;
          }
         case 4: {
            //Prepare parameters
            crypto_nonce struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            
            //Call function with prepared parameters
            crypto_set_nonce(struct_0);
            break;
          }
         case 5: {
            //Prepare parameters
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            crypto_hmac struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            
            //Call function with prepared parameters
            crypto_verify_hmac(fuzz_data_0.data(), fuzz_size_0, &struct_0);
            break;
          }
         case 6: {
            //Prepare parameters
            crypto_key struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            
            //Call function with prepared parameters
            crypto_verify_key(struct_0);
            break;
          }
         case 7: {
            //Prepare parameters
            crypto_nonce struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            
            //Call function with prepared parameters
            crypto_verify_nonce(&struct_0);
            break;
          }
         case 8: {
            //Prepare parameters
            GPS_position struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            
            //Call function with prepared parameters
            get_current_position(&struct_0);
            break;
          }
         case 9: {
            //Call function
            get_destination_position();
            break;
          }
         case 10: {
            //Call function
            init_crypto_module();
            break;
          }
         case 11: {
            //Prepare parameters
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            
            //Call function with prepared parameters
            key_management_create_key(fuzz_data_0.data(), fuzz_size_0);
            break;
          }
         case 12: {
            //Prepare parameters
            std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
            size_t fuzz_size_0 = fuzz_data_0.size();
            
            //Call function with prepared parameters
            key_management_create_nonce(fuzz_data_0.data(), fuzz_size_0);
            break;
          }
         case 13: {
            //Prepare parameters
            GPS_position struct_0 = {0};
            ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
            
            //Call function with prepared parameters
            set_destination_postition(struct_0);
            break;
          }
      }
    }

    return 0;
}
