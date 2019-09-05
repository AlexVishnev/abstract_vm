#ifndef PARSER_HPP 
# define PARSER_HPP

#include <list>
#include <fstream>
#include <iostream>
#include "defines.hpp"


class Parser
{

public:
	Parser();
	Parser(Parser const &ref);
	Parser &operator=(const Parser &ref);
	~Parser();
	
	std::string		 &GetFilePath();
	void			_read(const int mode, const char **cfg_file);
	bool			isFilestream(const int mode);
	std::list <std::string> *GetCommandsList();

private:
	std::string					FilePath;
	std::list <std::string>	Commands;
};

#endif // !PARSER_HPP 