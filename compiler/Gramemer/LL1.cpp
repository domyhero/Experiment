// =====================================================================================
// 
//       Filename:  LL1.cpp
//
//    Description:  预测分析法
//
//        Version:  1.0
//        Created:  2014年05月06日 08时08分26秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <cassert>
#include <stdexcept>

#include "LL1.h"

/// 从标准输入读取文法
void LL1::input_grammer()
{
	std::string tmpstr;
	while (std::cin >> tmpstr) {
		input_grammer_.push_back(tmpstr);
	}
}

/// 分析处理文法
bool LL1::analyse_grammer()
{
	dispose_left_recursion();
	dispose_public_left_factor();
	analse_symbol();
	analyse_sentence();
	analyse_first_follow_set();
	
	if (!isLL1()) {
		return false;
	}

	create_analysis_table();

	return true;
}

/// 消除文法左递归
void LL1::dispose_left_recursion()
{
	// 拷贝输入文法到修正文法集合
	for (auto &grammer_str : input_grammer_) {
		fixed_grammer_.push_back(grammer_str);
	}

	// TODO 判断文法左递归以及消除
}

/// 提取公共左因子
void LL1::dispose_public_left_factor()
{
	// TODO
}

/// 分析生成终结符和非终结符集合
void LL1::analse_symbol()
{
	for (auto &grammer_str : fixed_grammer_) {
		for (auto &ch : grammer_str) {
			if (ch == '=' || ch == '|') {
				continue;
			}
			if (is_terminal_symbol(ch)) {
				terminal_set_.insert(ch);
			} else {
				nonterminal_set_.insert(ch);
			}
		}
	}
}

/// 分析拆分出非终结符对应的产生式
void LL1::analyse_sentence()
{
	for (auto sen : fixed_grammer_) {
		std::string::size_type i = sen.find("=");
		while (i != std::string::npos) {
			++i;	
			std::string::size_type j = sen.find("|", i);
			if (j != std::string::npos) {
				sentent_.insert(make_pair(sen[0], sen.substr(i, j-i)));
			} else {
				sentent_.insert(make_pair(sen[0], sen.substr(i, sen.size()-i)));
			}
			i = j;
		}
	}
}

/// 分析和生成first集和follow集
void LL1::analyse_first_follow_set()
{
	for (auto ch : nonterminal_set_) {
		get_symbol_first(ch, first_map_[ch]);
	}

	for (auto ch : nonterminal_set_) {
		get_symbol_follow(ch, follow_map_[ch]);
	}
}

/// 求一个元素first集
void LL1::get_symbol_first(char ch, std::set<char> &first_set)
{
	auto idx = sentent_.find(ch);
	while (idx != sentent_.end() && idx->first == ch) {
		std::string sen(idx->second);
		for (int i = 0; i < sen.size(); ++i) {
			// 如果第一个字符是终结符则直接加入
			if (is_terminal_symbol(sen[i])) {
				first_set.insert(sen[i]);
			} else {
				/// 非终结符则递归求其first集
				get_symbol_first(sen[i], first_set);
				// 当前终结符不能推导出空则结束当前推导
				if (!is_to_empty(sen[i])) {
					break;
				}
				// 最后一个符号依然含有空，则first集加入空
				if (i + 1 == sen.size()) {
					first_set.insert('^');
				}
			}
		}
		++idx;
	}
}

/// 求一个元素的follow集
void LL1::get_symbol_follow(char ch, std::set<char> &follow_set)
{
	// 遍历每一个产生式
	for (auto &sen_pair : sentent_) {
		std::string sen(sen_pair.second);
		// 遍历当前产生式
		for (int i = 0; i < sen.size(); ++i) {
			// 如果当前非终结符不位于最后
			if (ch == sen[i] && i != sen.size()-1) {
				// 如果当前元素之后紧跟的是终结符号则加入
				if (is_terminal_symbol(sen[i+1])) {
					follow_set.insert(sen[i+1]);
				} else {
					// 如果是非终结符，则把该终结符的first集合中的非空加入
					// 这要求必须先求first集合，再求follow集合
					for (auto ch : first_map_[sen[i+1]]) {
						if (ch != '^') {
							follow_set.insert(ch);
						}
					}
				}
			}
			// 如果当前非终结符位于最后
			if (ch == sen[i] && i == sen.size()-1) {
				get_symbol_follow(sen_pair.first, follow_set);
			}
		}
	}
	// 开始符号要加入#
	if (ch == 'S') {
		follow_set.insert('#');
	}
}

/// 分析某终结符是否能推出空
bool LL1::is_to_empty(char ch)
{
	auto idx = sentent_.find(ch);
	while (idx != sentent_.end() && idx->first == ch) {
		if (idx->second == "^") {
			return true;
		}
		++idx;
	}
	
	return false;
}


/// 判断是否为LL1文法
bool LL1::isLL1()
{
	return true;
}

/// 构建预测分析表
void LL1::create_analysis_table()
{

}

/// 分析一个句子是否符合本文法
bool LL1::analyse_sentence(std::string sentence)
{
	return true;
}

/// 输出所有中间数据
void LL1::output_all_intermediate_data()
{
	output_input_grammer();
	output_fixed_grammer();
	output_all_symbol();
	output_all_sentence();
	output_frist_follow_set();
	output_analusis_table();
}

/// 输出原始文法
void LL1::output_input_grammer()
{
	std::cout << "原始文法:" << std::endl;
	for (auto &str : input_grammer_) {
		std::cout << str << std::endl;
	}
	std::cout << std::endl;
}

/// 输出修正后的文法
void LL1::output_fixed_grammer()
{
	std::cout << "修正后文法:" << std::endl;
	for (auto &idx : fixed_grammer_) {
		std::cout << idx << std::endl;
	}
	std::cout << std::endl;
}

/// 输出所有的终结符和非终结符
void LL1::output_all_symbol()
{
	std::cout << "非终结符: ";
	for (auto &ch : nonterminal_set_) {
		std::cout << ch << " ";
	}
	std::cout << std::endl;
	std::cout << "终结符: ";
	for (auto &ch : terminal_set_) {
		std::cout << ch << " ";
	}
	std::cout << '\n' << std::endl;
}

/// 输出所有的非终结符的产生式
void LL1::output_all_sentence()
{
	std::cout << "非终结符推导式: " << std::endl;
	for (auto ch : nonterminal_set_) {
		auto idx = sentent_.find(ch);
		assert(idx != sentent_.end());
		while (idx != sentent_.end() && idx->first == ch) {
			std::cout << idx->first << " = " << idx->second << std::endl;
			++idx;
		}
	}
	std::cout << std::endl;
}

/// 输出每个非终结符的frist集和follow集
void LL1::output_frist_follow_set()
{
	std::cout << "Frist集:" << std::endl;
	for (auto &idx : first_map_) {
		std::cout << "Frist(" << idx.first << ") : ";
		for (auto &char_set : idx.second) {
			std::cout << char_set << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Follow集:" << std::endl;
	for (auto &idx : follow_map_) {
		std::cout << "Follow(" << idx.first << ") : ";
		for (auto &char_set : idx.second) {
			std::cout << char_set << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/// 输出预测分析表
void LL1::output_analusis_table()
{
	std::cout << "预测分析表:" << std::endl;
	std::cout << std::endl;
}

/**
 *
 * 判断一个符号是终结符还是非终结符号
 * 返回 true 为终结符号，false 为非终结符
 */
inline bool LL1::is_terminal_symbol(char ch)
{
	return !(ch >= 'A' && ch <= 'Z');
}
