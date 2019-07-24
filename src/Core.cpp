#include "Core.hpp"
#include "Exceptions.hpp"

void Core::DeleteEmptyData(std::list<std::string> &Data)
{
	// std::list<std::string>::iterator it = Data.begin();
	
	// Data.unique();
	Data.erase(std::remove_if(Data.begin(), Data.end(), [](std::string elem){
		return elem.empty();
	}), Data.end());
}

void	Core::RunLiveMode()
{
	std::string buffer;

	while (std::getline(std::cin, buffer))
	{
		// parser.GetCommandsList()->unique();
		DeleteEmptyData(*parser.GetCommandsList());

		if (buffer == ";;" || buffer == "q" || buffer == "quit" || buffer == "exit")
			break ;
		parser.GetCommandsList()->push_back(buffer);

		try {
			lexer.StartTokenizing(parser, parser.GetCommandsList(), &CommandQueue, true);
		}
		catch (LexerException &e) {
			std::cerr << e.what() << std::endl;
		}
		_exec();
	}

}

void	Core::__initd(const int mode, const char **cmd)
{
	parser._read(mode, cmd);

	if (!parser.is_filestream(mode)) {
		RunLiveMode();
	}
	 else {
		try {
			lexer.StartTokenizing(parser, parser.GetCommandsList(), &CommandQueue, false);
		}
		catch(LexerException &e) {
			std::cerr << e.what() << std::endl;
		}
		_exec();
	}
}

void	Core::_exec()
{
	try 
	{
		for (auto cmd : CommandQueue)
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
						_exit();
				default:
						std::cout << "CHAGE THIS MESSAGE" << std::endl;
			}
		}
	}
	catch (EmptyStackException &e) {
		PRINT_ERROR(e.what());
	}
	catch (OverflowException &e) {
		PRINT_ERROR(e.what());
	}
	catch (UnderflowException &e) {
		PRINT_ERROR(e.what());
	}
	catch (DivByZeroException &e) {
		PRINT_ERROR(e.what());
	}
	catch (LexerException &e){
		PRINT_ERROR(e.what());
	}
	catch (NullPointerException &e) {
		PRINT_ERROR(e.what());
	}
	//ADD cathcers
}

void	Core::_exit(){
	exit(0);
}

void	Core::_clear() {
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
		throw EmptyStackException(RED"Runtime error:\033[0m Trying to ASSERT on empty stack");

	const IOperand *v1 = _stack.back();

	const IOperand *v2 = Factory().createOperand(cmd.oper_type, cmd.strValue);

	if (v1->getType() != v2->getType()) {
		delete v1;
		delete v2;
		throw EmptyStackException(RED"Asserting error:\033[0m asserting types not equal");
	}

	if (std::stod(v1->toString()) != std::stod(v2->toString())) {
		PRINT_WARNING("ASSERT FALSE");
	}
	else
		PRINT_GREEN("ASSERT TRUE");

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
		throw EmptyStackException(RED"Error:\033[0m There is nothing ot print\n");
	const IOperand *v1 = _stack.back();

	if (v1->getType() != Int8)
		throw EmptyStackException(RED"Error:\033[0m tying to print non char variable");

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
		throw EmptyStackException(RED"Runtime error:\033[0m Trying to POP with empty stack");
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
		throw EmptyStackException(RED"Runtime error:\033[0m there is nothing to dump\n"); //change to yellow clr

	for (auto i = _stack.end(); i != _stack.begin(); )
	{
		--i;
		if (*i != nullptr && !(*i)->toString().empty())
		PRINT_GREEN((*i)->toString());
	}
}

Core::Core(Core const &ref) {
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
		throw EmptyStackException(RED"Runtime error:\033[0m empty stack\n");
	if (_stack.size() < 2)
		throw EmptyStackException(RED"Runtime error:\033[0m not enought elements on stack for operation\n");
	first =_stack.back();
	_stack.pop_back();
	second = _stack.back();;
	_stack.pop_back();
}

Core::Core() {
	DrawLogo();
	FillDefaultCommands();
}

void Core::FillDefaultCommands()
{
	std::string	cmds[] = {  "pop", "dump", "print", "add", 
							"sub", "mul", "div", "mod" , "pow",
							"exit", "clear", "push", "assert"
							};
	for (auto var: cmds)
		_cmd_default.push_back(var);

}

void Core::DrawLogo()
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

Core::~Core(){ }