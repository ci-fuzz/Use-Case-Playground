#include <gtest/gtest.h>
#include <string.h>
#include "../src/explore_me.h"
using namespace std;

TEST(exploreMe,check_for_buffer_overflow) {
  int a = 20000;
  int b = 2000000;
  string c = "FUZZING";
  
  EXPECT_EQ(exploreMe(a,b,c), 1);
}

