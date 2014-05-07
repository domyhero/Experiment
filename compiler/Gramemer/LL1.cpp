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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <stdexcept>

#include "LL1.h"

/// 从标准输入读取文法(约定大写字母为非终结符，其他为终结符)
void LL1::input_grammer()
{
	std::string tmpstr;

	while (std::cin >> tmpstr) {
		input_grammer_.push_back(tmpstr);
	}
}

/// 从文件读取文法(约定大写字母为非终结符，其他为终结符)
void LL1::input_grammer_by_file(std::string filename)
{
	std::fstream file(filename);
	std::string tmpstr;

	if (!file.is_open()) {
		throw std::runtime_error("文件打开错误，请确认文件存在!");
	}

	while (file >> tmpstr) {
		input_grammer_.push_back(tmpstr);
	}
}

/// 分析处理文法
void LL1::analyse_grammer()
{
	dispose_left_recursion();
	dispose_public_left_factor();
	analse_symbol();
	analyse_sentence();
	analyse_first_follow_set();
	
	try {
		isLL1();
	} catch (std::runtime_error err) {
		throw err;
	}

	create_analysis_table();
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
				if (ch != '^') {
					terminal_set_.insert(ch);
				}
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
	/// follow集的计算需要依赖first集的数据，所以必须先求完first集合再求follow集
	for (auto nonch : nonterminal_set_) {
		get_symbol_first(nonch, first_map_[nonch]);
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
					// 判断之后终结符能否推出空
					for (int j = i+1; j < sen.size(); ++j) {
						if (is_terminal_symbol(sen[i]) || !is_to_empty(sen[i])) {
							break;
						}
					}
					get_symbol_follow(sen_pair.first, follow_set);
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

// 求非终结符的候选首符集
void LL1::analyse_symbol_select()
{
	for (auto ch : nonterminal_set_) {
		auto idx = sentent_.find(ch);
		while (idx != sentent_.end() && idx->first == ch) {
			for (auto nonch : idx->second) {
				if (!is_terminal_symbol(nonch)) {
					for (auto c : first_map_[nonch]) {
						nonterminal_select_[nonch].insert(c);
					}
				}
			}
			++idx;
		}
	}
}

/// 判断是否为LL1文法
void LL1::isLL1()
{
	// 1. 判断文法是否存在左递归
	for (auto &senpair : sentent_) {
		for (auto ch : senpair.second) {
			// 发现左递归则返回失败
			if (senpair.first == ch) {
				throw std::runtime_error("存在左递归，当前处理文法不是LL1文法，无法继续处理!");
			}
		}
	}
	
	// 2. 判断文法除过开始符号的非终结符号之间first集合两两不相交
	for (auto nonch : nonterminal_set_) {
		if (nonch != 'S') {
			for (auto ch : nonterminal_set_) {
				// 不检测开始符号、跳过自身
				if (ch != 'S' && nonch != ch) {
					// 比较当前两个非终结符的first集是否存在交集
					std::set<char> &first_set1 = first_map_[nonch];
					std::set<char> &first_set2 = first_map_[ch];
					for (auto c : first_set1) {
						if (first_set2.find(c) != first_set2.end()) {
							throw std::runtime_error("非终结符first集存在交集，"
									"当前处理文法不是LL1文法，无法继续处理!");
						}
					}
				}
			}
		}
	}

	// 3. 判断文法某个非终结符的select集(候选首符集)存在空时，该非终结符的first集和follow集不相交
	// 求所有非终结字符的select集
	analyse_symbol_select();

	for (auto &nonpair : nonterminal_select_) {
		for (auto ch : nonpair.second) {
			// 某个候选首符集中出现空集
			if (ch == '^') {
				// 检测该非终结符的first集和follow集是否存在交集
				std::set<char> &first_set = first_map_[nonpair.first];
				std::set<char> &follow_set = follow_map_[nonpair.first];
				for (auto c : first_set) {
					if (follow_set.find(c) != follow_set.end()) {
						throw std::runtime_error("候选首符集存在空的非终结符first集和follow集存在交集，"
								"当前处理文法不是LL1文法，无法继续处理!");
					}
				}
			}
		}
	}
}

/// 构建预测分析表
void LL1::create_analysis_table()
{
	terminal_set_.insert('#');

	// 遍历每一个非终结符，构造分析表
	for (auto nonch : nonterminal_set_) {
		auto idx = sentent_.find(nonch);
		while (idx != sentent_.end() && idx->first == nonch) {
			if (idx->second != "^") {
				// 遍历first(nonch)，加入产生式
				for (auto ch : first_map_[nonch]) {
					if (ch != '^') {
						analysis_table_[nonch][ch] = idx->second;
					}
				}
			} else {
				// 遍历follow(nonch)，加入产生式
				for (auto ch: follow_map_[nonch]) {
					if (ch != '^') {
						analysis_table_[nonch][ch] = idx->second;
					}
				}
			}
			++idx;
		}
	}
	
	// 所有空位置为 "Err"
	for (auto nonch : nonterminal_set_) {
		for (auto ch : terminal_set_) {
			if (analysis_table_[nonch].find(ch) == analysis_table_[nonch].end()) {
				analysis_table_[nonch][ch] = "Err";
			}
		}
	}
}

/// 分析一个句子是否符合本文法
bool LL1::analyse_sentence(std::string sentence)
{
	#define BLANK "---------------------------------------------------------------"
	
	std::cout << BLANK << std::endl;
	std::cout << std::left << std::setw(20) << " 步骤";
	std::cout << std::left << std::setw(20) << "符号串";
	std::cout << std::left << std::setw(20) << "输入串";
	std::cout << std::left << std::setw(20) << "所用产生式" << std::endl;
	std::cout << BLANK << std::endl;

	int step = 0;
	std::vector<char> symb_stack; 	// 需要打印中间过程，无奈只好用vector定义stack
	symb_stack.push_back('#');
	symb_stack.push_back('S');
	
	// 输入串添加#结尾
	sentence += "#";

	// 步骤 0
	output_analyse_step(step++, symb_stack, sentence, std::string(""));

	// 开始分析过程
	while (symb_stack.size() > 1) {
		char nonch = symb_stack.back();
		if (nonch == sentence[0]) {
			symb_stack.pop_back();
			sentence.erase(0, 1);
			output_analyse_step(step++, symb_stack, sentence, std::string(""));
			continue;
		}
		// 取得当前非终结符symb_stack.bask()面临输入sentence[0]的产生式
		std::string product = analysis_table_[nonch][sentence[0]];
		if (product != "Err") {
			symb_stack.pop_back();
			if (product != "^") {
				// 逆序压栈
				for (int i = product.size()-1; i >= 0; --i) {
					symb_stack.push_back(product[i]);
				}
			}
			output_analyse_step(step++, symb_stack, sentence, std::string("") + nonch + " = " + product);
		} else {
			std::cout << "找不到 " << nonch << " 面临输入 " << sentence[0] 
				<< " 时的对应产生式!\n" << BLANK << "\n" << std::endl;
			return false;
		}
	}
	
	std::cout << BLANK << "\n" << std::endl;

	if (symb_stack.size() == 1 && symb_stack[0] == '#' && sentence == "#") {
		return true;
	}

	return false;
	#undef BLANK
}

/// 打印分析的步骤
void LL1::output_analyse_step(int step, std::vector<char> &symb_stack, std::string sentence, std::string product)
{
	std::cout << " " << std::left << std::setw(17) << step;
	std::string str_stack;
	for (auto ch : symb_stack) {
		str_stack += ch;
	}
	std::cout << std::left << std::setw(17) << str_stack;
	std::cout << std::left << std::setw(17) << sentence;
	std::cout << std::left << std::setw(17) << product << std::endl;
}

/// 输出所有中间数据
void LL1::output_all_intermediate_data()
{
	output_input_grammer();
	output_fixed_grammer();
	output_all_symbol();
	output_all_sentence();
	output_frist_follow_set();
	output_select();
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
	for (auto &nonch : nonterminal_set_) {
		std::cout << nonch << " ";
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
	for (auto nonch : nonterminal_set_) {
		auto idx = sentent_.find(nonch);
		assert(idx != sentent_.end());
		while (idx != sentent_.end() && idx->first == nonch) {
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

/// 输出每个非终结符的select集
void LL1::output_select()
{
	std::cout << "非终结符的候选首符集:" << std::endl;
	for (auto &selepair : nonterminal_select_) {
		std::cout << selepair.first << " : ";
		for (auto ch : selepair.second) {
			std::cout << ch << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/// 输出预测分析表
void LL1::output_analusis_table()
{ 	
	std::cout << "预测分析表:" << std::endl;
	int blank_size = terminal_set_.size() * 12 + 8;

	for (int i = 0; i < blank_size; ++i) {
		std::cout << "-";
	}
	std::cout << std::endl << "     |    ";

	for (auto ch : terminal_set_) {
		std::cout << std::left << std::setw(12) << ch;
	}
	std::cout << std::endl;
	for (int i = 0; i < blank_size; ++i) {
		std::cout << "-";
	}
	std::cout << std::endl;

	for (auto &nonmap : analysis_table_) {
		std::cout << "  " << nonmap.first << "  |    "; 
		for (auto ch : terminal_set_) {
			std::cout << std::left << std::setw(12) 
				<< std::string("") + nonmap.first + " = "  + nonmap.second[ch];
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < blank_size; ++i) {
		std::cout << "-";
	}
	std::cout << "\n" << std::endl;
}

/**
 * 判断一个符号是终结符还是非终结符号
 * 返回 true 为终结符号，false 为非终结符
 */
inline bool LL1::is_terminal_symbol(char ch)
{
	return !(ch >= 'A' && ch <= 'Z');
}
