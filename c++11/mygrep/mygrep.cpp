// =====================================================================================
// 
//       Filename:  mygrep.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2013年11月04日 17时43分51秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <fstream>

#include "TextQuery.h"

std::ostream &print(std::ostream &os, const QueryResult &qr);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << "使用方法： " << argv[0] << " 文件名" << std::endl;
		return 0;
	}

	std::ifstream infile(argv[1]);

	TextQuery tq(infile);

	while (true) {
		std::cout << "输入单词查询，输入 q 退出：";
		std::string input;
		if (!(std::cin >> input) || input == "q") {
			break;
		}
		print(std::cout, tq.query(input)) << std::endl;
	}

	return 0;
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " 出现了 " << qr.lines->size() << " 次：" << std::endl;

	for (auto num : *(qr.lines)) {
		os << "\t(line " << num + 1 << ") " << (*(qr.file))[num] << std::endl;
	}

	return os;
}

