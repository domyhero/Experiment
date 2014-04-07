// =====================================================================================
// 
//       Filename:  LexicalAnalysis.h
//
//    Description:  词法分析
//
//        Version:  1.0
//        Created:  2014年04月01日 08时45分52秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef LEXICALANALYSIS_H_
#define LEXICALANALYSIS_H_

#include <list>

#include "Types.h"

/// 词法分析
class LexicalAnalysis {
public:
	LexicalAnalysis();
	~LexicalAnalysis();
	
	/// 构造符号流
	void cerateTokensStream();
	
	/// 输出符号流
	void printTokensStream();

private:
	/// 指针移动到下一个非空白字符
	const char *skipBlank(const char *stream);

	/// 解析一个Token
	bool analyseToken(const char *stream);

	/// 解析整数
	int analyseInt(const char *stream);

	/// 解析浮点数
	double analyseDouble(const char *stream);

private:
	std::list<TokenNode> tokens_stream_;
};

#endif 	// LEXICALANALYSIS_H_
