// =====================================================================================
// 
//       Filename:  LexicalAnalysis.cpp
//
//    Description:  词法分析
//
//        Version:  1.0
//        Created:  2014年04月01日 08时55分18秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <fstream>

#include "LexicalAnalysis.h"
#include "Error.h"
#include "Types.h"

LexicalAnalysis::LexicalAnalysis()
{

}

LexicalAnalysis::~LexicalAnalysis()
{

}
	
/// 构造符号流
void LexicalAnalysis::cerateTokensStream()
{
	std::cout << "构造符号流" << std::endl;
}
	
/// 输出符号流
void LexicalAnalysis::printTokensStream()
{
	std::cout << "输出符号流" << std::endl;
}

/// 指针移动到下一个非空白字符
const char *LexicalAnalysis::skipBlank(const char *stream)
{
	return stream;
}

/// 解析一个Token
bool LexicalAnalysis::analyseToken(const char *stream)
{
	return true;
}

/// 解析整数
int LexicalAnalysis::analyseInt(const char *stream)
{
	return 0;
}

/// 解析浮点数
double LexicalAnalysis::analyseDouble(const char *stream)
{
	return 0.0;
}

