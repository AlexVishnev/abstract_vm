#include "Parser.hpp"

bool Parser::is_filestream(const int mode){
	if (mode != 2)
		PRINT_RED("\nInfo: no file detect using stdin");
	return (mode == 2);
}


void Parser::_read(const int mode, const char **cfg_file)
{
	if (is_filestream(mode))
		file_path = cfg_file[1];
	
	PRINT_GREEN(file_path);

	std::ifstream file(file_path);
	std::string buffer;

	if (file.is_open() && !file.eof()) {
		while (std::getline(file, buffer))
		{
			if (buffer[0] != ';')
				comands.push_back(buffer);

		}
		file.close();
	}
	else {
		while (std::getline(std::cin, buffer)){
			comands.push_back(buffer);
			if (buffer == ";;" || buffer == "exit")
				break ;
		}
	}

	PRINT_GREEN("TEST WHAT WRITED INTO LIST\n");
	for (std::string i : comands)
		std::cout << i << std::endl;
}

Parser &Parser::operator=(Parser const &ref)
{
	if (this != &ref){
		file_path = ref.file_path;
		comands = ref.comands;
	}
	return *this;
}
Parser::Parser(){

}

Parser::~Parser()
{
	std::cout << "BY BY FROM " << __func__ << std::endl;
}