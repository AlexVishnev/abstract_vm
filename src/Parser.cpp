#include "Parser.hpp"

bool Parser::is_filestream(const int mode)
{
	return (mode == 2);
}

std::list <std::string> *Parser::GetCommandsList()
{
	return (&this->Commands);
}
void Parser::_read(const int mode, const char **cfg_file)
{
	if (is_filestream(mode))
		FilePath = cfg_file[1];
	else{
		FilePath = "UserInput";
		PRINT_WARNING("INFO:  Using standart input for declaring commands\n\
	  Write comands separated by 'Enter' for adding them into command quene \n\
	  Press 'Ctrl + D' for execution commands\n");
	}
	

	std::ifstream file(FilePath);
	std::string buffer;

	if (file.is_open() && !file.eof()) {

		PRINT_GREEN(FilePath);
		while (std::getline(file, buffer))
		{
			Commands.push_back(buffer);
		}
		file.close();
	}
	else {
		while (std::getline(std::cin, buffer))
		{
			Commands.push_back(buffer);
			if (buffer == ";;" || buffer == "exit")
				break ;
		}
	}
}

Parser &Parser::operator=(Parser const &ref)
{
	if (this != &ref){
		FilePath = ref.FilePath;
		Commands = ref.Commands;
	}
	return *this;
}

std::string &Parser::GetFilePath()
{
	return this->FilePath;
}
Parser::Parser(){

}

Parser::~Parser(){
}