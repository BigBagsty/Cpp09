/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:45:23 by francisco         #+#    #+#             */
/*   Updated: 2026/09/29 18:25:01 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
    (void)other;
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return *this;
}

int RPN::parsing(char *math)
{
    int counter = 0;
    size_t i = 0;

    while(math[i] == ' ')
        i++;
    if(isdigit((unsigned char)math[i]) && !math[i + 1])
        return 0;
        
    while(math[i])
    {
        if (isdigit((unsigned char)math[i]) && !math[i + 1])
            return 1;
        if (math[i + 1] && ((isdigit((unsigned char)math[i]) || math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/') && math[i + 1] != ' '))
            return 1;
        else if (isdigit((unsigned char)math[i]))
            counter++;
        else if(math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/')
            counter--;
        else if(math[i] != ' ')
            return 1;
        i++;
    }
    if (counter != 1)
        return 1;
    return 0;
}

bool RPN::mather(const char *input, double &result)
{
    std::stack<double> numbers;
    size_t i = 0;
    
    double num1, num2;
    while (input[i])
    {
        if (input[i] == ' ')
            i++;
        else if (isdigit((unsigned char)input[i]))
        {
            numbers.push(input[i] - '0');
            i++;
        }
        else
        {
            if (numbers.size() < 2)
            {
                std::cerr << "Error: not enough operands" << std::endl;
                return false;
            }
            num1 = numbers.top();
            numbers.pop();
            num2 = numbers.top();
            numbers.pop();
            if (input[i] == '+')
                numbers.push(num2 + num1);
            else if (input[i] == '-')
                numbers.push(num2 - num1);
            else if (input[i] == '*')
                numbers.push(num2 * num1);
            else
            {
                if(num1 == 0)
                {
                    std::cerr << "Error: dividing by zero is inconclusive" << std::endl;
                    return false;
                }
                numbers.push(num2 / num1);
            }
            i++;
        }
    }
    result = numbers.top();
    return true;
}