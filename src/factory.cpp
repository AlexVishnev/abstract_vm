#include "Factory.hpp"

Factory::Factory(){}
Factory::~Factory(){}

Factory &Factory::operator = (Factory const &ref)
{
	if (this != &ref) {

	}
	return *this;
}

IOperand const *Factory::createInt8  (std::string const &value ) const
{
	try {
		int64_t number = std::stoll(value);
		return (new eOperand<int8_t>(static_cast<int8_t>(number)));
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	

}

IOperand const *Factory::createInt16(std::string const &value ) const
{
	try {
		int64_t number = std::stoll(value);
		return (new eOperand<int16_t>(static_cast<int16_t>(number)));
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	

}

IOperand const *Factory::createInt32(std::string const &value ) const
{
	try {
		int64_t number = std::stoll(value);
		return (new eOperand<int32_t>(static_cast<int32_t>(number)));
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	

}

IOperand const *Factory::createFloat(std::string const &value ) const
{
	try {
		int64_t number = std::stoll(value);
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	

}

IOperand const *Factory::createDouble(std::string const &value ) const
{
	try {
		int64_t number = std::stoll(value);
		return (new eOperand<Double>(static_cast<int16_t>(number)));
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
}