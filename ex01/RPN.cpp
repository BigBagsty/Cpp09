/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:45:23 by francisco         #+#    #+#             */
/*   Updated: 2026/04/01 22:22:02 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
    if (this != &other)
        this->data = other.data;
}

RPN::~RPN()
{
}

const RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        this->data  = other.data;
    }
    return *this;
}

int RPN::parsing(char *math)
{
    int counter = 0;
    size_t i = 0;
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

double RPN::mather(const char *input)
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
                numbers.push(num2 / num1);
            i++;
        }
    }
    return(numbers.top());
}