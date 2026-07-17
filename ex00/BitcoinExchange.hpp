/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:48:17 by fragarc2          #+#    #+#             */
/*   Updated: 2026/01/20 10:48:17 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

#define INT_MAX std::numeric_limits<int>::max()

class BitcoinExchange
{
	private:
		std::map<std::string, double> _Biter;
		std::map<std::string, double> _input;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(BitcoinExchange const& a);
		void fillMap();
		void inputFinder();
		double findValidDate(std::string inputLine);
};

#endif
