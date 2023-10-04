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
	while (it != ite)
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