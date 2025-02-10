#pragma once

#include <gtest/gtest.h>

#include <bor.hpp>

TEST(TestBase, Preambule) {
  {
    Tbor bor("aaabbbcccdddeeefffgggqqq");
    std::vector<bool> exp_pr = 
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(bor.get_preambule(), exp_pr);
  }
  {
    Tbor bor("abbccc");
    std::vector<bool> exp_pr = 
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0};
    EXPECT_EQ(bor.get_preambule(), exp_pr);
  }
  {
    Tbor bor("qwertyqsr");
    std::vector<bool> exp_pr = 
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(bor.get_preambule(), exp_pr);
  }
}
