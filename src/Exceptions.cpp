#include "Exceptions.hpp"

UnderflowException::UnderflowException(const std::string &message): std::out_of_range(message), msg(message){

}

OverflowException::OverflowException(const std::string &message): std::out_of_range(message), msg(message){

}

EmptyStackException::EmptyStackException(const std::string &message): msg(message) {

}

DivByZeroException::DivByZeroException(const std::string &message): msg(message){

}

LexerException::LexerException(const std::string &message): msg(message){

}
const char *EmptyStackException::what() const throw() {
	return msg.c_str();
}

const char *UnderflowException::what() const throw() {
	return msg.c_str();
}
const char *DivByZeroException::what() const throw() {
	return msg.c_str();
}

const char *LexerException::what() const throw() {
	return msg.c_str();
}

const char *OverflowException::what() const throw() {
	return msg.c_str();
}

UnderflowException::~UnderflowException(){ }
OverflowException::~OverflowException(){ }
EmptyStackException::~EmptyStackException(){ }
DivByZeroException::~DivByZeroException(){ }
LexerException::~LexerException(){ }



//TODO WRITE EXCEPTIONS