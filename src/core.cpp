#include "Core.hpp"
#include "Exceptions.hpp"

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
	_get_elements_from_stack();
	if (first != nullptr && second != nullptr) {

		rezult = *first ^ *second;

		_stack.push_back(rezult);
		delete first;
		delete second;
	}
}

void	Core::_mod()
{
	_get_elements_from_stack();
	
	if (first != nullptr && second != nullptr) {

		// 	throw OverflowException("\033[0;31mError: Overflow rezult after operation ->ADD\033[0m");
		if (second->toString() == "0" || second->toString() == "0.0")
			throw DivByZeroException("\033[0;31mError: Trying to Modulo by zero\033[0m");
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
		// if (overflow_check(first, second, '+'))
		// 	throw OverflowException("\033[0;31mError: Overflow rezult after operation ->ADD\033[0m");
		try {
			rezult = *first + *second;
		}
		catch (std::exception &e){
			PRINT_RED(e.what())
		}

		_stack.push_back(rezult);
		delete first;
		delete second;
	}
}

bool	Core::overflow_check(IOperand const *first, IOperand const *second, int8_t _operator)
{
	eOperandType otype[2];

	if (_operator == '+') {
		otype[0] = first->getType();
		otype[1] = second->getType();
		if (otype[0] == Int32){

		}
	
	}
	else if (_operator == '-') {
		
	}
	else if (_operator == '*') {
		
	}
	else if (_operator == '/') {
		
	}
	else if (_operator == '^') {
		
	}	
	return false;
}


void	Core::_mult()
{
	_get_elements_from_stack();

	if (first != nullptr && second != nullptr) {

		rezult = *first * *second;
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}

void	Core::_div()
{
	_get_elements_from_stack();

	if (first != nullptr && second != nullptr) {

		if (second->toString() == "0" || second->toString() == "0.0")
			throw DivByZeroException("\033[0;31mError: Trying to Divide by zero\033[0m");
		rezult = *first / *second;
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
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

void Core::_get_elements_from_stack()
{
	if (_stack.empty())
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");
	if (_stack.size() < 2)
		throw EmptyStackException("\033[0;31mError: Trying to ADD with empty stack\033[0m");

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