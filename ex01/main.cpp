/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:44:03 by francisco         #+#    #+#             */
/*   Updated: 2026/08/14 12:59:49 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    RPN conta;

    if (ac != 2 || !av[1][0])
    {
        std::cout << "Error: wrong way of using code." << std::endl;
        return -1;
    }
    if (conta.parsing(av[1]) == 1)
    {
        std::cout << "Error" << std::endl;
        return -1;
    }
    else     
        std::cout << conta.mather(av[1]) << std::endl;
    return 0;      
}