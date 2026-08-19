/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:54:31 by francisco         #+#    #+#             */
/*   Updated: 2026/06/30 11:45:28 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <limits>
#include <ctime>
#include <stdexcept>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    bool parsePositiveInt(const std::string &s, int &out) const;
    void fillContainers(int ac, char **av);
    void printSequence(const std::string &label, const std::vector<int> &v) const;
    void printSequence(const std::string &label, const std::deque<int> &d) const;
    void sortVector();
    void sortDeque();

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();
    void run(int ac, char **av);
};

#endif