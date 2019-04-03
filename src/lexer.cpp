#include "Lexer.hpp"

void	Lexer::run_lexer(Parser  &parser, std::list <std::string> *commands, std::list <t_cmds> *cmd_quene)
{

	parser.is_filestream(2);

	New_command(cmd_quene, Int32, "32", 3);
	std::array <std::regex, 2> reg;
	reg[0] = "((\\s)+)?(pop|add|sub|mul|div|mod|pow|clear|print|exit)((\\s)+)?(;(.+)?)?";
	reg[1] = "((\\s)+)?(push|assert)((\\s)+)?"
				"(int8|int16|int32|float|double)((\\s)+)?"
				"\\(((\\s)+)?"
				"(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s)+)?"
				"\\)((\\s)+)?"
				"(;(.+)?)?";
	
	std::smatch base_mach;
	std::smatch piece;

	for (auto var : *commands){

		for (size_t i = 0; i < reg.size(); ++i)
		{
			// if (std::regex_match(var, base_mach ,std::regex(reg[i])))
				// std::cout << "base_match: " << base_mach.str() << std::endl;
			
			if (std::regex_match(var, piece ,std::regex(reg[i]))){
				for (size_t j = 0; j < piece.size(); ++j)
				{
					std::ssub_match sub_match = piece[j];
					std::string piece = sub_match.str();
						if (piece != "")
							std::cout << "piece.size() : " << piece.size() << "\n\t\tpiece_match: " << j << ": " << piece << std::endl;
				}
				std::cout << var << std::endl;
			}
		}
//todo THINK ABOUT HOW TO GET SEARCH REZUT AND SUBSEARCH AND TRANSFORM INTO OPER TYPES
	}
}

void	Lexer::New_command(std::list <t_cmds> *cmd_quene, eOperandType o_type, std::string value, int c_type)
{

	t_cmds cmd;

	if (c_type > 1) {
		cmd.type = static_cast<cmd_type>(c_type);
		cmd.oper_type = o_type;
		cmd.strValue = value;
		cmd_quene->push_back(cmd);
	}
	else
	{
		cmd.type = static_cast<cmd_type>(c_type);
		cmd_quene->push_back(cmd); 
	}
	

}


Lexer::Lexer(/* args */)
{

}

Lexer::~Lexer()
{
	std::cout << "BY BY FROM " << __func__ << std::endl;
}