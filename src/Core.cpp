#include "Core.hpp"
#include "Exceptions.hpp"
void	Core::__initd(const int mode, const char **cmd)
{
	parser._read(mode, cmd );
	lexer.run_lexer(parser, parser.get_list_commands(), &command_quene);
	//Parse file
	//Lexer analys
	//start exec Core
	_exec();

}
void	Core::_exec()
{
	for (auto cmd : command_quene)
	{
		std::cout <<"cmd.type == " <<  cmd.type <<"\ncmd.oper_type == "<< cmd.oper_type <<"\ncmd.str_value == "<< cmd.strValue << std::endl;
	}
	try 
	{
		for (auto cmd : command_quene)
		{
			switch (cmd.type)
			{
				case Push:
						_push(cmd);
						break;
				case Pop:
						_pop();
						break;
				case Dump:
						_dump();
						break;
				case Print:
						_print();
						break;
				case Assert:
						_assert(cmd);
						break;
				case Add:
						_add();
						break;
				case Sub:
						_sub();
						break;
				case Mul:
						_mul();
						break;
				case Div:
						_div();
						break;
				case Mod:
						_mod();
						break;
				case Pow:
						_pow();
						break;
				case Clear:
						_clear();
						break;
				case Exit:
						return ;
				default:
						std::cout << "LOOOl" << std::endl;
			}
		}
	}
	catch (EmptyStackException &e) {
		std::cerr << e.what() << std::endl;
	}
	catch (OverflowException &e) {
		std::cerr << e.what() << std::endl;
	}
	catch (UnderflowException &e) {
		std::cerr << e.what() << std::endl;
	}
	catch (DivByZeroException &e) {
		std::cerr << e.what() << std::endl;
	}
	//ADD cathcers
}


void	Core::_clear()
{
	_stack.clear();
}
void	Core::_pow()
{
	_get_elements_from_stack();
	if (first != nullptr && second != nullptr) {
//try
		rezult = *first ^ *second;
//catch
		_stack.push_back(rezult);
		delete first;
		delete second;
	}
}

void	Core::_mod()
{
	_get_elements_from_stack();
	
	if (first != nullptr && second != nullptr) {

		rezult = *first % *second;
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}

void	Core::_add()
{
	_get_elements_from_stack();
	
	if (first != nullptr && second != nullptr) {

		rezult = *first + *second;
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}



void	Core::_mul()
{
	_get_elements_from_stack();

	if (first != nullptr && second != nullptr) {

		rezult = *first * *second;
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}

void	Core::_assert(t_cmds cmd)
{
	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ASSERT with empty stack\033[0m");

	const IOperand *v1 = _stack.back();
	_stack.pop_back();

	const IOperand *v2 = Factory().createOperand(cmd.oper_type, cmd.strValue);

	if (v1->getType() != v2->getType()) {
		delete v1;
		delete v2;
		throw EmptyStackException("daun");
	}
	if (std::stod(v1->toString()) != std::stod(v2->toString())) {
		delete v1;
		delete v2;
		throw EmptyStackException("lol");
	}
	delete v1;
	delete v2;

}
void	Core::_div()
{
	_get_elements_from_stack();

	if (first != nullptr && second != nullptr) {

		rezult = *first / *second;
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}

void	Core::_print()
{
	if (_stack.empty())
		throw EmptyStackException("There is nothing ot print");
	const IOperand *v1 = _stack.back();

	if (v1->getType() != Int8)
		throw EmptyStackException("int8");

	std::cout << static_cast<char>(std::stoi(v1->toString())) << std::endl;
}

void	Core::_sub()
{
	_get_elements_from_stack();
	
	if (first != nullptr && second != nullptr) {

		rezult = *first - *second;
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}
void	Core::_pop()
{
	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to POP with empty stack\033[0m");
	else
		_stack.pop_back();


}

void	Core::_push(t_cmds	cmd)
{
	_stack.push_back(Factory().createOperand(cmd.oper_type, cmd.strValue));
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
		lexer = ref.lexer;
	}
	return (*this);
}

void Core::_get_elements_from_stack()
{
	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: empty stack\n\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: not enought elemetns for operation\n\033[0m");
	first =_stack.back();
	_stack.pop_back();
	second = _stack.back();;
	_stack.pop_back();
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