#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Operand.hpp"
#include <vector>
#include "IOperand.hpp"

class Factory
{
public:
	Factory();
	~Factory();
	Factory &operator = (Factory const &ref);
	Factory(Factory const &ref);
	IOperand const *createOperand( eOperandType type, std::string const & value ) const;

private:
	IOperand const *createInt8  (std::string const & value ) const;
	IOperand const *createInt16 (std::string const & value ) const;
	IOperand const *createInt32 (std::string const & value ) const;
	IOperand const *createFloat (std::string const & value ) const;
	IOperand const *createDouble(std::string const & value ) const;


	std::vector <IOperand const *(Factory::*)(std::string const &value) const > CoreQueue;

};





#endif