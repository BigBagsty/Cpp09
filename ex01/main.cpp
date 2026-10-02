/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:44:03 by francisco         #+#    #+#             */
/*   Updated: 2026/09/24 18:56:13 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    RPN conta;
    double result;

    if (ac != 2 || !av[1][0])
    {
        std::cerr << "Error: wrong way of using code." << std::endl;
        return 1;
    }
    if (conta.parsing(av[1]) == 1)
    {
        std::cerr << "Error: wrong assortment of characters" << std::endl;
        return 1;
    }
    if (!conta.mather(av[1], result))
        return 1;
    std::cout << result << std::endl;
    return 0;      
}