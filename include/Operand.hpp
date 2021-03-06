#ifndef EOPERAND_HPP
# define EOPERAND_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include "Exceptions.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <typeinfo>

template <typename T>
class Operand: public IOperand
{
protected:
	T			_value;
	std::string	_buffer;
public:
	Operand(T value);
	~Operand();
	Operand();
	Operand(Operand const &ref);

	IOperand const &operator =(Operand const &ref); 

	int					getPrecision() const;
	eOperandType		getType() const;
	IOperand const		*operator + (IOperand const &rhs) const;
	IOperand const		*operator - (IOperand const &rhs) const;
	IOperand const		*operator * (IOperand const &rhs) const;
	IOperand const		*operator / (IOperand const &rhs) const;
	IOperand const		*operator % (IOperand const &rhs) const;
	IOperand const		*operator ^ (IOperand const &rhs) const;

	// bool				operator == (IOperand const &rhs) const;
	// bool				operator >  (IOperand const &rhs) const;
	// bool				operator <  (IOperand const &rhs) const;
	// bool				operator >= (IOperand const &rhs) const;
	// bool				operator <= (IOperand const &rhs) const;
	// bool				operator != (IOperand const &rhs) const;

	void				operations_check(T first, T second, char _operator) const;
	std::string const	&toString() const;

};

#endif