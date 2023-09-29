/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:22:46 by nwyseur           #+#    #+#             */
/*   Updated: 2023/09/29 17:09:13 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

RPN::RPN(char* IPE)
{
	this->_IPE = std::string(IPE);

	try
	{
		parsing();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	try
	{
		calculation();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}

void	RPN::parsing(void)
{
	for (int i = 0; _IPE[i]; i++)
	{
		if ((_IPE[i] < '0' || _IPE[i] > '9') 
			&& _IPE[i] != '+' && _IPE[i] != '-' 
			&& _IPE[i] != '/' && _IPE[i] != '*' && _IPE[i] != ' ')
			throw invalidFormatException("Error : input is not a valide RPN");
	}
	int j = 0;
	while (_IPE[j] == ' ')
		j++;
	if (_IPE[j] < '0' || _IPE[j] > '9')
		throw invalidFormatException("Error : input is not a valide RPN (should start with a number)");
}

void	RPN::calculation(void)
{
	for (int i = 0; _IPE[i]; i++)
	{
		if (_IPE[i] >= '0' && _IPE[i] <= '9')
			_pile.push(atoi(&_IPE[i]));
		if (_IPE[i] == '+' || _IPE[i] == '-' || _IPE[i] == '/' || _IPE[i] == '*')
			operation(_IPE[i]);
	}
	if (_pile.size() != 1)
		throw invalidFormatException("Error : remaning value in stack");
	else
		std::cout << _pile.top() << std::endl;
}

int getIndex(char c)
{
	int i = 0;
	char array[4] = {'+', '-', '/', '*'};
	while (i != 3)
	{
		if (array[i] == c)	
			return (i);
		i++;
	}
	return (i);
}

void RPN::plus(void)
{
	int i;
	int j;
	
	if (_pile.size() < 2)
		throw invalidFormatException("Error: not enough value in stack to perform the operation (+)");
	i = _pile.top();
	_pile.pop();
	j = _pile.top();
	_pile.pop();
	_pile.push(j + i);
}

void RPN::moins(void)
{
	int i;
	int j;
	
	if (_pile.size() < 2)
		throw invalidFormatException("Error: not enough value in stack to perform the operation (-)");
	i = _pile.top();
	_pile.pop();
	j = _pile.top();
	_pile.pop();
	_pile.push(j - i);
}

void RPN::diviser(void)
{
	int i;
	int j;
	
	if (_pile.size() < 2)
		throw invalidFormatException("Error: not enough value in stack to perform the operation (/)");
	i = _pile.top();
	_pile.pop();
	j = _pile.top();
	_pile.pop();
	if (i == 0)
		throw invalidFormatException("Error: invalid division by 0");
	_pile.push(j / i);
}

void RPN::fois(void)
{
	int i;
	int j;
	
	if (_pile.size() < 2)
		throw invalidFormatException("Error: not enough value in stack to perform the operation (*)");
	i = _pile.top();
	_pile.pop();
	j = _pile.top();
	_pile.pop();
	_pile.push(i * j);
}

void RPN::operation(char c)
{
	void (RPN::*functionArray[4])(void) = {&RPN::plus, &RPN::moins, &RPN::diviser, &RPN::fois};
	int i = getIndex(c);
	
	(this->*(functionArray[i]))(); // La prochaine fois je ferai un switch case ce sera moins chiant
}