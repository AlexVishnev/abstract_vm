#ifndef CMDS_HPP
#define CMDS_HPP
#include "Operand.hpp"

enum cmd_type
{
	Pop,
	Dump,
	Print,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Pow,
	Clear,
	Exit,
	Push,
	Assert,
	endlist,
};

typedef struct s_cmds
{
	cmd_type type;
	eOperandType oper_type;
	std::string strValue;

} t_cmds;

#endif