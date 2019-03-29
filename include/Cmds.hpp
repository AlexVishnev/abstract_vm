#ifndef CMDS_HPP
# define CMDS_HPP
#include "Operand.hpp"

enum cmd_type
{
	Push,
	Pop,
	Dump,
	Print,
	Exit,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Pow,
	Clear,
};

typedef struct s_cmds
{
	cmd_type		type;
	eOperandType	oper_type;
	std::string		strValue;
	long double		value;

}				t_cmds;


#endif