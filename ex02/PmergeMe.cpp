#include "PmergeMe.hpp"

PmergeMe::PmergeMe() 
{
}
PmergeMe::PmergeMe(const PmergeMe &other)
{
    _vec = other._vec;
    _deq = other._deq;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other) 
{
    if (this != &other) 
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}
PmergeMe::~PmergeMe()
{
}

static size_t jacobsthal(size_t n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    size_t a = 0;
    size_t b = 1;
    size_t c = 0;
    size_t i = 2;
    while (i <= n)
    {
        c = b + 2 * a;
        a = b;
        b = c;
        ++i;
    }
    return b;
}

static std::vector<size_t> buildInsertionOrder(size_t n)
{
    std::vector<size_t> order;
    if (n == 0)
        return order;

    order.push_back(0);
    size_t prev = 1;
    size_t k = 3;

    while (prev < n)
    {
        size_t current = jacobsthal(k);
        if (current > n)
            current = n;

        size_t idx = current;
        while (idx > prev)
        {
            order.push_back(idx - 1);
            --idx;
        }
        prev = current;
        ++k;
    }
    return order;
}

static bool pairsecondcompare(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.second < b.second;
}

bool PmergeMe::parsePositiveInt(const std::string &s, int &out) const
{
    long long n = 0;
    size_t i = 0;

    if (s.empty())
        return false;
    while (i < s.size())
    {
        if (s[i] < '0' || s[i] > '9')
            return false;
        n = n * 10 + (s[i] - '0');
        if (n > std::numeric_limits<int>::max())
            return false;
        ++i;
    }
    if (n <= 0)
        return false;
    out = static_cast<int>(n);
    return true;
}

void PmergeMe::fillContainers(int ac, char **av) 
{
    for (int i = 1; i < ac; ++i) 
    {
        int value;
        if (!parsePositiveInt(av[i], value))
            throw std::runtime_error("Error");
        _vec.push_back(value);
        _deq.push_back(value);
    }
}

void PmergeMe::sortVector()
{
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> main;
    std::vector<int> pending;
    size_t i = 0;

    while (i < _vec.size())
    {
        int a = _vec[i++];
        if (i < _vec.size())
        {
            int b = _vec[i++];
            if (a < b)
                pairs.push_back(std::make_pair(a, b));
            else
                pairs.push_back(std::make_pair(b, a));
        }
        else
            pairs.push_back(std::make_pair(a, -1));
    }

    std::sort(pairs.begin(), pairs.end(), pairsecondcompare);

    for (size_t j = 0; j < pairs.size(); ++j)
    {
        if (pairs[j].second != -1)
            main.push_back(pairs[j].second);
        pending.push_back(pairs[j].first);
    }

    std::vector<size_t> order = buildInsertionOrder(pending.size());
    for (size_t k = 0; k < order.size(); ++k)
    {
        size_t idx = order[k];
        if (idx < pending.size())
        {
            std::vector<int>::iterator pos =
                std::lower_bound(main.begin(), main.end(), pending[idx]);
            main.insert(pos, pending[idx]);
        }
    }

    _vec = main;
}

void PmergeMe::sortDeque()
{
    std::deque<std::pair<int, int> > pairs;
    std::deque<int> main;
    std::deque<int> pending;
    size_t i = 0;

    while (i < _deq.size())
    {
        int a = _deq[i++];
        if (i < _deq.size())
        {
            int b = _deq[i++];
            if (a < b)
                pairs.push_back(std::make_pair(a, b));
            else
                pairs.push_back(std::make_pair(b, a));
        }
        else
            pairs.push_back(std::make_pair(a, -1));
    }

    std::sort(pairs.begin(), pairs.end(), pairsecondcompare);

    for (size_t j = 0; j < pairs.size(); ++j)
    {
        if (pairs[j].second != -1)
            main.push_back(pairs[j].second);
        pending.push_back(pairs[j].first);
    }

    std::vector<size_t> order = buildInsertionOrder(pending.size());
    for (size_t k = 0; k < order.size(); ++k)
    {
        size_t idx = order[k];
        if (idx < pending.size())
        {
            std::deque<int>::iterator pos =
                std::lower_bound(main.begin(), main.end(), pending[idx]);
            main.insert(pos, pending[idx]);
        }
    }

    _deq = main;
}

void PmergeMe::printSequence(const std::string &label, const std::vector<int> &v) const
{
    std::cout << label;
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i)
            std::cout << ' ';
        std::cout << v[i];
    }
    std::cout << std::endl;
}

void PmergeMe::printSequence(const std::string &label, const std::deque<int> &d) const 
{
    std::cout << label;
    for (size_t i = 0; i < d.size(); ++i) 
    {
        if (i) std::cout << ' ';
        std::cout << d[i];
    }
    std::cout << std::endl;
}

void PmergeMe::run(int ac, char **av)
{
    fillContainers(ac, av);
    printSequence("Before: ", _vec);

    std::clock_t startVec = std::clock();
    sortVector();
    std::clock_t endVec = std::clock();

    std::clock_t startDeq = std::clock();
    sortDeque();
    std::clock_t endDeq = std::clock();

    printSequence("After: ", _vec);

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : "
              << (endVec - startVec) * 1000000.0 / CLOCKS_PER_SEC << " microseconds" << std::endl;

    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque : "
              << (endDeq - startDeq) * 1000000.0 / CLOCKS_PER_SEC << " microseconds" << std::endl;
}