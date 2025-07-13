#pragma once
#include <stdexcept>
#include <stdio.h>
class MyException : public std::exception {
public:
	MyException(const std::string exceptionMsg) :
		message(exceptionMsg)
	{

	}
	const char* what() const throw() {
		return message.c_str();
	}
	const void printMsg() const throw()
	{
		if (!message.empty())
		{
			printf("%s\n", message.c_str());
		}
	}
private:
	std::string message;
};