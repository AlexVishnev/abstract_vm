#include "Parser.hpp"

bool Parser::isFilestream(const int mode) {
	return (mode == 2);
}

std::list <std::string> *Parser::GetCommandsList() {
	return (&this->Commands);
}

void Parser::_read(const int mode, const char **cfg_file)
{
	if (isFilestream(mode))
		FilePath = cfg_file[1];
	else {
		FilePath = "UserInput";
		PRINT_WARNING("AVM INFO: Run in Live mode\n\tType -h,--help for assistance");
	}
	

	std::ifstream file(FilePath);
	std::string buffer;

	if (file.is_open() && !file.eof()) {
		while (std::getline(file, buffer))
			Commands.push_back(buffer);

		file.close();
	}
	else
		return ;

}

Parser &Parser::operator=(Parser const &ref)
{
	if (this != &ref){
		FilePath = ref.FilePath;
		Commands = ref.Commands;
	}
	return *this;
}

std::string &Parser::GetFilePath() {
	return this->FilePath;
}

Parser::Parser(){ }

Parser::~Parser()
{
	Commands.clear();
}