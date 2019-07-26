#include "Factory.hpp"

IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const
{
	return ((*this.*CoreQueue.at(type))(value));
}

IOperand const *Factory::createInt8(std::string const &value) const
{
	try
	{
		int64_t number = std::stoll(value);
		if (number < INT8_MIN || number > INT8_MAX)
			return (nullptr);
		return (new Operand<int8_t>(static_cast<int8_t>(number)));
	}
	catch (const std::bad_cast &e)
	{
		std::cerr << e.what() << std::endl;
		return (nullptr);
	}
}

IOperand const *Factory::createInt16(std::string const &value) const
{
	try
	{
		int64_t number = std::stoll(value);
		if (number < INT16_MIN || number > INT16_MAX)
			return (nullptr);
		return (new Operand<int16_t>(static_cast<int16_t>(number)));
	}
	catch (const std::bad_cast &e)
	{
		std::cerr << e.what() << std::endl;
		return (nullptr);
	}
}

IOperand const *Factory::createInt32(std::string const &value) const
{
	try
	{
		int64_t number = std::stoll(value);
		if (number < INT32_MIN || number > INT32_MAX)
			return (nullptr);
		return (new Operand<int32_t>(static_cast<int32_t>(number)));
	}
	catch (const std::bad_cast &e)
	{
		std::cerr << e.what() << std::endl;
		return (0);
	}
}

IOperand const *Factory::createFloat(std::string const &value) const
{
	try
	{
		int64_t number = std::stoll(value);
		return (new Operand<float>(static_cast<float>(number)));
	}
	catch (const std::bad_cast &e)
	{
		std::cerr << e.what() << std::endl;
		return (0);
	}
}

IOperand const *Factory::createDouble(std::string const &value) const
{
	try
	{
		int64_t number = std::stoll(value);
		return (new Operand<double>(static_cast<double>(number)));
	}
	catch (const std::bad_cast &e)
	{
		std::cerr << e.what() << std::endl;
		return (0);
	}
}

Factory &Factory::operator=(Factory const &ref)
{
	if (this != &ref)
		this->CoreQueue = ref.CoreQueue;
	return *this;
}

Factory::Factory()
{
	CoreQueue.push_back(&Factory::createInt8);
	CoreQueue.push_back(&Factory::createInt16);
	CoreQueue.push_back(&Factory::createInt32);
	CoreQueue.push_back(&Factory::createFloat);
	CoreQueue.push_back(&Factory::createDouble);
}
Factory::~Factory() {}