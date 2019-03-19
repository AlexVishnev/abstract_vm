#include "Operand.hpp"

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


template <class T> std::string const &Operand<T>::toString() const {
	return (_buffer);
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
		return (end);
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

	if (type < Float)
		rezult_operation = std::to_string(static_cast<int64_t>(this->_value) + std::stoll(ref.toString()));
	else
		rezult_operation = std::to_string(static_cast<long double>(this->_value) + std::stold(ref.toString()));

	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator - (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	if (type < Float)
		rezult_operation = std::to_string(static_cast<int64_t>(this->_value) - std::stoll(ref.toString()));
	else
		rezult_operation = std::to_string(static_cast<long double>(this->_value) - std::stold(ref.toString()));


	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator * (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	if (type < Float)
		rezult_operation = std::to_string(static_cast<int64_t>(this->_value) * std::stoll(ref.toString()));
	else
		rezult_operation = std::to_string(static_cast<long double>(this->_value) * std::stold(ref.toString()));


	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator / (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	if (type < Float)
		rezult_operation = std::to_string(static_cast<int64_t>(this->_value) / std::stoll(ref.toString()));
	else
		rezult_operation = std::to_string(static_cast<long double>(this->_value) / std::stold(ref.toString()));

	return (Factory().createOperand(type, rezult_operation));

}

template <class T> IOperand const *Operand<T>::operator % (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	if (type < Float)
		rezult_operation = std::to_string(static_cast<int64_t>(this->_value) % std::stoll(ref.toString()));
	else
		rezult_operation = std::to_string(fmod(static_cast<long double>(this->_value),  std::stold(ref.toString())));

	return (Factory().createOperand(type, rezult_operation));

}


template <class T> IOperand const *Operand<T>::operator ^ (IOperand const &ref) const
{
	eOperandType	type;
	std::string 	rezult_operation;


	type = this->getType() >= ref.getType() ? this->getType() : ref.getType();

	if (type < Float)
		rezult_operation = std::to_string(pow(static_cast<int64_t>(this->_value), std::stoll(ref.toString())));
	else
		rezult_operation = std::to_string(pow(static_cast<long double>(this->_value), std::stold(ref.toString())));

	return (Factory().createOperand(type, rezult_operation));

}



template <class T> Operand<T>::Operand(){ /*-_-*/}

template <class T> Operand<T>::Operand(Operand const &ref)
{
	*this = ref;
}

template <class T> Operand<T>::~Operand(){ /*-_-*/ }


template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;