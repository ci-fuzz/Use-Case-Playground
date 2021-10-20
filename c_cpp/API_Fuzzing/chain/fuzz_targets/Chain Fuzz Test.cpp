#include <stdint.h>
#include <stddef.h>

#include <fuzzer/FuzzedDataProvider.h>

#define NONCE_LENGTH 64
#define KEY_LENGTH 64
#define HMAC_LENGTH 64

namespace target_software {

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
      if (len > 0) {
        if (message[1] == 42) {
          //Delete nonce to make sure it is only used once
          free(current_nonce);
          return hmac_successfully_calculated;
        }
      }
      current_state = initialized;
      return error_during_hmac_calculation;
    }
    return wrong_state;
  }
}

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {
  
  FuzzedDataProvider fuzz_data(Data, Size);
  
  target_software::init();

  target_software::key k;
  fuzz_data.ConsumeData(&k, sizeof(k));
  target_software::set_key(k);
  
  target_software::nonce n;
  fuzz_data.ConsumeData(&n, sizeof(n));
  target_software::set_nonce(n);
  
  target_software::hmac h;
  std::vector<uint8_t> message = fuzz_data.ConsumeBytes<uint8_t>(fuzz_data.ConsumeIntegral<uint8_t>());

  //Execute API function with prepared parameters
  target_software::calculate_hmac(message.data(), message.size(), &h);

  return 0;
}
