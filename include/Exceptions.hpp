#ifndef EXEPTIONS_HPP 
# define EXEPTIONS_HPP

#include <exception>
#include <string>
#include <limits>
#include <iostream>

class EmptyStackException : public std::exception
{
public:
	explicit EmptyStackException(const std::string &message);
	virtual	const char *what() const throw() override;
	virtual ~EmptyStackException();
private:
	std::string msg;
};

class BadLimitException : public std::out_of_range
{
public:
	explicit BadLimitException(const std::string &message, std::string type);
	virtual	const char *what() const throw() override;
	virtual ~BadLimitException();
private:
	std::string msg;
};


class	OverflowException : public std::out_of_range
{
public:
	explicit OverflowException(const std::string &message, std::string oper);
	virtual const char *what() const throw() override;
	virtual ~OverflowException();
private:
	std::string		msg;
};

class	UnderflowException : public std::out_of_range 
{
public:
	explicit UnderflowException(const std::string &message, std::string oper);
	virtual const char *what() const throw() override;
	virtual ~UnderflowException();
private:
	std::string		msg;
};

class	DivByZeroException : public std::exception
{
public:
	explicit DivByZeroException(const std::string &message);
	virtual const char *what() const throw() override;
	virtual ~DivByZeroException();
private:
	std::string	msg;
};

class	LexerException : public std::exception
{
public:
	explicit LexerException(const std::string &message);
	virtual const char *what() const throw() override;
	virtual ~LexerException();
private:
	std::string	msg;
};

class NullPointerException: public std::exception 
{
public:
	explicit NullPointerException(const std::string &message);
	virtual const char *what() const throw() override;
	virtual ~NullPointerException();
private:
	std::string	msg;
};

class CustomException: public std::exception 
{
public:
	explicit CustomException(const std::string &message);
	virtual const char *what() const throw() override;
	virtual ~CustomException();
private:
	std::string	msg;
};

#endif
