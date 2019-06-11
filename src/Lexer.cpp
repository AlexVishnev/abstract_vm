#include "Lexer.hpp"


void Lexer::StartTokenizing(Parser &parser, std::list<std::string> *commands, std::list<t_cmds> *CmdQueue)
{
	std::array<std::regex, 2> reg;
	std::smatch base_mach;
	std::smatch piece;

	reg[0] = "((\\s)+)?(pop|add|sub|mul|div|mod|pow|clear|print|dump|exit)((\\s)+)?(;(.+)?)?";
	reg[1] = "((\\s)+)?(push|assert)((\\s)+)?"
			 "(int8|int16|int32|float|double)((\\s)+)?"
			 "\\(((\\s)+)?"
			 "(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s)+)?"
			 "\\)((\\s)+)?"
			 "(;(.+)?)?";

	if (!CheckForExitCommand(commands))
		throw LexerException(RED"Lexer error:\033[0m no exit command");

	for (auto &Command : *commands)
	{
		std::cout << "commands == [" <<  Command << "]"<< std::endl; 
		for (size_t i = 0; i < reg.size(); ++i)
		{
			if (std::regex_match(Command, piece, std::regex(reg[i]))) {
				for (size_t j = 0; j < piece.size(); ++j)
				{
					std::ssub_match sub_match = piece[j];
					std::string piece = sub_match.str();
				}
				if (!i && !Command.empty()){
					CreateNewCommand(CmdQueue, "one_pararmetr", Command);
					Command.clear();
				}
				else if (i && !Command.empty()){
					CreateNewCommand(CmdQueue, "several_params", Command);
					Command.clear();
				}
			}
		}

	}

	AnalyseCommandQueue(commands, parser.GetFilePath());
}

enum cmd_type Lexer::TransformValueToCmdtype(std::string &ValueType)
{
	//type depends on variable position if DefValues[]; 
	std::string DefValues[] = {"pop", "dump", "print",
							   "add", "sub", "mul",
							   "div", "mod", "pow",
							   "clear", "exit", "push", "assert"};


	for (size_t i = 0; i < sizeof(DefValues) / sizeof(DefValues[0]); i++)
	{
		if (ValueType == DefValues[i])
			return static_cast<cmd_type>(i);
	}
	return static_cast<cmd_type>(13);
}
enum eOperandType Lexer::TransformValueToOtype(std::string &ValueType)
{
	ValueType.erase(0, ValueType.find("push") == std::string::npos ? 7 : 5);
	std::string	tmp = ValueType.substr(0, ValueType.find('('));

	std::string DefValues[] = {"int8", "int16", "int32",
							   "float", "double"};

	for (size_t i = 0; i < sizeof(DefValues) / sizeof(DefValues[0]); i++)
	{
		if (tmp == DefValues[i])
			return static_cast<eOperandType>(i);
	}
	return static_cast<eOperandType>(5);
}

void Lexer::CreateNewCommand(std::list<t_cmds> *CmdQueue,
						std::string condition, std::string &c_type)
{
	if (CmdQueue == nullptr || c_type.empty() || condition.empty())
		return ;
	t_cmds cmd;

	if (condition == "several_params")
	{
		std::string tmp = c_type.find("push") == std::string::npos ? "assert": "push";
		cmd.type = TransformValueToCmdtype(tmp);
		cmd.oper_type = TransformValueToOtype(c_type);

		cmd.strValue = c_type.substr(c_type.find('(') + 1, c_type.find(')') - 2);
		cmd.strValue.pop_back();
		CmdQueue->push_back(cmd);
	}
	else
	{
		cmd.type = TransformValueToCmdtype(c_type);
		cmd.strValue = "0";
		cmd.oper_type = End;
		CmdQueue->push_back(cmd);

	}
}

void Lexer::AnalyseCommandQueue(std::list <std::string> *CommandsQueue, std::string FilePath)
{
	int16_t line = 1;

	for (auto &Command: *CommandsQueue)
	{
		if (!Command.empty() && Command[0] != ';' && Command.find_first_not_of(' ') != std::string::npos){
			std::cerr << FilePath <<":" << line << ":\033[0;31m" << " lexer error:" << "\033[0m" << " Unrecognized command  " << "\'" 
				<< Command  << "\'" << std::endl;
		}
		line++;
	}
}

bool Lexer::CheckForExitCommand(std::list <std::string> *CommandQueue)
{
	int exitAmounts = 0; 

	for (auto &Cmd: *CommandQueue)
	{
		if (Cmd == "exit" || Cmd == ";;")
			exitAmounts++;
	}

	return exitAmounts == 1;
}

Lexer::Lexer(){

}

Lexer::~Lexer(){

}
