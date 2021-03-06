#include "Core.hpp"
#include "Exceptions.hpp"

std::string getType(eOperandType type)
{
	switch (type)
	{
		case Int8: return "int8";
		case Int16: return "int16";
		case Int32: return "int32";
		case Float: return "float";
		case Double: return "double";
		default: return "";
	}

}

void Core::PrintStackSize()
{
	try {
		std::string color = _stack.size() == 0 ? RED : GREEN;
		std::cout << YELLOW "stack_size: " NO_COLOR + color << _stack.size() << NO_COLOR << std::endl;
	}
	catch (const std::exception &e) {
		PRINT_ERROR(e.what());
	}
}
void Core::DeleteEmptyData(std::list<std::string> &Data)
{
	Data.erase(std::remove_if(Data.begin(), Data.end(), [](std::string elem){
		return elem.empty();
	}), Data.end());
}

void	Core::Usage()
{
	PRINT_WARNING("Description\n"\
	"  Commands:\n\t- pop: Unstacks the value from the top of the stack\n"\
	"\t- dump: Displays each value of the stack, from the most recent one to the oldest one \n"\
	"\t- add: Unstacks the first two values on the stack, adds them together and stacks the result.\n"\
	"\t- div: Unstacks the first two values on the stack, subtracts them, then stacks the result.\n" \
	"\t- mul: Unstacks the first two values on the stack, multiplies them, then stacks the result. \n "\
	);
	PRINT_ERROR("Abstract VM by avishnev [version 1.9]");
}

void	Core::RunLiveMode()
{
	std::string buffer;

	while (std::getline(std::cin, buffer))
	{
		DeleteEmptyData(*parser.GetCommandsList());

		if (buffer == ";;" || buffer == "q" || buffer == "quit" || buffer == "exit")
			break ;
		if (buffer == "-h" || buffer == "--help")
			Usage();
		else
			parser.GetCommandsList()->push_back(buffer);

		try {
			lexer.StartTokenizing(parser, parser.GetCommandsList(), &CommandQueue, true);
		}
		catch (LexerException &e) {
			std::cerr << e.what() << std::endl;
		}
		CommandQueue.erase(CommandQueue.begin(), --CommandQueue.end()); // Need for executetion one last
		Exec();															// Command given from stdin
	}
	parser.GetCommandsList()->clear();
	_stack.clear();

}

void	Core::__initd(const int mode, const char **cmd)
{
	parser.Read(mode, cmd);

	if (!parser.isFilestream(mode)) {
		RunLiveMode();
	}
	 else {
		try {
			lexer.StartTokenizing(parser, parser.GetCommandsList(), &CommandQueue, false);
		}
		catch (LexerException &e) {
			std::cerr << e.what() << std::endl;
		}
		Exec();
	}
}

void	Core::Exec()
{
	try 
	{
		for (auto cmd : CommandQueue)
		{
			switch (cmd.type)
			{
				case Push: PushValue(cmd); break;
				case Assert: AssertValue(cmd); break;
				case Dump: _Dump(); break;
				case Print: _Print(); break;
				case Clear: _Clear(); break;
				case Pop: _Pop(); break;
				case Add: _Add(); break;
				case Sub: _Sub(); break;
				case Mul: _Mul(); break;
				case Div: _Div(); break;
				case Mod: _Mod(); break;
				case Pow: _Pow(); break;
				case Exit: _Exit();
				case Size: PrintStackSize(); break;
				case Sort: SortStack(); break;
				default:
					std::cout << "CHAGE THIS MESSAGE" << std::endl;
			}
		}
	}
	catch (EmptyStackException &e)  { PRINT_ERROR(e.what()); }
	catch (OverflowException &e)    { PRINT_ERROR(e.what()); }
	catch (UnderflowException &e)   { PRINT_ERROR(e.what()); }
	catch (DivByZeroException &e)   { PRINT_ERROR(e.what()); }
	catch (LexerException &e)       { PRINT_ERROR(e.what()); }
	catch (NullPointerException &e) { PRINT_ERROR(e.what()); }
	catch (BadLimitException &e)    { PRINT_ERROR(e.what()); }
	catch (std::exception &e)       { PRINT_ERROR(e.what()); }
	CommandQueue.clear();
}

void	Core::_Exit()
{ 
	if (_stack.size() != 0)
		_stack.clear();
	exit(0);
}

void	Core::_Clear()
{
	_stack.clear();
}

void	Core::_Pow()
{
	GetElementsFromStack();
	if (first != nullptr && second != nullptr) {
		rezult = *first ^ *second;
	
		if (rezult == nullptr) {
			delete first;
			delete second;
			throw OverflowException("Calculation Error: ", "^");
		}
		_stack.push_back(rezult);
		delete first;
		delete second;
	}
}

void	Core::SortStack()
{
	if (_stack.empty()) {
		PRINT_WARNING("Stack is empty");
		return ;
	}

	for (size_t i = 0; i < _stack.size(); i++)
	{
		for (size_t j = 0; j < _stack.size(); j++)
		{
			if (std::stold((_stack[i])->toString()) > std::stold((_stack[j])->toString())){
				const IOperand *tmp = _stack[i];
				_stack[i] = _stack[j];
				_stack[j] = tmp;
				j = 0;
			}
		}
	}
	_stack.shrink_to_fit();
}

void	Core::_Mod()
{
	GetElementsFromStack();
	
	if (first != nullptr && second != nullptr) {

		rezult = *first % *second;
		if (rezult == nullptr) {
			throw NullPointerException(RED "Calculation error: can`t modulo" NO_COLOR);
			delete first;
			delete second;
		}
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}

void	Core::_Add()
{
	GetElementsFromStack();
	
	if (first != nullptr && second != nullptr) {

		rezult = *first + *second;
		if (rezult == nullptr){
			delete first;
			delete second;

			throw OverflowException("Calculation Error: ", "+");
		}
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}


void	Core::_Mul()
{
	GetElementsFromStack();

	if (first != nullptr && second != nullptr) {

		rezult = *first * *second;
		if (rezult == nullptr){
			delete first;
			delete second;
			throw OverflowException("Calculation Error: ", "*");
		}

		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}

void	Core::AssertValue(t_cmds cmd)
{
	if (_stack.empty())
		throw EmptyStackException(RED"Runtime error:\033[0m Trying to ASSERT on empty stack");

	const IOperand *v1 = _stack.back();

	const IOperand *v2 = Factory().createOperand(cmd.oper_type, cmd.strValue);

	if (v2 == nullptr) {
		throw BadLimitException(cmd.strValue, getType(cmd.oper_type));
		delete v1;
	}

	if (v1->getType() != v2->getType()) {
		delete v2;
		throw EmptyStackException(RED"Asserting error:\033[0m types not equal");
	}

	if (std::stod(v1->toString()) != std::stod(v2->toString())) {
		PRINT_WARNING(YELLOW "AVM (#_assert): " NO_COLOR RED "FALSE");
	}
	else
		PRINT_GREEN(YELLOW "AVM (#_assert): " NO_COLOR GREEN "TRUE");

	delete v2;
}


void	Core::_Div()
{
	GetElementsFromStack();

	if (first != nullptr && second != nullptr) {

		rezult = *first / *second;
		if (rezult == nullptr){
			delete first;
			delete second;
			throw NullPointerException(RED "Calculation error: can`t divide" NO_COLOR);
		}
		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}

void	Core::_Print()
{
	if (_stack.empty())
		throw EmptyStackException(RED"Print Error:\033[0m There is nothing to print\n");
	const IOperand *v1 = _stack.back();

	if (v1->getType() != Int8)
		throw EmptyStackException(RED"Print Error:\033[0m trying to print non char variable");

	std::cout << YELLOW "AVM (#Print):" NO_COLOR << static_cast<char>(std::stoi(v1->toString())) << std::endl;
}

void	Core::_Sub()
{
	GetElementsFromStack();
	
	if (first != nullptr && second != nullptr) {

		rezult = *first - *second;
		if (rezult == nullptr) {
			delete first;
			delete second;

			throw UnderflowException("Calculation Error: ", "-");
		}

		_stack.push_back(rezult);

		delete first;
		delete second;
	}
}
void	Core::_Pop()
{
	if (_stack.empty())
		throw EmptyStackException(YELLOW"Warning:\033[0m Trying to POP with empty stack");
	else
		_stack.pop_back();
}

void	Core::PushValue(t_cmds	cmd)
{
	const IOperand *Operand = Factory().createOperand(cmd.oper_type, cmd.strValue);
	if (Operand == nullptr)
		throw BadLimitException(cmd.strValue, getType(cmd.oper_type));
	_stack.push_back(Operand);
}


void Core::_Dump()
{
	if (_stack.empty())
		throw EmptyStackException(YELLOW"Warning:\033[0m there is nothing to dump\n");

	int16_t counter = _stack.size();
	std::cout << std::endl;

	for (auto i = _stack.end(); i != _stack.begin(); )
	{
		--i;
		if (*i != nullptr && !(*i)->toString().empty())
			std::cout << YELLOW "AVM (#Dump): " NO_COLOR RED "stack[" << --counter 
			<< "] " NO_COLOR << (*i)->toString() << std::endl;

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

void Core::GetElementsFromStack()
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

Core::Core() 
{
	first = nullptr;
	second = nullptr;
	rezult = nullptr;
	DrawLogo();

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
		PRINT_ERROR(line);
		usleep(65000);
	}
	logo.clear();
}

Core::~Core()
{
	if (first) delete first;
	if (second) delete second;
	if (rezult) delete rezult;

	if (_stack.size())
		_stack.clear();
	CommandQueue.clear();
	_cmd_default.clear();

}

