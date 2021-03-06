#include <stdint.h>
#include <stddef.h>

#include <fuzzer/FuzzedDataProvider.h>

#define NONCE_LENGTH 64
#define KEY_LENGTH 64
#define HMAC_LENGTH 64

//The software that we want to test is defined in this namespace
namespace target_software {

  //Declarations
  typedef struct nonce {
    uint8_t nonce[NONCE_LENGTH];
    int time_of_creation;
  } nonce;

  typedef struct key {
    uint8_t key[KEY_LENGTH];
  } key;
    
  typedef struct hmac {
    uint8_t hmac[HMAC_LENGTH];
  } hmac;

  enum return_status {
    valid_key_provided,
    invalid_key_provided,
    valid_nonce_provided,
    invalid_nonce_provided,
    wrong_state,
    hmac_successfully_calculated,
    error_during_hmac_calculation,
    invalid_hmac,
    valid_hmac
  };

  enum state{
    uninitialized,
    initialized,
    key_set,
    nonce_set,
    nonce_and_key_set
  };


  //Definition of global variables
  static enum state current_state = uninitialized;
  static key current_key = {0};
  static nonce * current_nonce;

  void init() {
    memset(&current_key, 0 , sizeof(current_key));
    if (current_state == uninitialized) {
      current_nonce = (nonce*)calloc(1, sizeof(nonce));
    }
    else {
      memset(current_nonce, 0 , sizeof(nonce));
    }
    current_state = initialized;
  }

  return_status set_key(key k) {
    if (k.key[0] != 0) {
        current_key = k;
        if (current_state == nonce_set) {
            current_state = nonce_and_key_set;
        }
        else {
            current_state = key_set;
        }
        return valid_key_provided;
    }
    return invalid_key_provided;
  }

  return_status set_nonce(nonce n) {
    if (current_state != uninitialized) {
      if(n.nonce[0] != 0) {
        for (int i = 0; i < NONCE_LENGTH; i++) {
          current_nonce->nonce[i] = n.nonce[i];
        }
        current_nonce->time_of_creation = n.time_of_creation;
        if (current_state == key_set) {
          current_state = nonce_and_key_set;
        }
        else {
          current_state = nonce_set;
        }
        return valid_nonce_provided;
      }
      return invalid_nonce_provided;
    }
    return wrong_state;
  }

  return_status calculate_hmac(const uint8_t * const message, size_t len, hmac * h) {
    if (current_state == nonce_and_key_set) {
      if (len > 6) {
        if (message[0] == 'C') {
          if (message[1] == 'I') {            
            if (message[2] == '-') {            
              if (message[3] == 'F') {        
                if (message[4] == 'U') {        
                  if (message[5] == 'Z') {        
                    if (message[6] == 'Z') {
                      //Delete nonce to make sure it is only used once
                      free(current_nonce);
                      return hmac_successfully_calculated;
                    }
                  }
                }
              }
            }
          }
        }
      }
      current_state = initialized;
      return error_during_hmac_calculation;
    }
    return wrong_state;
  }
}

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {
  //We make use of the FuzzedDataProvider to consume the fuzzing data in different formats
  FuzzedDataProvider fuzz_data(Data, Size);
  
  //Call first function
  target_software::init();

  //Prepare parameter for second function
  target_software::key k;
  fuzz_data.ConsumeData(&k, sizeof(k));
  //Call second function
  target_software::set_key(k);
  
  //Prepare parameter for third function
  target_software::nonce n;
  fuzz_data.ConsumeData(&n, sizeof(n));
  //Call third function
  target_software::set_nonce(n);
  
  //Prepare parameter for fourth function
  //The hmac parameter is only an output parameter so we do not need to fill it with fuzzing data
  target_software::hmac h;
  std::vector<uint8_t> message = fuzz_data.ConsumeBytes<uint8_t>(fuzz_data.ConsumeIntegral<uint8_t>());

  //Execute fourth function with prepared parameters
  target_software::calculate_hmac(message.data(), message.size(), &h);

  return 0;
}
