/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:48:34 by fragarc2          #+#    #+#             */
/*   Updated: 2026/09/29 18:07:25 by francisco        ###   ########.fr       */
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

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if(this != &other)
		this->_Biter = other._Biter;
	return *this;
}

bool BitcoinExchange::fillMap()
{
	std::ifstream file("data.csv");
	if(!file.is_open())
		return false;
	std::string line;
	std::string line2;	
	
	if(std::getline(file, line, '\n'))
	{
		while (std::getline(file, line, ','))
		{
			if (std::getline(file, line2, '\n'))
			{
				this->_Biter[line] = std::atof(line2.c_str());
			}
		}	
	}
	else
		return false;
	return true;	
}

bool isLeapYear(int year)
{
    return (year % 400 == 0)
        || (year % 4 == 0 && year % 100 != 0);
}


bool isValidDateFormat(const std::string& date)
{
    if (date.size() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;

        if (date[i] < '0' || date[i] > '9')
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[] =
    {
        0, 31, 28, 31, 30, 31,
        30, 31, 31, 30, 31, 30, 31
    };

    if (month == 2 && isLeapYear(year))
        daysInMonth[2] = 29;

    if (day < 1 || day > daysInMonth[month])
        return false;

    return true;
}

double BitcoinExchange::findValidDate(std::string inputLine)
{
    std::map<std::string, double>::iterator it =
        this->_Biter.lower_bound(inputLine);

    if (it != this->_Biter.end() && it->first == inputLine)
        return it->second;

    if (it == this->_Biter.begin())
        return -1;

    --it;
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

bool tooLarge(const std::string &input)
{
    std::string value = input;
    if (!value.empty() && value[0] == ' ')
        value.erase(0, 1);
    size_t dot = value.find('.');
    std::string intPart;
    std::string decimalPart;
    if (dot != std::string::npos)
    {
        intPart = value.substr(0, dot);
        decimalPart = value.substr(dot + 1);
    }
	else
		intPart = value;
	if(intPart.size() > 4)
		return true;
    int intValue = std::atoi(intPart.c_str());
    if (intValue > 1000)
        return true;
    if (intValue < 1000)
        return false;
    for (size_t i = 0; i < decimalPart.size(); i++)
    {
        if (decimalPart[i] != '0')
            return true;
    }
    return false;
}

void BitcoinExchange::inputFinder(char *av)
{
	std::ifstream file(av);
	if(!file.is_open())
	{
		std::cout << "ERROR: could not use file" << std::endl;
			return ;
	}
	std::string inputLine;
	std::getline(file, inputLine, '\n');

	if (inputLine != "date | value")
	{
		std::cout << "ERROR: invalid file header" << std::endl;
			return ;
	}

	while (std::getline(file, inputLine))
	{
		if(inputLine.empty())
		{
			std::cout << "ERROR: invalid format" << std::endl;
			continue;
		}
		size_t pos = inputLine.find('|');
		if (pos == std::string::npos || pos == 0 || inputLine.find_first_of('.') != inputLine.find_last_of('.') || inputLine[pos + 1] != ' ' || inputLine[pos - 1] != ' ')
		{
			std::cout << "ERROR: invalid format" << std::endl;
			continue;
		}
		std::string date = inputLine.substr(0, pos - 1);
		std::string value = inputLine.substr(pos + 1);
		
		if (!isValidDateFormat(date))
		{
    		std::cout << "ERROR: invalid date format" << std::endl;
    		continue;
		}
		double valid = findValidDate(date);
		if(valid != -1)
		{
			if(is_digit(value) == 1 || tooLarge(value.c_str()))
			{
				std::cout << "ERROR: invalid amount" << std::endl;
			}
			else
				std::cout << date << " =>" << value << " = " << (valid * atof(value.c_str())) << std::endl;
		}
		else
			std::cout << "ERROR: invalid date" << std::endl;
	}
}
