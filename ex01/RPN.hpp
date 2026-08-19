/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:45:38 by francisco         #+#    #+#             */
/*   Updated: 2026/08/03 12:17:54 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <utility>
#include <fstream>
#include <map>
#include <stack>

class RPN
{
private:
    char *data;

    
public:
    RPN();
    RPN(const RPN &other);
    ~RPN();
    const RPN &operator=(const RPN &other);
    int parsing(char *math);
    double mather(const char *input);
    

};

#endif