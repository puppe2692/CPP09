/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:41:39 by nwyseur           #+#    #+#             */
/*   Updated: 2023/10/05 12:21:28 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(char** str)
{
	std::cout << GREEN << "Constructor call" << RESET << std::endl;
	try
	{
		parsing(str);
		sequencing(str);
		mergevect();
		mergelist();
		printAll();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

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

void	PmergeMe::printAll(void)
{
	printvect(0);
	printvect(1);
	std::cout << "Time to process a range of " << _vectS.size() << " elements with std::vector : " << _timeVect << "ms" << std::endl;
	std::cout << "Time to process a range of " << _listS.size() << " elements with std::list : " << _timeList << "ms" << std::endl;

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
	{
		std::cout << "Before: ";
		for(unsigned long j = 0; j < _vectS.size(); j++)
		{
			std::cout << ' ' << this->_vectS[j];
			if (j > 10)
			{
				std::cout << " [...] ";
				break;
			}
		}
	}
	if (i == 1)
	{
		std::cout << "After: ";
		for(unsigned long j = 0; j < _vectSort.size(); j++)
		{
			std::cout << ' ' << this->_vectSort[j];
			if (j > 10)
			{
				std::cout << " [...] ";
				break;
			}
		}
	}
	std::cout << '\n';
}

void PmergeMe::mergevect(void)
{
	clock_t start = clock();
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
	insertvect(tmp);
	clock_t end = clock();
	_timeVect = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.00;
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

	for (std::vector<std::pair<int, int> >::iterator it = _vectP.begin(); it < _vectP.end(); it++)
	{
			_vectSort.push_back((*it).first);
	}

	for (std::vector<std::pair<int, int> >::iterator it = _vectP.begin(); it < _vectP.end(); it++)
	{
		std::vector<int>::iterator sortit = std::lower_bound(_vectSort.begin(), _vectSort.end(), (*it).second);
		_vectSort.insert(sortit, (*it).second);
	}

	if (tmp != NULL)
	{
		std::vector<int>::iterator ittmp = std::lower_bound(_vectSort.begin(), _vectSort.end(), valtmp);
		_vectSort.insert(ittmp, valtmp);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void PmergeMe::mergelist(void)
{
	clock_t start = clock();
	int len = _listS.size();
	int *tmp = NULL;

	if (len % 2 == 1)
	{
		for(std::list<int>::iterator it = _listS.begin(); it != getPrev(_listS.end()); it++)
		{
			if ((*it) >= (*getNext(it)))
			{
				_listP.push_back(std::make_pair((*it), (*getNext(it))));
				++it;
			}
			else
			{
				_listP.push_back(std::make_pair((*getNext(it)), (*it)));
				++it;
			}
		}
	}
	else
	{
		for(std::list<int>::iterator it = _listS.begin(); it != _listS.end(); it++)
		{
			if ((*it) >= (*getNext(it)))
			{
				_listP.push_back(std::make_pair((*it), (*getNext(it))));
				++it;
			}
			else
			{
				_listP.push_back(std::make_pair((*getNext(it)), (*it)));
				++it;
			}
		}
	}
	
	if (len % 2 == 1)
	{
		std::list<int>::iterator it = getPrev(_listS.end());
		tmp = &(*it);
	}

	sortlistP();
	insertlist(tmp);
	clock_t end = clock();
	_timeList = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.00;
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

	for (std::list<std::pair<int, int> >::iterator it = _listP.begin(); it != _listP.end(); it++)
	{
			_listSort.push_back((*it).first);
	}

	for (std::list<std::pair<int, int> >::iterator it = _listP.begin(); it != _listP.end(); it++)
	{
		std::list<int>::iterator sortit = std::lower_bound(_listSort.begin(), _listSort.end(), (*it).second);
		_listSort.insert(sortit, (*it).second);
	}

	if (tmp != NULL)
	{
		std::list<int>::iterator ittmp = std::lower_bound(_listSort.begin(), _listSort.end(), valtmp);
		_listSort.insert(ittmp, valtmp);
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

