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

int mail_check(const char *str_mail);

TEST(TEST_check_passwd, Return_int)
{
	/*
	 * 错误邮箱
	 */

	// 多个@
	EXPECT_EQ(0, mail_check("Aa%@1@gmail.com"));
	EXPECT_EQ(0, mail_check("1254@dAgdhnh@qq.com"));
	// 含有空格
	EXPECT_EQ(0, mail_check("115 AHNGJM@qq.com"));
	EXPECT_EQ(0, mail_check(" ddsdasd@qq.com"));
	// 其他符号
	EXPECT_EQ(0, mail_check("115%&^$aaaass@qq.com"));
	// 其他域名
	EXPECT_EQ(0, mail_check("msald@tt.com"));
	EXPECT_EQ(0, mail_check("cscasfnainso@0xffffff.org"));
	EXPECT_EQ(0, mail_check("ss@bs@.com"));
	 

	/*
	 * 正确邮箱
	 */

	EXPECT_EQ(1, mail_check("darkiller@qq.com"));
	EXPECT_EQ(1, mail_check("7758485aaa@gmail.com"));
	EXPECT_EQ(1, mail_check("5615sfaf@sina.com.cn"));
	EXPECT_EQ(1, mail_check("2525@163.com"));
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

