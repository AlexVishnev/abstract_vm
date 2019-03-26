#ifndef EXEPTIONS_HPP 
# define EXEPTIONS_HPP

#include <exception>
#include <string>

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

class	DivisionByZeroException : std::exception
{

public:
	explicit DivisionByZeroException(const std::string &message): msg(message){}
	virtual const char *what() const throw() override {
		return "Division by zero";
	}
private:
	std::string	msg;
};


#endif
