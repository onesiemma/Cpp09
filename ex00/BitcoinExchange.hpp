/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:03:54 by ombatkam          #+#    #+#             */
/*   Updated: 2026/09/30 13:35:26 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <vector>
# include <stdexcept>

struct Date 
{
    int year;
    int month;
    int day;
};
struct Line
{
    std::string datestr;
    std::string valuestr;
};


template <typename T>

class BitcoinExchange
{
private:
    std::vector<Date> dates;
    std::vector<T> values;
    std::vector<T> numbers;

    size_t               getPosition(const std::string& str, char c) const;
    bool                  validDate(Date date) const;
    bool                 compareDates(const Date d1, const Date d2) const;
    bool                 dateOrder(Date d1, Date d2) const;
public:
    BitcoinExchange(/* args */);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
    
    
    T                    getValue(const std::string& str) const;
    T                    getNumber(const std::string& str) const;
    T                    TotalPrice(const T value, const T number) const;
    Date                 getDate(const std::string& str) const;
    Line                 parseLineNumber(const std::string& str) const;
    Line                 parseLineValue(const std::string& str) const;
    std::vector<Line>    getLines(const std::string &filename) const;
    std::vector<Date>    myDates(const std::vector<Line> lines) const;
    std::vector<T>       myValues(const std::vector<Line> lines) const;
    bool                 validValue(const T& value) const;
    bool                 validNumber(const T& number) const;
    void                 printData(const std::string &filename1, const std::string &filename2) const;
    size_t               findDate(const Date date, const std::vector<Date> dates) const;
};

#include "BitcoinExchange.cpp"
#endif // !BITCOINEXCHANGE_CPP
