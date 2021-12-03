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
        if (len > 6) {
            if (message[0] == 'C') {
                if (message[1] == 'I') {            
                    if (message[2] == '-') {            
                        if (message[3] == 'F') {        
                            if (message[4] == 'U') {        
                                if (message[5] == 'Z') {        
                                    if (message[6] == 'Z') {
                                        int x[3];
                                        h->hmac[0] = x[3];
                                        return error_during_hmac_calculation;
                                    }
                                }
                            }
                        }   
                    }   
                }   
            }
        }
        return hmac_successfully_calculated; 
    }
}

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {
  
  target_software::hmac h;

  //Execute API function with prepared parameters
  target_software::calculate_hmac(Data, Size, &h);

  return 0;
}
