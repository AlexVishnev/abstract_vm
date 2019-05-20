#include "Lexer.hpp"


void Lexer::run_lexer(Parser &parser, std::list<std::string> *commands, std::list<t_cmds> *cmd_quene)
{
	parser.is_filestream(2);

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
				if (!i && !Command.empty())
					New_command(cmd_quene, "one_pararmetr", Command);
				else if (i && !Command.empty())
					New_command(cmd_quene, "several_params", Command);
			}
			// else
			// {
				// PRINT_RED("ERROR: BLYAD");
			// }
			
		}
		//todo THINK ABOUT HOW TO GET SEARCH REZUT AND SUBSEARCH AND TRANSFORM INTO OPER TYPES
	}
}

enum cmd_type Lexer::TransformValueToCmdtype(std::string &ValueType)
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
enum eOperandType Lexer::TransformValueToOtype(std::string &ValueType)
{
	std::cout << std::endl << "\n\nbefore earase val ==" <<ValueType << std::endl;
	ValueType.erase(0, ValueType.find("push") == std::string::npos ? 7 : 5);
	std::cout << std::endl << "\n\nafter earase val ==" <<ValueType << std::endl;
	std::string	tmp = ValueType.substr(0, ValueType.find('('));
	std::cout << "T M P\n\n\n" << tmp << std::endl;
	std::string DefValues[] = {"int8", "int16", "int32",
							   "float", "double"};

	for (size_t i = 0; i < sizeof(DefValues) / sizeof(DefValues[0]); ++i)
	{
		if (tmp == DefValues[i])
			return static_cast<eOperandType>(i);
	}
	return static_cast<eOperandType>(6);
}

void Lexer::New_command(std::list<t_cmds> *cmd_quene,
						std::string condition, std::string &c_type)
{
	if (cmd_quene == nullptr || c_type.empty() || condition.empty())
		return ;
	t_cmds cmd;

	if (condition == "several_params")
	{
		std::string tmp = c_type.find("push") == std::string::npos ? "push" : "assert";
		cmd.type = TransformValueToCmdtype(tmp);
		cmd.oper_type = TransformValueToOtype(c_type);
		
		std::cout << __func__ <<  " if condition " << " :"<< c_type << std::endl;
		cmd.strValue = condition;
		cmd_quene->push_back(cmd);
	}
	else
	{
		std::cout << "else condition " << __func__ << " "<<  c_type << std::endl;
		cmd.type = TransformValueToCmdtype(c_type);
		cmd_quene->push_back(cmd);
	}
}

Lexer::Lexer(/* args */) { std::cout << "HELLO FROM " << __func__ << std::endl; }

Lexer::~Lexer()
{
	std::cout << "BY BY FROM " << __func__ << std::endl;
}