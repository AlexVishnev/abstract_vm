#include "Lexer.hpp"


void Lexer::StartTokenizing(Parser &parser, std::list<std::string> *Commands, std::list<t_cmds> *CmdQueue, bool istream)
{
	std::array<std::regex, 2> pattern;
	std::smatch base_mach, piece;
	bool HasExit = true, HasOneParam = true;

	pattern[0] = "((\\s)+)?(pop|add|sub|mul|div|mod|pow|clear|print|dump|exit|size|sort)((\\s)+)?(;(.+)?)?";
	pattern[1] = "((\\s)+)?(push|assert)((\\s)+)?"
			 "(int8|int16|int32|float|double)((\\s)+)?"
			 "\\(((\\s)+)?"
			 "(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s)+)?"
			 "\\)((\\s)+)?"
			 "(;(.+)?)?";

	this->istream = istream;

	if (!istream)
		HasExit = CheckForExitCommand(Commands);

	for (std::string &Command : *Commands)
	{
		for (size_t i = 0; i < pattern.size(); ++i)
		{
			if (std::regex_match(Command, piece, std::regex(pattern[i]))) {
				for (size_t j = 0; j < piece.size(); ++j)
				{
					std::ssub_match sub_match = piece[j];
					std::string piece = sub_match.str();
				}
				try 
				{
					if (!i && !Command.empty()){
						if (HasExit)
							CmdQueue->push_back(CreateNewCommand(!HasOneParam, Command));
						Command.clear();
					}
					else if (i && !Command.empty()){
						if (HasExit)
							CmdQueue->push_back(CreateNewCommand(HasOneParam, Command));
						Command.clear();
					}
				}
				catch (NullPointerException &e) {
					PRINT_ERROR(e.what());
				}
			}
		}
	}
	AnalyseCommandQueue(Commands, parser.GetFilePath());
	if (!HasExit)
		throw LexerException(RED"lexer error:\033[0m no exit command");
}

enum cmd_type Lexer::TransformValueToCmdtype(std::string &ValueType)
{
	//type depends on variable position if DefValues[];
	std::string DefValues[] = {
		"pop", "dump", "print", "add", "sub", "mul",
		"div", "mod", "pow", "clear", "exit", "push", 
		"assert", "size", "sort"
	};

	std::list<std::pair<std::string, int>> expr;

	int i = 0;
	for (std::string var: DefValues)
		expr.push_back(std::make_pair(var, i++));

	for (auto var: expr) 
	{
		if (ValueType == var.first || ValueType.substr(0, 3) == var.first ||
			ValueType.substr(0, 4) == var.first || ValueType.substr(0, 5) == var.first)
			return static_cast<cmd_type>(var.second);
	}
	expr.clear();
	return static_cast<cmd_type>(15);
}

enum eOperandType Lexer::TransformValueToOtype(std::string &ValueType)
{
	ValueType.erase(0, ValueType.find("push") == std::string::npos ? 7 : 5);
	std::string	tmp = ValueType.substr(0, ValueType.find('('));

	std::string DefValues[] = {
		"int8", "int16", "int32", "float", "double"
	};

	for (size_t i = 0; i < sizeof(DefValues) / sizeof(DefValues[0]); i++)
	{
		if (tmp == DefValues[i])
			return static_cast<eOperandType>(i);
	}
	return static_cast<eOperandType>(5);
}

t_cmds Lexer::CreateNewCommand(bool HasTwoParams, std::string &c_type)
{
	t_cmds cmd;
	
	if (c_type.empty())
		throw NullPointerException("Error: cat`t create command");

	if (HasTwoParams) {
		std::string tmp = c_type.find("push") == std::string::npos ? "assert" : "push";
		cmd.type = TransformValueToCmdtype(tmp);
		cmd.oper_type = TransformValueToOtype(c_type);

		cmd.strValue = c_type.substr(c_type.find('(') + 1, c_type.find(')') - 2);
		cmd.strValue.pop_back();
	
	}
	else {
		cmd.type = TransformValueToCmdtype(c_type);
		cmd.strValue = "0";
		cmd.oper_type = End;
	}
	return cmd;
}

void Lexer::AnalyseCommandQueue(std::list <std::string> *CommandsQueue, std::string FilePath)
{
	int16_t line = 1;
	if (CommandsQueue == nullptr)
		throw NullPointerException("CommandQueue in AnalyseCommandQueue()");

	for (std::string &Command: *CommandsQueue)
	{
		if (!Command.empty() && Command[0] != ';' && Command.find_first_not_of(' ') != std::string::npos){

			if (this->istream){
				std::cerr << FilePath << ":\033[0;31m" << " lexer error:" << "\033[0m" << " Unrecognized command  " << "\'" 
				<< Command  << "\'" << std::endl;
				Command.clear();
			}
			else
				std::cerr << FilePath <<":" << line << ":\033[0;31m" << " lexer error:" << "\033[0m" << " Unrecognized command  " << "\'" 
				<< Command  << "\'" << std::endl;
		}
		line++;
	}
}

bool Lexer::CheckForExitCommand(std::list <std::string> *CommandQueue)
{
	int16_t exitAmounts = 0; 
	if (CommandQueue == nullptr)
		throw NullPointerException("CommandQueue");

	for (std::string &Cmd: *CommandQueue)
	{
		if (Cmd == "exit" || Cmd == ";;")
			exitAmounts++;
	}

	return exitAmounts > 0;
}

Lexer::Lexer(){}
Lexer::~Lexer(){}
