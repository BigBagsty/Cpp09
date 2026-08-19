/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:48:34 by fragarc2          #+#    #+#             */
/*   Updated: 2026/08/03 10:11:15 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}
BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	if(this != &other)
			*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& a)
{
	if(this != &a)
		*this = a;
	return *this;
}

void BitcoinExchange::fillMap()
{
	std::ifstream file("data.csv");
	std::string line;
	std::string line2;
	std::map<std::string, double>::iterator it = this->_Biter.begin();

	while (std::getline(file, line, ','))
	{
		if (std::getline(file, line2, '\n'))
		{
			this->_Biter[line] = std::atof(line2.c_str());
			it++;
		}
	}
}

bool isValidDateFormat(const std::string& date)
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
            return false;
    }
    return true;
}

double BitcoinExchange::findValidDate(std::string inputLine)
{
	std::map<std::string, double>::iterator it = this->_Biter.lower_bound(inputLine);
	if (it != this->_Biter.end() && it->first == inputLine)
		return static_cast<int>(it->second);
	if(it == this->_Biter.begin())
		return -1;
	it--;
	return it->second;
}

int is_digit(std::string& str)
{
	int i = 0;
		
	if (str[i] == ' ')
		i++;
	if (!str[i] || str[0] != ' ')
		return 1;
	while(str[i])
	{
		if ((str[i] > '9' || str[i] < '0') && (str[i] != '.'))
			return 1;
		if (str[i] == '.' && (str[i + 1] > '9' || str[i + 1] < '0'))
			return 1;
		if (str[i] == '.' && (str[i - 1] > '9' || str[i - 1] < '0'))
		return 1;
		i++;
	}
	return 0;
}

void BitcoinExchange::inputFinder()
{
	std::ifstream file("input.txt");
	std::string inputLine;
	std::string Line;
	std::getline(file, inputLine, '\n');


	while (std::getline(file, inputLine))
	{
		if(inputLine.empty())
		{
			std::cout << "ERROR: invalid format" << std::endl;
			continue;
		}
		size_t pos = inputLine.find('|');
		if (pos == std::string::npos || inputLine.find_first_of('.') != inputLine.find_last_of('.') || inputLine[pos + 1] != ' ' || inputLine[pos - 1] != ' ')
		{
			std::cout << "ERROR: invalid format" << std::endl;
			continue;
		}
		std::string date = inputLine.substr(0, pos - 1);
		std::string value = inputLine.substr(pos + 1);
		
		if (!isValidDateFormat(date))
		{
    		std::cout << "ERROR: invalid date" << std::endl;
    		continue;
		}
		if(findValidDate(date) != -1)
		{
			if(is_digit(value) == 1 || atof(value.c_str()) > 1000)
			{
				std::cout << "ERROR: invalid amount" << std::endl;
			}
			else
				std::cout << date << " =>" << value << " = " << (findValidDate(date) * atof(value.c_str())) << std::endl;
		}
		else
			std::cout << "ERROR: invalid date" << std::endl;
	}

}
