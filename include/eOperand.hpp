#ifndef EOPERAND_HPP
# define EOPERAND_HPP
#include "IOperand.hpp"

template <typename T>
class eOperand: public IOperand
{
private:
    T _data;
public:
    eOperand(T data);
    ~eOperand();
    eOperand();
    eOperand(eOperand const &ref);

    IOperand const &operator =(eOperand const &ref); 

	int					getPrecision() const = 0;
	eOperandType		getType() const = 0;
	IOperand const		*operator + (IOperand const &rhs) const = 0;
	IOperand const		*operator - (IOperand const &rhs) const = 0;
	IOperand const		*operator * (IOperand const &rhs) const = 0;
	IOperand const		*operator / (IOperand const &rhs) const = 0;
	IOperand const		*operator % (IOperand const &rhs) const = 0;
	IOperand const		*operator ^ (IOperand const &rhs) const = 0;

	bool				operator == (IOperand const &rhs) const = 0;
	bool				operator >  (IOperand const &rhs) const = 0;
	bool				operator <  (IOperand const &rhs) const = 0;
	bool				operator >= (IOperand const &rhs) const = 0;
	bool				operator <= (IOperand const &rhs) const = 0;
	bool				operator != (IOperand const &rhs) const = 0;
	std::string const	&toString() const = 0;




};

#endif