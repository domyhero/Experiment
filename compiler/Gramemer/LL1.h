// =====================================================================================
// 
//       Filename:  LL1.h
//
//    Description:  预测分析法
//
//        Version:  1.0
//        Created:  2014年05月06日 08时08分47秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef LL1_H_
#define LL1_H_

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>

class LL1
{
public:
	LL1() {}
	~LL1() {}

	/// 从标准输入读取文法(约定大写字母为非终结符，其他为终结符)
	void input_grammer();

	/// 分析处理文法
	bool analyse_grammer();

	/// 分析一个句子是否符合本文法
	bool analyse_sentence(std::string sentence);

	/// 输出所有中间数据
	void output_all_intermediate_data();

	/// 输出原始文法
	void output_input_grammer();
	
	/// 输出修正后的文法
	void output_fixed_grammer();

	/// 输出所有的终结符和非终结符
	void output_all_symbol();
	
	/// 输出所有的非终结符的产生式
	void output_all_sentence();

	/// 输出每个非终结符的frist集和follow集
	void output_frist_follow_set();

	/// 输出预测分析表
	void output_analusis_table();

private:
	/// 消除文法左递归
	void dispose_left_recursion();

	/// 提取公共左因子
	void dispose_public_left_factor();

	/// 分析生成终结符和非终结符集合
	void analse_symbol();

	/// 分析拆分出非终结符对应的产生式
	void analyse_sentence();

	/// 分析和生成first集和follow集
	void analyse_first_follow_set();

	/// 求一个元素first集
	void get_symbol_first(char ch, std::set<char> &first_set);

	/// 求一个元素的follow集
	void get_symbol_follow(char ch, std::set<char> &follow_set);

	/// 分析某终结符是否能推出空
	bool is_to_empty(char ch);

	/// 判断是否为LL1文法
	bool isLL1();

	/// 构建预测分析表
	void create_analysis_table();
	/**
	 * 判断一个符号是终结符还是非终结符
	 * 返回 true 为终结符，false 为非终结符
	 */
	inline bool is_terminal_symbol(char ch);
	
	std::vector<std::string> input_grammer_; 	// 保存原始的文法
	std::vector<std::string> fixed_grammer_; 	// 修正后的文法
	std::set<char> terminal_set_; 			// 终结符集合
	std::set<char> nonterminal_set_; 		// 非终结符集合
	std::multimap<char, std::string> sentent_; 	// 非终结符的产生式集
	std::map<char, std::set<char>> first_map_; 	// 所有非终结符的first集
	std::map<char, std::set<char>> follow_map_; 	// 所有非终结符second集
	std::map<char, std::vector<int>> analysis_table_; // 预测分析表，int 为fixed_grammer中相应文法的下标
};

#endif 	// LL1_H_
