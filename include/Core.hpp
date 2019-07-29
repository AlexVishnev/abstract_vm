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
	std::list <IOperand const *>	_stack;
	
	void	_push(t_cmds comadnds);
	void	_assert(t_cmds comadnds);
	void	_get_elements_from_stack();
	void	_pop();
	void	_add();
	void	_sub();
	void	_div();
	void	_mul();
	void	_mod();
	void	_dump();
	void	_pow();
	void	_print();
	void	_clear();
	void	_exit();
	void	_printStackSize();
	void	_sortStack();
	void	_equal();

private:
	
	void	_exec();
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*rezult;
	

	void	DrawLogo();
	void	FillDefaultCommands();
	void	RunLiveMode();
	void	DeleteEmptyData(std::list<std::string> &Data);

	Core(Core const &ref);
	Core &operator=(const Core &ref);

};





#endif