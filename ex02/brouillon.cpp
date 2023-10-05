	for (unsigned long j = 0; j < _vectP.size(); j++)
	{
		std::cout << j << " - first: " << _vectP[j].first << std::endl;
		std::cout << j << " - second: " << _vectP[j].second << std::endl;
		std::cout << '\n';
	}
	if (len % 2 == 1)
	{
		std::cout << "on top: " << tmp << std::endl;
	}


void PmergeMe::printlist(int i) // effacer
{
	std::list<int>::iterator	it = _listS.begin();
	std::list<int>::iterator	ite = _listS.end();
	if (i == 0)
		std::cout << "Before L:";
	if (i == 1)
		std::cout << "After L:";
	while (it != ite)void PmergeMe::printvect(int i)
{
	if (i == 0)
	{
		std::cout << "Before V:";
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
	if (i == 0)
	{
		std::cout << "After V:";
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
	for(unsigned long j = 0; j < _vectSort.size(); j++)
		std::cout << ' ' << this->_vectSort[j];
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
	for(unsigned long j = 0; j < _listSort.size(); j++)
	{
		std::list<int>::iterator it = _listSort.begin();
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

	{
		std::cout << ' ' << *it;
		it++;
	}
	std::cout << '\n';
}
	for (unsigned long i = 0; Jacobstyle[i] < _vectS.size() * 2; i++)
	{
		std::vector<std::pair<int, int> >::iterator it = _vectP.begin() + i;
		std::vector<int>::iterator itsorted = std::lower_bound(_vectS.begin(), _vectS.begin() + Jacobstyle[i], (*it).second);
		_vectS.insert(itsorted, (*it).second);
	}

	unsigned long arr[] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	std::vector<unsigned long> Jacobstyle(arr, arr + sizeof(arr) / sizeof(arr[0]));
	
	for (std::vector<std::pair<int, int> >::iterator it = _vectP.begin(); it < _vectP.end(); it++)
	{
		std::vector<int>::iterator sortit = std::lower_bound(_vectS.begin(), _vectS.end(), (*it).second);
		_vectS.insert(sortit, (*it).second);
	}


	///////////////////////////////////

	void PmergeMe::printvect(int i)
{
	if (i == 0)
	{
		std::cout << "Before V:";
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
	if (i == 0)
	{
		std::cout << "After V:";
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
	for(unsigned long j = 0; j < _vectSort.size(); j++)
		std::cout << ' ' << this->_vectSort[j];
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
	for(unsigned long j = 0; j < _listSort.size(); j++)
	{
		std::list<int>::iterator it = _listSort.begin();
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
