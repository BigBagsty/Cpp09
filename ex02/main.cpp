/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:44:03 by francisco         #+#    #+#             */
/*   Updated: 2026/06/29 15:58:36 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av) 
{
    try 
    {
        if (ac < 2) 
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        PmergeMe pm;
        pm.run(ac, av);
    } 
    
    catch (const std::exception &) 
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}