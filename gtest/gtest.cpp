// =====================================================================================
// 
//       Filename:  gtest.c
//
//    Description:  gtest 测试
//
//        Version:  1.0
//        Created:  2013年05月13日 20时14分02秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <gtest/gtest.h>
#include <climits>

int add(int a, int b)
{
	return (a + b);
}

// ASSERT_* 系列的断言，当检查点失败时，退出当前函数（注意：并非退出当前案例）
// EXPECT_* 系列的断言，当检查点失败时，继续往下执行

TEST(TEST_BOOL, ONLY_TEST)
{
	/*
	 * 布尔值检查
	 */
	EXPECT_TRUE(add(1, 1));
	EXPECT_FALSE(add(0, 0));
}

TEST(TEST_INT, ONLY_TEST)
{
	/* 
	 * 数值类型测试
	 */
	// 相等测试
	EXPECT_EQ(2, add(1, 1));
	// 不等测试
	EXPECT_NE(3, add(1, 1));
	// 大于测试
	EXPECT_GT(4, add(1, 1));
	// 大与等于测试
	EXPECT_GT(4, add(1, 1));
	// 小于测试
	EXPECT_LT(1, add(1, 1));
	// 小于等于测试
	EXPECT_LE(1, add(1, 1));
}

TEST(TEST_STRING, ONLY_TEST)
{
	/*
	 * 字符串检查
	 */
	// 相等测试
	EXPECT_STREQ("test", "test");
	// 不相等测试
	EXPECT_STRNE("hello", "world");
	// 相等测试 - 忽略 char 和 wchar_t
	EXPECT_STRCASEEQ("test", "test");
	// 不相等测试 - 忽略 chae 和 wchar_t
	EXPECT_STRCASENE("hello", "world");
}

TEST(TEST_FLOAT_DOUBLE, ONLY_TEST)
{
	/*
	 * 浮点型检查
	 */
	// 相等
	EXPECT_FLOAT_EQ(1.1, 1.1);
	EXPECT_DOUBLE_EQ(1.1, 1.1);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

