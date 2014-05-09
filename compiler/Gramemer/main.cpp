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
#include <stdexcept>

#include "LL1.h"

int main(int argc, char *argv[])
{
	LL1 ll1;

	if (argc == 2) {
		try {
			ll1.input_grammer_by_file(argv[1]);
		} catch (std::runtime_error err) {
			std::cout << err.what() << std::endl;
			exit(-1);
		}
	} else {
		std::cout << "请逐一输入原始文法(输入EOF结束)：" << std::endl;
		ll1.input_grammer();
	}

	try {
		ll1.analyse_grammer();
	} catch (std::runtime_error err) {
		ll1.output_input_grammer();
		ll1.output_all_symbol();
		ll1.output_all_sentence();
		ll1.output_frist_follow_set();
		std::cout << err.what() << std::endl;
		exit(-1);
	}

	ll1.output_all_intermediate_data();

	std ::cout << "请输入要测试的句子: ";
	std::string sentence = "aa";
	while (std::cin >> sentence) {
		if (ll1.analyse_sentence(sentence)) {
			std ::cout << "句子 " << sentence << " 符合文法" << std::endl;
		} else {
			std ::cout << "句子 " << sentence << " 不符合文法" << std::endl;
		}
		std ::cout << "\n请输入要测试的句子: ";
	}

	std::cout << std::endl;

	return 0;
}

