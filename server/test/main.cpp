#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TestGroupName, Subtest_1) {
  ASSERT_TRUE(1 == 1);
}


int main(int argc, char **argv)
{
	//system("chcp 1251 > nul");
	//setlocale(LC_ALL, "ru_RU.UTF-8");

	//setlocale(LC_ALL, "Russian_Russia.1251");

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}