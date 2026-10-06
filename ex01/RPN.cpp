/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:28:08 by ombatkam          #+#    #+#             */
/*   Updated: 2026/09/30 16:12:15 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}
RPN::RPN(const RPN& other)
{
    (void)other;
}
RPN&    RPN::operator=(const RPN& other)
{
    (void)other;
    return (*this);
}
RPN::~RPN()
{}

int RPN::executor(const int a, const int b, char operation)
{
    if (operation == '+')
        return (a + b);
    else if (operation == '-')
        return (a - b);
    if (operation == '*')
        return (a * b);
    else if (operation == '/')
        return (a / b);
    else
        throw std::runtime_error("Error");
}

bool    RPN::operators(const char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::conversion(const std::string &token)
{
    int value;
    std::stringstream ss(token);
    
    if (!(ss >> value) || !ss.eof())
    {
        throw std::runtime_error("Error");
    }
    return (value);
}

void RPN::parseStr(const std::string &str)
{
    int             a;
    int             b;
    int             value;
    int             tmp;
    std::string     token;
    std::stack<int> results;
    std::stringstream ss(str);

    while (ss >> token)
    {
        if (token.length() == 1 && operators(token[0]))
        {
            if (results.size() < 2)
                throw std::runtime_error("Error");
            b = results.top();
            results.pop();
            a = results.top();
            results.pop();
            tmp = executor(a, b, token[0]);
            results.push(tmp);
 
        }
        else if(token.length() == 1 && token[0] >= '0' && token[0] <= '9')
        {
            value = conversion(token);
            results.push(value);
        }
        else
        {
            throw std::runtime_error("Error");
        }
    }
    if (results.size() != 1)
        throw std::runtime_error("Error");
    std::cout << results.top() << std::endl;
}