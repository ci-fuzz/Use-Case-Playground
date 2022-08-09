#include <gtest/gtest.h>
#include <string.h>
#include "../src/explore_me.h"
using namespace std;

TEST(exploreMe,my_gtest) {
  int a = 2000000;
  int b = 2000000;
  string c = "FUZZING";

  EXPECT_EQ(exploreMe(a,b,c), 1);
}

