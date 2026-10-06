/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:27:54 by ombatkam          #+#    #+#             */
/*   Updated: 2026/09/30 23:05:27 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <deque>
# include <list>
# include <algorithm>
# include <ctime>
# include <stdexcept>
# include <utility>

class PmergeMe
{
    private:
        std::deque<int> _dequeContainer;
        std::list<int>  _listContainer;
        std::deque<int>  sortDequeRecursive(std::deque<int> deq);
        size_t           getJacobsthal(size_t n);
        std::list<int>   sortListRecursive(std::list<int> lst);
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();
        
        PmergeMe(int argc, char **argv);
        void runSorting();
};

#endif
