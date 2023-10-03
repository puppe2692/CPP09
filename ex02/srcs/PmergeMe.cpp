/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:41:39 by nwyseur           #+#    #+#             */
/*   Updated: 2023/10/03 18:23:41 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(char** str)
{
	std::cout << GREEN << "Constructor call" << RESET << std::endl;
	try
	{
		parsing(str);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	sequencing(str);
	printvect(0);
	printlist(0);

	
}

PmergeMe::~PmergeMe()
{
	std::cout << RED << "Destructor call" << RESET << std::endl;
	return;
}

void	PmergeMe::parsing(char** str)
{
	for(int i = 1; str[i]; i++)
	{
		if (strlen(str[i]) >= 10 && strcmp(str[i], "2147483647") > 0)
			throw invalidFormatException("Error: the sequence must only content positive int");
		for(int j = 0; str[i][j]; j++)
		{
			if (str[i][j] == '+')
				throw invalidFormatException("Error: are you trying to fool me?");
			if (str[i][j] < '0' || str[i][j] > '9')
				throw invalidFormatException("Error: the sequence must only content positive int");
		}	
	}
}

void	PmergeMe::sequencing(char** str)
{
	for (int i = 1; str[i]; i++)
	{
		this->_vectS.push_back(std::atoi(str[i]));
		this->_listS.push_back(std::atoi(str[i]));
	}
}

void PmergeMe::printvect(int i)
{
	if (i == 0)
		std::cout << "Before V:";
	if (i == 1)
		std::cout << "After V:";
	for(int j = 0; this->_vectS[j]; j++)
		std::cout << ' ' << this->_vectS[j];
	std::cout << '\n';
}

void PmergeMe::printlist(int i) // effacer
{
	std::list<int>::iterator	it = _listS.begin();
	std::list<int>::iterator	ite = _listS.end();
	if (i == 0)
		std::cout << "Before L:";
	if (i == 1)
		std::cout << "After L:";
	while (it != ite)
	{
		std::cout << ' ' << *it;
		it++;
	}
	std::cout << '\n';
}

template<typename T>
void swap(T& a, T&b)
{
	T tmp;

	tmp = a;
	a = b;
	b = tmp;
	return;
}


void PmergeMe::mergevect(void)
{
	int len = _vectS.size();
	for (int i = 0; i < len; i += 2)
	{
		_vectP.push_back(std::make_pair(_vectS[i], _vectS[i + 1]));
	}
}