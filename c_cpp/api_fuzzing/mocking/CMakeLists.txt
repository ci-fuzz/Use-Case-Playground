cmake_minimum_required(VERSION 3.10)

add_library(example-embedded-library
    modules/crypto_module/src/crypto_module_1.c
    modules/crypto_module/src/crypto_module_2.c
    modules/time_module/src/time_module_1.c
    modules/GPS_module/src/GPS_module_1.c
    modules/key_management_module/src/key_management_module_1.c
)

target_include_directories(example-embedded-library PRIVATE
    modules/crypto_module/src
    modules/time_module/src
    modules/key_management_module/src
    modules/GPS_module/src
)