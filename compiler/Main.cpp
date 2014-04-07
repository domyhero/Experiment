// =====================================================================================
// 
//       Filename:  Main.cpp
//
//    Description:  主函数
//
//        Version:  1.0
//        Created:  2014年04月07日 16时44分39秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>

#include "LexicalAnalysis.h"
#include "Types.h"
#include "Error.h"

int main(int argc, char *argv[])
{
	LexicalAnalysis lexAnalysis;

	lexAnalysis.cerateTokensStream();
	lexAnalysis.printTokensStream();

	return 0;
}

