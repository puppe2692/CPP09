/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:17:04 by nwyseur           #+#    #+#             */
/*   Updated: 2023/09/29 16:36:44 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <ctime>
# include <algorithm>
# include <exception>
# include <cstdlib>

# define RED "\e[0;31m"
# define RESET "\e[0m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"

class BitcoinExchange
{
	public:
		BitcoinExchange(char *inputile);
		~BitcoinExchange();

		void	csvDataFill(void);
		void	iterInput(std::string input);
		bool	isPars(std::string line);
		void	results(std::string& date, float amount);

		class invalidFormatException : public std::exception
		{
			public:
				invalidFormatException(const std::string& msg)
				{
					_message = msg;
				}
				virtual const char *what() const throw()
				{
					return (_message.c_str());
				}
				virtual ~invalidFormatException() throw() {}

			private:
				std::string _message;
		};

	private:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange& other);
		BitcoinExchange& operator=(BitcoinExchange& other);
		std::map<std::string, float> _csvData;
		std::string _inputFile;

};


#endif