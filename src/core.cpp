#include "Core.hpp"


void	Core::__initd(const int mode, const char **cmd)
{
	std::cout << "Daemon started" << std::endl;

	parser._read(mode, cmd );
	//Parse file
	//Lexer analys
	//start exec Core

}

void Core::_get_elements_from_stack()
{
	
}


Core::Core(Core const &ref)
{
	*this = ref;
}

Core &Core::operator=(Core const &ref)
{
	if (this != &ref) {
		factory = ref.factory;
		parser = ref.parser;
		std::cout << "DONE YOU WORK PIDOR" << std::endl;
	}
	return (*this);
}


Core::Core ()
{
	draw_logo();
}

void Core::draw_logo()
{
	std::list <std::string> logo;

	logo.push_back(" ▄▄▄       ▄▄▄▄     ██████ ▄▄▄█████▓ ██▀███   ▄▄▄       ▄████▄  ▄▄▄█████▓    ██▒   █▓ ███▄ ▄███▓");
	logo.push_back("▒████▄    ▓█████▄ ▒██    ▒ ▓  ██▒ ▓▒▓██ ▒ ██▒▒████▄    ▒██▀ ▀█  ▓  ██▒ ▓▒   ▓██░   █▒▓██▒▀█▀ ██▒");
	logo.push_back("▒██  ▀█▄  ▒██▒ ▄██░ ▓██▄   ▒ ▓██░ ▒░▓██ ░▄█ ▒▒██  ▀█▄  ▒▓█    ▄ ▒ ▓██░ ▒░    ▓██  █▒░▓██    ▓██░");
	logo.push_back("░██▄▄▄▄██ ▒██░█▀    ▒   ██▒░ ▓██▓ ░ ▒██▀▀█▄  ░██▄▄▄▄██ ▒▓▓▄ ▄██▒░ ▓██▓ ░      ▒██ █░░▒██    ▒██ ");
	logo.push_back(" ▓█   ▓██▒░▓█  ▀█▓▒██████▒▒  ▒██▒ ░ ░██▓ ▒██▒ ▓█   ▓██▒▒ ▓███▀ ░  ▒██▒ ░       ▒▀█░  ▒██▒   ░██▒");
	logo.push_back(" ▒▒   ▓▒█░░▒▓███▀▒▒ ▒▓▒ ▒ ░  ▒ ░░   ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░░ ░▒ ▒  ░  ▒ ░░         ░ ▐░  ░ ▒░   ░  ░");
	logo.push_back("  ▒   ▒▒ ░▒░▒   ░ ░ ░▒  ░ ░    ░      ░▒ ░ ▒░  ▒   ▒▒ ░  ░  ▒       ░          ░ ░░  ░  ░      ░");
	logo.push_back("  ░   ▒    ░    ░ ░  ░  ░    ░        ░░   ░   ░   ▒   ░          ░              ░░  ░      ░   ");
	logo.push_back("      ░  ░ ░            ░              ░           ░  ░░ ░                        ░         ░   ");
	logo.push_back("                ░                                      ░                         ░              ");

	system("clear");

	for (std::string line : logo)
	{
		PRINT_GREEN(line);
		usleep(65000);
	}
	logo.clear();
}

Core::~Core()
{
	std::cout << "by by from  " << __func__ << std::endl;
}