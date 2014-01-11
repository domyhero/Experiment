// =====================================================================================
// 
//       Filename:  unit_test.cpp
//
//    Description:  测试代码
//
//        Version:  1.0
//        Created:  2013年05月14日 17时33分52秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <gtest/gtest.h>

int passwd_check(const char *passwd);

TEST(TEST_check_passwd, Return_int)
{
	/*
	 * 错误密码
	 */

	// 长度不够
	EXPECT_EQ(0, passwd_check("Aa%1589"));
	// 长度超出
	EXPECT_EQ(0, passwd_check("1254dAgdhnhgtyhgf"));
	// 密码强度不够
	EXPECT_EQ(0, passwd_check("115AHNGJMMM"));
	EXPECT_EQ(0, passwd_check("%#JHNGJMMM"));
	EXPECT_EQ(0, passwd_check("115aaaasssss"));
	// 非法字符
	EXPECT_EQ(0, passwd_check("(nk12&Ajsdds"));
	EXPECT_EQ(0, passwd_check("$$HA45+222"));
	EXPECT_EQ(0, passwd_check("1512%$saA#!--"));
	 

	/*
	 * 正确密码
	 */

	EXPECT_EQ(1, passwd_check("1254$!JHJsss"));
	EXPECT_EQ(1, passwd_check("12JHs5et"));
	EXPECT_EQ(1, passwd_check("1247%#!As5sAssiu"));
	EXPECT_EQ(1, passwd_check("122@@s3dAA6ew"));
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

