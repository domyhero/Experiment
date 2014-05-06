// =====================================================================================
// 
//       Filename:  Types.cpp
//
//    Description:  关键字类型定义
//
//        Version:  1.0
//        Created:  2014年04月08日 11时16分56秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <string>
#include <map>

#include "Types.h"

std::map<std::string, TokenType> keywordMap = {
	{"auto", AUTO}, {"break", BREAK}, {"case", CASE}, {"char", CHAR},
	{"const", CONST}, {"continue", CONTINUE}, {"default", DEFAULT}, {"do", DO},
	{"double", DOUBLE}, {"else", ELSE}, {"enum", ENUM}, {"extern", EXTERN},
	{"float", FLOAT}, {"for", FOR}, {"goto", GOTO}, {"if", IF},
	{"int", INT}, {"long", LONG}, {"register", REGISTER}, {"return", RETURN},
	{"short", SHORT}, {"signed", SIGNED}, {"sizeof", SIZEOF}, {"static", STATIC},
	{"struct", STRUCT}, {"switch", SWITCH}, {"typedef", TYPEDEF}, {"union", UNION},
	{"unsigned", UNSIGNED}, {"void", VOID}, {"volatile", VOLATILE}, {"while", WHILE}
};
