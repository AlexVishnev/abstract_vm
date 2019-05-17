#include "Lexer.hpp"

void Lexer::run_lexer(Parser &parser, std::list<std::string> *commands, std::list<t_cmds> *cmd_quene)
{
	parser.is_filestream(2);

	New_command(cmd_quene, Int32, "32", "push");
	std::array<std::regex, 2> reg;
	reg[0] = "((\\s)+)?(pop|add|sub|mul|div|mod|pow|clear|print|exit)((\\s)+)?(;(.+)?)?";
	reg[1] = "((\\s)+)?(push|assert)((\\s)+)?"
			 "(int8|int16|int32|float|double)((\\s)+)?"
			 "\\(((\\s)+)?"
			 "(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s)+)?"
			 "\\)((\\s)+)?"
			 "(;(.+)?)?";

	std::smatch base_mach;
	std::smatch piece;

	for (auto Command : *commands)
	{

		for (size_t i = 0; i < reg.size(); ++i)
		{
			if (std::regex_match(Command, piece, std::regex(reg[i])))
			{
				for (size_t j = 0; j < piece.size(); ++j)
				{
					std::ssub_match sub_match = piece[j];
					std::string piece = sub_match.str();
					// if (piece != "")
					// std::cout << "piece.size() : " << piece.size() << "\n\t\tpiece_match: " << j << ": " << piece << std::endl;
				}
				std::cout << "command == " << Command <<" i = "<<  i <<  std::endl;
				if (!i && !Command.empty())
					New_command(cmd_quene, static_cast<eOperandType>(0), "nullptr", Command);
				else if (i && !Command.empty())
					New_command(cmd_quene, static_cast<eOperandType>(0), "notnullptr", Command);
			
			}
		}
		//todo THINK ABOUT HOW TO GET SEARCH REZUT AND SUBSEARCH AND TRANSFORM INTO OPER TYPES
	}
}

enum cmd_type Lexer::TransformValueToCmdtype(std::string ValueType)
{

	std::string DefValues[] = {"pop", "dump", "print",
							   "add", "sub", "mul",
							   "div", "mod", "pow",
							   "clear", "exit", "push", "assert"};
	for (size_t i = 0; i < 10; ++i)
	{
		if (ValueType == DefValues[i])
			return static_cast<cmd_type>(i);
	}
	return static_cast<cmd_type>(13);
}

void Lexer::New_command(std::list<t_cmds> *cmd_quene, eOperandType o_type, std::string value, std::string c_type)
{
	t_cmds cmd;

	if (value == "nullptr")
	{
		cmd.type = TransformValueToCmdtype(c_type.find("push") == std::string::npos ? "push": "assert");
		cmd.oper_type = o_type;
		cmd.strValue = value;
		cmd_quene->push_back(cmd);
	}
	else
	{
		cmd.type = TransformValueToCmdtype(c_type);
		cmd_quene->push_back(cmd);
	}
}

Lexer::Lexer(/* args */) { std::cout << "HELLO FROM " << __func__ << std::endl; }

Lexer::~Lexer()
{
	std::cout << "BY BY FROM " << __func__ << std::endl;
}