// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<RPN.cpp>>

#include "RPN.hpp"
#include <iostream>

#define _isop(x)	(x == '+' || x == '-' || x == '*' || x == '/')
#define _isint(x)	(x >= '0' && x <= '9')

RPN::RPN(void) {}

RPN::~RPN(void) {}

// misc

void	RPN::solve(std::stringstream &expr)
{
	uint64_t	n1;
	uint64_t	n2;
	std::string	tmp;

	std::getline(expr, tmp, ' ');
	if (tmp.empty() || !_isint(tmp.at(0)))
		throw RPN::InvalidExpressionException();
	this->_stack.push(std::stoi(tmp));
	while (!expr.eof()) {
		std::getline(expr, tmp, ' ');
		if (tmp.empty())
			break ;
		if (_isint(tmp.at(0)))
			this->_stack.push(std::stoi(tmp));
		else if (_isop(tmp.at(0)) && this->_stack.size() >= 2) switch (tmp.at(0)) {
			case '+':
				n1 = this->_stack.top();
				this->_stack.pop();
				n2 = this->_stack.top();
				this->_stack.pop();
				this->_stack.push(n2 + n1);
				break ;
			case '-':
				n1 = this->_stack.top();
				this->_stack.pop();
				n2 = this->_stack.top();
				this->_stack.pop();
				this->_stack.push(n2 - n1);
				break ;
			case '*':
				n1 = this->_stack.top();
				this->_stack.pop();
				n2 = this->_stack.top();
				this->_stack.pop();
				this->_stack.push(n2 * n1);
				break ;
			case '/':
				n1 = this->_stack.top();
				if (n1 == 0)
					throw RPN::InvalidExpressionException();
				this->_stack.pop();
				n2 = this->_stack.top();
				this->_stack.pop();
				this->_stack.push(n2 / n1);
				break ;
		} else
			throw RPN::InvalidExpressionException();
	}
	if (this->_stack.size() != 1)
		throw RPN::InvalidExpressionException();
	std::cout << this->_stack.top() << "\n";
}

// exception

const char	*RPN::InvalidExpressionException::what(void) const noexcept
{
	return "Invalid expression";
}
