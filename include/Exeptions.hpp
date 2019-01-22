#ifndef EXEPTIONS_HPP 
# define EXEPTIONS_HPP

#include <exeption>





class   OverflowExeption: std::overflow_error 
{

public:
    explicit ParseExeption(const std::string &message): msg(message),overflow_error(message){}
    virtual const char *what() const throw() override
    {
        return (msg.c_str());
    }
    
private:
    std::string     msg;

};

class   DivisionByZeroException : std::exception
{

public:
	virtual const char *what() const throw() override
    {
		return "Division by zero";
	}

};


#endif
