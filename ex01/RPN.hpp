/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:27:54 by ombatkam          #+#    #+#             */
/*   Updated: 2026/09/30 15:56:00 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <stdexcept>
# include <cctype>
# include <sstream>

class RPN
{
private:
    /* data */
public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    int executor(const int a, const int b, char operation);
    void parseStr(const std::string &str);
    bool    operators(char c) const;
    int     conversion(const std::string &token);
};



#endif // !PMERGEME_HPP
