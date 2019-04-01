#ifndef LEXER_HPP
# define LEXER_HPP
#include <string>
#include <iostream>
#include <list>
#include <unistd.h>

class Lexer
{
private:

public:
	void	run_lexer(std::list <std::string> *commands);
	void	check_commands();
	Lexer(/* args */);
	~Lexer();
};





#endif