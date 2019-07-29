#include "Operand.hpp"
#include "defines.hpp"

template <class T>Operand<T>::Operand(T value): _value(value)
{

	if ((typeid(T) == typeid(int8_t)) || (typeid(T) == typeid(int16_t))
		|| (typeid(T) == typeid(int32_t)))
		_buffer = std::to_string(value);
	else if (typeid(T) == typeid(float)) {
		std::stringstream set(std::stringstream::out);
		set << std::setprecision(7) << value;
		_buffer = set.str();
	}
	else if (typeid(T) == typeid(double)) {
		std::stringstream set(std::stringstream::out);
		set << std::setprecision(14) << value;
		_buffer = set.str();
	}
}

//TODO WRITE CATHCERS
template <class T> void Operand<T>::operations_check(T first, T second, char _operator) const
{
	if (_operator == '+') {
		if (first > 0 && second > 0) {
			if ((first + second) < second)
				throw UnderflowException("Calculation error: ", "+"); 
		}
		else if (first < 0 && second < 0) {
			if (first < 0 && (first + second) > second)
				throw OverflowException("Calculation error: ", "+");
			else if ((first + second) < second)
				throw UnderflowException("Calculation error: ", "+");
		}
	}
	else if (_operator == '*')
	{
		if (std::abs(first) > std::numeric_limits<T>::max() / std::abs(second)) {
			if ((first > 0 && second > 0) || (first < 0 && second < 0))
				throw OverflowException("Calculation error: ", "*");
			else
				throw UnderflowException("Calculation error: ", "*");
			
		}
	}
	else if (_operator == '-') {

		if (first > 0 && second < 0){
			if ((std::numeric_limits<T>::max() / 2 < std::abs(first)) 
				&& (std::numeric_limits<T>::max() / 2 < std::abs(first)))
				throw OverflowException("Calculation error: ", "-");
		}
		else if (first < 0 && second > 0){
			if ((std::numeric_limits<T>::max() / 2 < std::abs(first)) 
				&& (std::numeric_limits<T>::max() / 2 < std::abs(first)))
				throw UnderflowException("Calculation error: ", "-");
		}
	}
	else if (_operator == '/') {
		if (second == 0)
			throw DivByZeroException(RED"Calculation error: \033[0m division by zero");
	}
	else if (_operator == '%') {
		if (second == 0)
			throw DivByZeroException (RED"Calculation error: \033[0m modulo by zero");
	}
	else if (_operator == '^') {
		if (second > 32)
			throw OverflowException("Calculation error: ", "pow");
	}
}

template <class T> std::string const &Operand<T>::toString() const {

	return (this->_buffer);
}

template <class T> int Operand<T>::getPrecision() const
{
	if (typeid(T) == typeid(float))
		return (7);
	else if (typeid(T) == typeid(double))
		return (14);
	else
		return (0);
	
}

template <class T> eOperandType Operand<T>::getType() const
{
	if (typeid(T) == typeid(int8_t))
		return(Int8);
	else if (typeid(T) == typeid(int16_t))
		return(Int16);
	else if (typeid(T) == typeid(int32_t))
		return(Int32);
	else if (typeid(T) == typeid(float))
		return (Float);
	else if (typeid(T) == typeid(double))
		return (Double);
	else
		return (End);
}

template <class T> IOperand const &Operand<T>::operator = (Operand const &ref)
{
	if (this != &ref) {
		_buffer = ref._buffer;
		_value = ref._value;
	}
	return (*this);

}

template <class T> IOperand const *Operand<T>::operator + (IOperand const &ref) const
{
	eOperandType	type;
	std::string		rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	operations_check(_value, static_cast<T>(std::stod(ref.toString())), '+');

	rezult_operation = type < Float ? std::to_string(static_cast<int64_t>(this->_value) + std::stoll(ref.toString())) : 
									  std::to_string(static_cast<long double>(this->_value) + std::stold(ref.toString()));

	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator - (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	operations_check(_value, static_cast<T>(std::stod(ref.toString())), '-');

	rezult_operation = type < Float ? std::to_string(static_cast<int64_t>(this->_value) - std::stoll(ref.toString())) : 
									  std::to_string(static_cast<long double>(this->_value) - std::stold(ref.toString()));

	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator * (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	operations_check(_value, static_cast<T>(std::stod(ref.toString())), '*');

	rezult_operation = type < Float ? std::to_string(static_cast<int64_t>(this->_value) * std::stoll(ref.toString())) : 
									  std::to_string(static_cast<long double>(this->_value) * std::stold(ref.toString()));

	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator / (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	operations_check(_value, static_cast<T>(std::stod(ref.toString())), '/');

	rezult_operation = type < Float ? std::to_string(static_cast<int64_t>(this->_value) / std::stoll(ref.toString())) : 
									  std::to_string(static_cast<long double>(this->_value) / std::stold(ref.toString()));
	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator % (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	operations_check(_value, static_cast<T>(std::stod(ref.toString())), '%');
	rezult_operation = type < Float ? std::to_string(static_cast<int64_t>(this->_value) % std::stoll(ref.toString())) : 
									  std::to_string(fmod(static_cast<long double>(this->_value), std::stold(ref.toString())));

	return (Factory().createOperand(type, rezult_operation));

}


template <class T> IOperand const *Operand<T>::operator ^ (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();
	operations_check(_value, static_cast<T>(std::stod(ref.toString())), '^');
	if (type < Float)
		rezult_operation = std::to_string(pow(static_cast<int64_t>(this->_value), std::stoll(ref.toString())));
	else
		rezult_operation = std::to_string(pow(static_cast<long double>(this->_value), std::stold(ref.toString())));

	return (Factory().createOperand(type, rezult_operation));

}


template <class T> Operand<T>::Operand(Operand const &ref)
{
	*this = ref;
}

template <class T> Operand<T>::Operand(){ /*-_-*/}
template <class T> Operand<T>::~Operand(){/*	std::cout << "BY BY FROM " << __func__ << std::endl; */}


template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;