# Go API Fuzzing

* In fuzzStringCompare.go, the panic can only be triggered if the fuzzer generates the string “Awesome Fuzzing!”
* In fuzzXorEncrypt.go, the encrypt function is used to transform the input and then compares the results with two constants. The panic can only be triggered when both checks are fulfilled.