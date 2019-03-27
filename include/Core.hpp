#ifndef CORE_HPP
# define CORE_HPP

#include "Enums.hpp"
#include "Parser.hpp"
#include "Factory.hpp"
#include <string>
#include <iostream>
#include <list>
#include <unistd.h>



class Core
{
public:
	Core ();
	~Core();
	Core &operator=(const Core &ref);
	Core(Core const &ref);

	void	_push(std::string const &type, std::string const &value);
	void	_assert(std::string const &type, std::string const &value);
	void	_get_elements_from_stack();
	void	_pop();
	void	_add();
	void	_sub();
	void	_div();
	void	_mult();
	void	_mod();
	void	_dump();
	void	_pow();
	void	__initd(const int mode, const char **cmd);

protected:
	Factory			factory;
	Parser			parser;

	bool	overflow_check(IOperand const *first, IOperand const *second, int8_t _operator);
	std::list <std::string> 		_cmd_default;
	std::list <IOperand const *>	_stack;
private:
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*rezult;
	void			_exec();
	void			draw_logo();
	void			fill_default_commands();


};





#endif