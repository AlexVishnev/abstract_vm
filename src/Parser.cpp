#include "Parser.hpp"

bool Parser::isFilestream(const int mode) {
	return (mode == 2);
}

std::list <std::string> *Parser::GetCommandsList() {
	return (&this->Commands);
}

void Parser::Read(const int mode, const char **cfg_file)
{
	if (isFilestream(mode))
		Parser::FilePath = cfg_file[1];
	else {
		Parser::FilePath = "UserInput";
		PRINT_WARNING("AVM INFO: Run in Live mode\n\tType -h,--help for assistance");
	}

	std::ifstream file(FilePath);
	std::string buffer;

	if (file.is_open() && !file.eof()) {
		while (std::getline(file, buffer))
			Parser::Commands.push_back(buffer);

		file.close();
	}
	else
		return ;

}

Parser &Parser::operator=(Parser const &ref)
{
	if (this != &ref){
		Parser::FilePath = ref.FilePath;
		Parser::Commands = ref.Commands;
	}
	return *this;
}

std::string &Parser::GetFilePath() {
	return this->FilePath;
}

Parser::Parser(){}

Parser::~Parser()
{
	Parser::Commands.clear();
}