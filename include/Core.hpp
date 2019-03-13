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
	Core &operator=(const Core &ref);
	Core(Core const &ref);
	~Core();

	void	_push(std::string const &value, eOperandType type);
	void	_assert(std::string const &value, eOperandType type);
	void	_get_elements_from_stack();
	void	_pop();
	void	_add();
	void	_sub();
	void	_div();
	void	_mult();
	void	_mod();
	void	_dump();
	void	__initd(const int mode, const char **cmd);


private:
	Factory			factory;
	Parser			parser;

	std::list <std::string> 	 __cmd; //container with what?
	std::list <IOperand const *> __stack;

	void	draw_logo();
};





#endif