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
public:
	void StartTokenizing(Parser &, std::list <std::string> *, std::list <t_cmds> *, bool);
	t_cmds CreateNewCommand(bool , std::string &);

	explicit Lexer();
	~Lexer();

private:
	bool istream;

	enum cmd_type TransformValueToCmdtype(std::string &);
	enum eOperandType TransformValueToOtype(std::string &);
	void AnalyseCommandQueue(std::list <std::string> *, std::string);
	bool CheckForExitCommand(std::list <std::string> *);

};

#endif
