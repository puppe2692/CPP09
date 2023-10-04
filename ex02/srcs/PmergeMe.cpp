/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:41:39 by nwyseur           #+#    #+#             */
/*   Updated: 2023/10/04 18:10:10 by nwyseur          ###   ########.fr       */
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
	//printvect(0);
	//mergevect();
	std::cout << "///////////////" << std::endl;
	printlist(0);
	mergelist();

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
	for(unsigned long j = 0; j < _vectS.size(); j++)
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

void PmergeMe::mergevect(void)
{
	int len = _vectS.size();
	int *tmp = NULL;
	for (int i = 0; i < len - 1; i += 2)
	{
		if (_vectS[i] >= _vectS[i + 1])
			_vectP.push_back(std::make_pair(_vectS[i], _vectS[i + 1]));
		else
			_vectP.push_back(std::make_pair(_vectS[i + 1], _vectS[i]));
	}
	if (len % 2 == 1)
	{
		tmp = &_vectS[len - 1];
	}
	sortvectP();
	for (unsigned long j = 0; j < _vectP.size(); j++)
	{
		std::cout << "Vect: " << j << " - first: " << _vectP[j].first << std::endl;
		std::cout << "Vect: " <<  j << " - second: " << _vectP[j].second << std::endl;
		std::cout << '\n';
	}
	if (len % 2 == 1)
	{
		std::cout << "Vect - on top: " << *tmp << std::endl;
	}
	insertvect(tmp);
	for(unsigned long j = 0; j < _vectS.size(); j++)
		std::cout << ' ' << this->_vectS[j];
	std::cout << '\n';
}

void PmergeMe::sortvectP(void)
{
	for (std::vector<std::pair<int, int> > ::iterator it = _vectP.begin() + 1; it < _vectP.end(); it++)
	{
		std::vector<std::pair<int, int> > ::iterator act = it;
		std::vector<std::pair<int, int> > ::iterator prev = it - 1;

		while ((*act).first < (*prev).first)
		{
			std::swap(*act, *prev);
			if (prev != _vectP.begin())
			{
				act = prev;
				prev = act - 1;
			}
		}
	}
}

void PmergeMe::insertvect(int* tmp)
{
	int valtmp;

	if (tmp != NULL)
	{
		valtmp = *tmp;
	}

	_vectS.clear();	
	for (std::vector<std::pair<int, int> >::iterator it = _vectP.begin(); it < _vectP.end(); it++)
	{
			_vectS.push_back((*it).first);
	}

	for (std::vector<std::pair<int, int> >::iterator it = _vectP.begin(); it < _vectP.end(); it++)
	{
		std::vector<int>::iterator sortit = std::lower_bound(_vectS.begin(), _vectS.end(), (*it).second);
		_vectS.insert(sortit, (*it).second);
	}

	if (tmp != NULL)
	{
		std::vector<int>::iterator ittmp = std::lower_bound(_vectS.begin(), _vectS.end(), valtmp);
		_vectS.insert(ittmp, valtmp);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void PmergeMe::mergelist(void)
{
	int len = _listS.size();
	int *tmp = NULL;


	for(std::list<int>::iterator it = _listS.begin(); it != getPrev(_listS.end()); getdbnext(it)) // ici ca va pas
	{
		if ((*it) >= (*getNext(it)))
			_listP.push_back(std::make_pair((*it), (*getNext(it))));
		else
			_listP.push_back(std::make_pair((*getNext(it)), (*it)));
	}

	for (unsigned long j = 0; j < _listP.size(); j++)
	{
		std::list<std::pair<int,int> >::iterator it = _listP.begin();
		std::advance(it, j);
		std::cout << "List: " << j << " - first: " << (*it).first << std::endl;
		std::cout << "List: " << j << " - second: " << (*it).second << std::endl;
		std::cout << '\n';
	}
	
	if (len % 2 == 1)
	{
		std::list<int>::iterator it = getPrev(_listS.end());
		tmp = &(*it);
	}
	sortlistP();
	for (unsigned long j = 0; j < _listP.size(); j++)
	{
		std::list<std::pair<int,int> >::iterator it = _listP.begin();
		std::advance(it, j);
		std::cout << "Sort List: " << j << " - first: " << (*it).first << std::endl;
		std::cout << "Sort List: " << j << " - second: " << (*it).second << std::endl;
		std::cout << '\n';
	}
	if (len % 2 == 1)
	{
		std::cout << "List - on top: " << *tmp << std::endl;
	}
	insertlist(tmp);
	for(unsigned long j = 0; j < _listS.size(); j++)
	{
		std::list<int>::iterator it = _listS.begin();
		std::advance(it, j);
		std::cout << ' ' << (*it);
	}
	std::cout << '\n';
}

void PmergeMe::sortlistP(void)
{
	for (std::list<std::pair<int, int> > ::iterator it = getNext(_listP.begin()); it != _listP.end(); it++)
	{
		std::list<std::pair<int, int> > ::iterator act = it;
		std::list<std::pair<int, int> > ::iterator prev = getPrev(it);

		while ((*act).first < (*prev).first)
		{
			std::swap(*act, *prev);
			if (prev != _listP.begin())
			{
				act = prev;
				prev = getPrev(act);
			}
		}
	}
}

void PmergeMe::insertlist(int* tmp)
{
	int valtmp;

	if (tmp != NULL)
	{
		valtmp = *tmp;
	}

	_listS.clear();	
	for (std::list<std::pair<int, int> >::iterator it = _listP.begin(); it != _listP.end(); it++)
	{
			_listS.push_back((*it).first);
	}

	for (std::list<std::pair<int, int> >::iterator it = _listP.begin(); it != _listP.end(); it++)
	{
		std::list<int>::iterator sortit = std::lower_bound(_listS.begin(), _listS.end(), (*it).second);
		_listS.insert(sortit, (*it).second);
	}

	if (tmp != NULL)
	{
		std::list<int>::iterator ittmp = std::lower_bound(_listS.begin(), _listS.end(), valtmp);
		_listS.insert(ittmp, valtmp);
	}
}

template<typename T>
T PmergeMe::getPrev(T it) 
{
	T tmp = it;

    --tmp;
    return tmp;
}

template<typename T>
T PmergeMe::getNext(T it) 
{
	T tmp = it;

    ++tmp;
    return tmp;
}

template<typename T>
T PmergeMe::getdbnext(T it) 
{
	T tmp = it;

    ++tmp;
	++tmp;
    return tmp;
}