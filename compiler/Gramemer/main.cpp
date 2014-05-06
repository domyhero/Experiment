// =====================================================================================
// 
//       Filename:  main.cpp
//
//    Description:  测试程序
//
//        Version:  1.0
//        Created:  2014年05月06日 09时28分36秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>

#include "LL1.h"

int main(int argc, char *argv[])
{
	LL1 ll1;

	ll1.input_grammer();
	ll1.analyse_grammer();
	ll1.output_all_intermediate_data();

	return 0;
}

