// =====================================================================================
// 
//       Filename:  QueryResult.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2013年11月04日 17时01分46秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================


#ifndef  QUERYRESULT_INC
#define  QUERYRESULT_INC

#include <memory>
#include <vector>
#include <set>
#include <map>

#include "QueryResult.h"

class QueryResult {
	using line_no = std::vector<std::string>::size_type;
	friend std::ostream& print(std::ostream &, const QueryResult &);
public:
	QueryResult(std::string s,
		    std::shared_ptr<std::set<line_no>> p,
		    std::shared_ptr<std::vector<std::string>> f) :
		sought(s), lines(p), file(f) {}

private:
	std::string sought;
	std::shared_ptr<std::set<line_no>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};

#endif   // ----- #ifndef QUERYRESULT_INC  -----

