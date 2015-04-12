// =====================================================================================
// 
//       Filename:  TextQuery.c
//
//    Description:  
//
//        Version:  1.0
//        Created:  2013年11月04日 16时43分28秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
	std::string text;

	while (std::getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		std::string word;
		while (line >> word) {
			auto &lines = wm[word];
			if (!lines) {
				lines.reset(new std::set<line_no>);
			}
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &sougth) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);

	auto loc = wm.find(sougth);

	if (loc == wm.end()) {
		return QueryResult(sougth, nodata, file);
	} else {
		return QueryResult(sougth, loc->second, file);
	}
}

