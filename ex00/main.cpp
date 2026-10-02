/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:29:01 by fragarc2          #+#    #+#             */
/*   Updated: 2025/12/22 12:29:01 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if(ac != 2)
	{
		std::cout << "Missing file" << std::endl;
		return 1;
	}
	BitcoinExchange bitiner;

	if(bitiner.fillMap() == false)
	{
		std::cout << "ERROR: could not use file" << std::endl;
		return 1;
	}

	bitiner.inputFinder(av[1]);

	return 0;
}
