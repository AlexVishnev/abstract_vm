#include "Core.hpp"
#include "Exeptions.hpp"

void	Core::_exec()
{
	try
	{
		_add();
		_pop();
		_sub();
		_mult();
		_div();
		_pow();
		_mod();
		_dump();
	}
	catch (EmptyStackException &e) {
		std::cerr << e.what() << std::endl;
	}
}
void	Core::_pow()
{
	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");

}

void	Core::_mod()
{

	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
}

void	Core::_add()
{

	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
}


void	Core::_mult()
{

	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
}

void	Core::_div()
{

	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
}

void	Core::_sub()
{
	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
}
void	Core::_pop()
{
	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to POP with empty stack\033[0m");
	else
		_stack.pop_back();


}

void	Core::_push(std::string	const &type, std::string const &value)
{
	eOperandType	op_type = end;

	if (type == "int8")
		op_type = Int8;
	else if (type == "int16")
		op_type = Int16;
	else if (type == "int32")
		op_type = Int32;
	else if (type == "float")
		op_type = Float;
	else if (type == "double")
		op_type = Double;
	else
		std::cerr << "wrong type" << std::endl;
	
	if (op_type != end)
		_stack.push_back(Factory().createOperand(op_type, value));
}

void	Core::__initd(const int mode, const char **cmd)
{
	std::cout << "Daemon started" << std::endl;

	parser._read(mode, cmd );
	//Parse file
	//Lexer analys
	//start exec Core
	_exec();

}

void Core::_dump()
{

	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");

	for (auto i = _stack.end(); i != _stack.begin(); --i)
	{
		if (*i != nullptr)
			PRINT_GREEN((*i)->toString());
	}
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
	}
	return (*this);
}


Core::Core ()
{
	draw_logo();
	fill_default_commands();
}

void Core::fill_default_commands()
{
	std::string	cmds[] = {  "pop", "dump", "add", "sub", "mul", 
							"div", "mod", "print", "pow", "exit"};
	for (auto var: cmds)
		_cmd_default.push_back(var);

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