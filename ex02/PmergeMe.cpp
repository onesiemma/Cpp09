/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:28:08 by ombatkam          #+#    #+#             */
/*   Updated: 2026/09/30 22:56:14 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Forme Canonique de Coplien
PmergeMe::PmergeMe() 
{}
PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        this->_dequeContainer = other._dequeContainer;
        this->_listContainer = other._listContainer;
    }
    return *this;
}

PmergeMe::~PmergeMe() 
{}

PmergeMe::PmergeMe(int argc, char **argv)
{
    if (argc < 2)
        throw std::runtime_error("Error");

    for (int i = 1; i < argc; ++i)
    {
        std::string token(argv[i]);
        if (token.empty())
            throw std::runtime_error("Error");
        for (size_t j = 0; j < token.length(); ++j)
        {
            if (!std::isdigit(token[j]))
                throw std::runtime_error("Error");
        }
        std::stringstream ss(token);
        long val;
        ss >> val;
        if (ss.fail() || !ss.eof() || val < 0 || val > 2147483647)
            throw std::runtime_error("Error");
        _dequeContainer.push_back(static_cast<int>(val));
        _listContainer.push_back(static_cast<int>(val));
    }
}

size_t PmergeMe::getJacobsthal(size_t n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    size_t prev2 = 0;
    size_t prev1 = 1;
    size_t current = 0;
    for (size_t i = 2; i <= n; ++i)
    {
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

/* ================================================================= */
/*                        DEQUE   IMPLEMENTATION.                    */
/* ================================================================= */

std::deque<int> PmergeMe::sortDequeRecursive(std::deque<int> deq)
{
    size_t n = deq.size();
    if (n <= 1)
        return deq;
    std::deque<std::pair<int, int> > pairs;
    int straggler = -1;
    bool has_straggler = false;
    if (n % 2 != 0)
    {
        straggler = deq.back();
        has_straggler = true;
        deq.pop_back();
    }
    for (size_t i = 0; i < deq.size(); i += 2)
    {
        int a = deq[i];
        int b = deq[i + 1];
        if (a > b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    std::deque<int> largerElements;
    for (size_t i = 0; i < pairs.size(); ++i)
        largerElements.push_back(pairs[i].second);

    largerElements = sortDequeRecursive(largerElements);

    std::deque<int> mainChain = largerElements;
    std::deque<int> pending;
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].second == mainChain[i])
            {
                pending.push_back(pairs[j].first);
                break;
            }
        }
    }
    if (!pending.empty())
    {
        mainChain.push_front(pending[0]);
        pending.pop_front();
    }
    size_t jacobIndex = 3;
    size_t insertedCount = 0;
    while (!pending.empty())
    {
        size_t currentJacob = getJacobsthal(jacobIndex);
        size_t chunkToInsert = (currentJacob > pending.size()) ? pending.size() : currentJacob;

        while (chunkToInsert > insertedCount)
        {
            int valToInsert = pending[chunkToInsert - 1 - insertedCount];
            std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), valToInsert);
            mainChain.insert(it, valToInsert);
            insertedCount++;
        }
        
        if (chunkToInsert == pending.size())
            break;
        
        jacobIndex++;
        insertedCount = 0;
        for (size_t k = 0; k < chunkToInsert; ++k)
            pending.pop_front();
    }

    if (has_straggler)
    {
        std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(it, straggler);
    }

    return mainChain;
}

/* ================================================================= */
/*                      LIST      IMPLEMENTATION                     */
/* ================================================================= */

std::list<int> PmergeMe::sortListRecursive(std::list<int> lst)
{
    size_t n = lst.size();
    if (n <= 1)
        return lst;
    std::list<std::pair<int, int> > pairs;
    int straggler = -1;
    bool has_straggler = false;
    if (n % 2 != 0)
    {
        straggler = lst.back();
        has_straggler = true;
        lst.pop_back();
    }
    std::list<int>::iterator it = lst.begin();
    while (it != lst.end())
    {
        int a = *it;
        ++it;
        int b = *it;
        ++it;
        if (a > b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    std::list<int> largerElements;
    for (std::list<std::pair<int, int> >::iterator pit = pairs.begin(); pit != pairs.end(); ++pit)
        largerElements.push_back(pit->second);
    largerElements = sortListRecursive(largerElements);
    std::list<int> mainChain = largerElements;
    std::list<int> pending;
    for (std::list<int>::iterator mit = mainChain.begin(); mit != mainChain.end(); ++mit)
    {
        for (std::list<std::pair<int, int> >::iterator pit = pairs.begin(); pit != pairs.end(); ++pit)
        {
            if (pit->second == *mit)
            {
                pending.push_back(pit->first);
                break;
            }
        }
    }
    if (!pending.empty())
    {
        mainChain.push_front(pending.front());
        pending.pop_front();
    }
    size_t jacobIndex = 3;
    size_t insertedCount = 0;
    while (!pending.empty())
    {
        size_t currentJacob = getJacobsthal(jacobIndex);
        size_t chunkToInsert = (currentJacob > pending.size()) ? pending.size() : currentJacob;

        while (chunkToInsert > insertedCount)
        {
            std::list<int>::iterator pit = pending.begin();
            std::advance(pit, chunkToInsert - 1 - insertedCount);
            int valToInsert = *pit;

            std::list<int>::iterator insert_it = std::lower_bound(mainChain.begin(), mainChain.end(), valToInsert);
            mainChain.insert(insert_it, valToInsert);
            insertedCount++;
        }
        
        if (chunkToInsert == pending.size())
            break;
        jacobIndex++;
        insertedCount = 0;
        for (size_t k = 0; k < chunkToInsert; ++k)
            pending.pop_front();
    }

    if (has_straggler)
    {
        std::list<int>::iterator insert_it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(insert_it, straggler);
    }

    return mainChain;
}

/* ================================================================= */
/*                     EXECUTION AND DISPLAYING                      */
/* ================================================================= */

void PmergeMe::runSorting()
{
    std::cout << "Before: ";
    for (std::deque<int>::iterator it = _dequeContainer.begin(); it != _dequeContainer.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    size_t elementCount = _dequeContainer.size();
    clock_t startDeque = clock();
    _dequeContainer = sortDequeRecursive(_dequeContainer);
    clock_t endDeque = clock();
    double timeDeque = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;
    clock_t startList = clock();
    _listContainer = sortListRecursive(_listContainer);
    clock_t endList = clock();
    double timeList = static_cast<double>(endList - startList) / CLOCKS_PER_SEC * 1000000;
    std::cout << "After: ";
    for (std::deque<int>::iterator it = _dequeContainer.begin(); it != _dequeContainer.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "Time to process a range of " << elementCount << " elements with std::deque : " << timeDeque << " us" << std::endl;
    std::cout << "Time to process a range of " << elementCount << " elements with std::list : " << timeList << " us" << std::endl;
}