/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:41:47 by nwyseur           #+#    #+#             */
/*   Updated: 2023/10/04 18:09:06 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <exception>
# include <iterator>
# include <cstdlib>
# include <cstring>
# include <utility>

# include <limits>
# include <sstream>
# include <algorithm>

# define RED "\e[0;31m"
# define RESET "\e[0m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"

class PmergeMe
{
	public:
		PmergeMe(char** str);
		~PmergeMe();

		void parsing(char** str);
		void sequencing(char** str);
		void mergevect(void);
		void sortvectP(void);
		void insertvect(int* tmp);
		void printvect(int i);

		void mergelist(void);
		void sortlistP(void);
		void insertlist(int* tmp);
		void printlist(int i);

		template<typename T>
		T getPrev(T it);
		template<typename T>
		T getNext(T it);
		template<typename T>
		T getdbnext(T it);

		class invalidFormatException : public std::exception
		{
			public:
				invalidFormatException(const std::string& msg)
				{
					_message = msg;
				}
				virtual const char* what() const throw()
				{
					return (_message.c_str());
				}
				virtual ~invalidFormatException() throw() {}

			private:
				std::string _message;
		};

	private:
		PmergeMe() {}
		PmergeMe(PmergeMe const& other);
		PmergeMe& operator=(PmergeMe const& other);
		std::vector<int>	_vectS;
		std::list<int>		_listS;
		std::vector<std::pair<int, int> >	_vectP;
		std::list<std::pair<int, int> >	_listP;

};

#endif
