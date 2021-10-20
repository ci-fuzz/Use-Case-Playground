#include <stdint.h>
#include <stddef.h>

#define HMAC_LENGTH 64

//The software that we want to test is defined in this namespace
namespace target_software {

  typedef struct hmac {
      uint8_t hmac[HMAC_LENGTH];
  } hmac;

  enum return_status {
      hmac_successfully_calculated,
      error_during_hmac_calculation,
  };

    return_status calculate_hmac(const uint8_t * const message, size_t len, hmac * h) {
        if (len > 4) {
            if (message[1] == 42) {
                return hmac_successfully_calculated; 
            }
            if (message[0] == 1) {
                if (message[1] == 2) {            
                    if (message[2] == 3) {            
                        if (message[3] == 4) {
                            int x[3];
                            int y = 3;
                            h->hmac[0] = x[y];
                        }   
                    }   
                }   
            }
        }
        return error_during_hmac_calculation;
    }
}

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {
  
  target_software::hmac h;

  //Execute API function with prepared parameters
  target_software::calculate_hmac(Data, Size, &h);

  return 0;
}
