#ifndef PARSER_HPP 
# define PARSER_HPP



#include <list>
#include <fstream>
#include <iostream>

#define PRINT_GREEN(x) std::cout << "\033[0;32m" << x << "\033[0m" << std::endl;
#define PRINT_RED(x) std::cout << "\033[0;31m" << x << "\033[0m" << std::endl;
class Parser
{

public:
	Parser();
	Parser(Parser const &ref);
	Parser &operator=(const Parser &ref);
	~Parser();
	
	void	_read(const int mode, const char **cfg_file);
	bool	is_filestream(const int mode);

private:
	std::string file_path;
	std::list <std::string > comands;
};

#endif // !PARSER_HPP 