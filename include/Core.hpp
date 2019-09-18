#ifndef CORE_HPP
# define CORE_HPP

#include "Parser.hpp"
#include "Factory.hpp"
#include "Cmds.hpp"
#include "Lexer.hpp"


class Core
{
public:
	Core ();
	~Core();
	void	__initd(const int mode, const char **cmd);

protected:
	Factory			factory;
	Parser			parser;
	Lexer			lexer;
	
	std::list <t_cmds>				CommandQueue;
	std::list <std::string> 		_cmd_default;
	std::vector <IOperand const *>	_stack;
	
	void	PushValue(t_cmds comadnds);
	void	AssertValue(t_cmds comadnds);
	void	GetElementsFromStack();
	void	_Pop();
	void	_Add();
	void	_Sub();
	void	_Div();
	void	_Mul();
	void	_Mod();
	void	_Dump();
	void	_Pow();
	void	_Print();
	void	_Clear();
	void	_Exit();
	void	PrintStackSize();
	void	SortStack();
	void	Equal();

private:
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*rezult;

	void	Exec();
	void	DrawLogo();
	void	RunLiveMode();
	void	DeleteEmptyData(std::list<std::string> &Data);
	void	Usage();

	Core(Core const &ref);
	Core &operator=(const Core &ref);
};

#endif