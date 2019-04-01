#include "Lexer.hpp"
#include <regex>
void	Lexer::run_lexer(std::list <std::string> *commands)
{
	// const std::array <std::regex, 4> reg;
//	reg[0] = ("^(pop|add|sub|mul|div|pow|mod|print|exit|;;|;)$");
	for (auto var : *commands)
		std::cout << var << std::endl;
}


Lexer::Lexer(/* args */)
{

}

Lexer::~Lexer()
{
	std::cout << "by by from  " << __func__ << std::endl;
}