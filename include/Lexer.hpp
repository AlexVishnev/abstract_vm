#ifndef LEXER_HPP
# define LEXER_HPP
#include <string>
#include <iostream>
#include <list>
#include <unistd.h>
#include <regex>
#include "Cmds.hpp"
#include "Parser.hpp"

class Lexer
{
private:
	enum cmd_type		TransformValueToCmdtype(std::string &ref);
	enum eOperandType	TransformValueToOtype(std::string &ref);
public:
	void	run_lexer(Parser &parser, std::list <std::string> *commands, std::list <t_cmds> *ref);
	void	New_command(std::list <t_cmds> *cmd_quene, std::string condition, std::string &c_type);
	void	check_commands();
	Lexer();
	~Lexer();
};





#endif