// =====================================================================================
// 
//       Filename:  TextQuery.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2013年11月04日 16时26分05秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef  TEXTQUERY_INC
#define  TEXTQUERY_INC

#include <vector>
#include <string>
#include <set>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>

#include "QueryResult.h"

class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;

private:
	// 输入文件
	std::shared_ptr<std::vector<std::string>> file;
	// 每个单词到它所在行号的集合和映射
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

#endif   // ----- #ifndef TEXTQUERY_INC  -----
