#ifndef EXEPTIONS_HPP 
# define EXEPTIONS_HPP

#include <exception>
#include <string>
#include <limits>

class EmptyStackException: std::exception
{
public:
	explicit EmptyStackException(const std::string &message): msg(message){}
	virtual	const char *what() const throw() override {
		return msg.c_str();
	}
private:
	std::string msg;
};


class	OverflowException: std::overflow_error 
{
public:
	explicit OverflowException(const std::string &message): overflow_error(message), msg(message) {}
	virtual const char *what() const throw() override {
		return (msg.c_str());
	}

private:
	std::string		msg;
};

class	UnderflowException: std::underflow_error 
{
public:
	explicit UnderflowException(const std::string &message): underflow_error(message), msg(message) {}
	virtual const char *what() const throw() override {
		return (msg.c_str());
	}

private:
	std::string		msg;
};

class	DivByZeroException : std::exception
{

public:
	explicit DivByZeroException(const std::string &message): msg(message){}
	virtual const char *what() const throw() override {
		return msg.c_str();
	}
private:
	std::string	msg;
};


#endif
