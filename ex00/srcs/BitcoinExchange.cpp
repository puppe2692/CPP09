/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:50:22 by nwyseur           #+#    #+#             */
/*   Updated: 2023/09/29 16:47:37 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(char *inputFile)
{
	std::cout << GREEN << " BitcoinExchange parameter constructor call" << RESET << std::endl;

	this->_inputFile = std::string(inputFile);
	try
	{
		csvDataFill();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		iterInput(this->_inputFile);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << RED << "BitcoinExchange desctructor call" << RESET << std::endl;
	return;
}

bool isfloat(std::string str)
{
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] != '.' && (str[i] < '0' || str[i] > '9'))
			return (false);
	}
	return (true);
}

void BitcoinExchange::csvDataFill(void)
{
	std::ifstream	infile;
	std::string		line;

	infile.open("data.csv");
	if (!infile.is_open())
		throw std::exception();
	else
	{
		while (std::getline(infile, line))
		{
			std::istringstream stream(line);
			std::string dateStr, floatPart;

			std::getline(stream, dateStr, ',');
			std::getline(stream, floatPart);

			if (isfloat(floatPart) == true)
			{
				double value = strtod(floatPart.c_str(),NULL);
				this->_csvData[dateStr] = value;
			}
		}
	}
}

bool isValidDate(const std::string& date) 
{
	std::tm tm = {};
	std::istringstream ss(date);
	ss >> tm.tm_year;
	ss.ignore();
	ss >> tm.tm_mon;
	ss.ignore();
	ss >> tm.tm_mday;
	return ss.eof() && !ss.fail() && tm.tm_year >= 2009 && tm.tm_mon >= 1 && tm.tm_mon <= 12 && tm.tm_mday >= 1 && tm.tm_mday <= 31;
}

bool BitcoinExchange::isPars(std::string line)
{	
	if (line == "date | value")
		return (true);
	
	std::string dateStr;
	std::string value;
	double valuef;
	
	if ( line.length() < 14 || line[10] != ' ' || line[12] != ' ' || line[11] != '|' || line[4] != '-' || line[7] != '-')
		throw invalidFormatException( "Error: bad input => " + line);
	dateStr = line.substr(0, 10);
	value = line.substr(13, line.length() - 13);
	if (isValidDate(dateStr) == false)
		throw invalidFormatException( "Error: invalid date => " + line);
	try
	{
		valuef = strtod(value.c_str(),NULL);
	}
	catch(const std::exception& e)
	{
		throw invalidFormatException("Error: invalid value => " + line);
	}
	if (valuef < 0)
		throw invalidFormatException("Error: not a positive number.");
	if (valuef > 1000)
		throw invalidFormatException("Error: too large a number.");
	results(dateStr, valuef);
	return (true);
	
}

template <typename Iterator>
Iterator my_prev(Iterator it)
{
	std::advance(it, -1);
	return it;
}

std::string findClosestDate(const std::map<std::string, float>& _csvData, const std::string& targetDate) 
{
	std::map<std::string, float>::const_iterator it = _csvData.lower_bound(targetDate);

	if (it == _csvData.begin()) {
		return it->first;
	}

	if (it == _csvData.end()) {
		return my_prev(it)->first;
	}

	const std::string& lowerDate = my_prev(it)->first;
	return (lowerDate);
}

void BitcoinExchange::results(std::string& date, float amount)
{
	
	std::map<std::string, float>::iterator it = _csvData.find(date);
	std::string csvDate;
	float value;

	if (it == _csvData.end())
		csvDate = findClosestDate(_csvData, date);
	else
		csvDate = date;

	value = _csvData[csvDate] * amount;

	std::cout << date << " => " << amount << " => " << value << std::endl;
}

void BitcoinExchange::iterInput(std::string input)
{
	std::ifstream	infile;
	std::string		line;

	infile.open(input.c_str());
	if (!infile.is_open())
		throw std::exception();
	else
	{
		while (std::getline(infile, line))
		{
			try
			{
				isPars(line);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
		}
	}
}