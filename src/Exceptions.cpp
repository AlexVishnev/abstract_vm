#include "Exceptions.hpp"
#include "defines.hpp"

BadLimitException::BadLimitException(const std::string &value, std::string type): std::out_of_range(value){
	msg = RED "Limit Error: " NO_COLOR "trying intialize type:[" + type + "] with value:[" + value +"]\n";
}

UnderflowException::UnderflowException(const std::string &message, std::string type): std::out_of_range(message), msg(message){
	msg = RED + message + NO_COLOR "underflow after " + type + " operation\n";
}

OverflowException::OverflowException(const std::string &message, std::string type): std::out_of_range(message), msg(message){
	msg = RED + message + NO_COLOR "overflow after " + type + " operation\n";
}

EmptyStackException::EmptyStackException(const std::string &message): msg(message) {}
DivByZeroException::DivByZeroException(const std::string &message): msg(message){}
LexerException::LexerException(const std::string &message): msg(message){}
CustomException::CustomException(const std::string &message): msg(message){}
NullPointerException::NullPointerException(const std::string &message): msg(message){}

const char *EmptyStackException::what() const throw() { return msg.c_str(); }
const char *CustomException::what() const throw() { return msg.c_str(); }
const char *BadLimitException::what() const throw() { return msg.c_str(); }
const char *UnderflowException::what() const throw() { return msg.c_str(); }
const char *DivByZeroException::what() const throw() { return msg.c_str(); }
const char *NullPointerException::what() const throw() { return msg.c_str(); }
const char *LexerException::what() const throw() { return msg.c_str(); }
const char *OverflowException::what() const throw() { return msg.c_str(); }

BadLimitException::~BadLimitException(){ }
UnderflowException::~UnderflowException(){ }
OverflowException::~OverflowException(){ }
EmptyStackException::~EmptyStackException(){ }
DivByZeroException::~DivByZeroException(){ }
LexerException::~LexerException(){ }
NullPointerException::~NullPointerException(){ }
CustomException::~CustomException(){ }
