/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:45:38 by francisco         #+#    #+#             */
/*   Updated: 2026/09/29 18:12:52 by francisco        ###   ########.fr       */
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
    RPN &operator=(const RPN &other);
    int parsing(char *math);
    bool mather(const char *input, double &result);
    

};

#endif