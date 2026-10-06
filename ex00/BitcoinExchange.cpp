/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:04:00 by ombatkam          #+#    #+#             */
/*   Updated: 2026/09/29 19:15:06 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "BitcoinExchange.hpp"

template <typename T>
BitcoinExchange<T>::BitcoinExchange()
{}
template <typename T>
BitcoinExchange<T>::BitcoinExchange(const BitcoinExchange& other): dates(other.dates), values(other.values), numbers(other.numbers)
{}
template <typename T>
BitcoinExchange<T>& BitcoinExchange<T>::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        dates = other.dates;
        values = other.values;
        numbers = other.numbers;
    }
    return (*this);
}
template <typename T>
BitcoinExchange<T>::~BitcoinExchange()
{}

template <typename T>
bool BitcoinExchange<T>::compareDates(const Date d1, const Date d2) const
{
    return (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year);
}

template <typename T>
bool    BitcoinExchange<T>::dateOrder(const Date d1, const Date d2) const
{
    if (d1.year > d2.year)
        return (true);
    else if (d1.year == d2.year && d1.month > d2.month)
        return (true);
    else if (d1.year == d2.year && d1.month == d2.month && d1.day > d2.day)
        return (true);
    return (false);
}
template <typename T>
size_t   BitcoinExchange<T>::getPosition(const std::string& str, char c) const
{
    size_t  pos;
    pos = str.find(c);
    if (pos == std::string::npos)
        return (0);
    return (pos); 
}

template <typename T>
bool BitcoinExchange<T>::validDate(const Date date) const
{
    if (date.day < 1)
        return (0);
    if (date.month == 2)
    {
        if (date.year % 4 == 0)
        {
            if (date.day > 29)
                return (0);
        }
        else if (date.day > 28)
            return (0);
        
    }
    if (date.month < 8 && date.month > 0)
    {
        if (date.month % 2 == 1)
        {
            if (date.day > 31)
                return (0);
        }
        else
        {
            if (date.day > 30)
                return (0);
        }
    }
    else if (date.month >= 8 && date.month < 13)
    {
        if (date.month % 2 == 0)
        {
            if (date.day > 31)
                return (0);
        }
        else
        {
            if (date.day > 30)
                return (0);
        }
    }
    return (1);
}
template <typename T>
bool    BitcoinExchange<T>::validNumber(const T& number) const
{
    return (number >= 0 && number <= 1000);
}

template <typename T>
bool    BitcoinExchange<T>::validValue(const T& value) const
{
    return (value >= 0);
}

template <typename T>
Date    BitcoinExchange<T>::getDate(const std::string& str) const
{
    Date    d;
    char    dash1;
    char    dash2;

    std::istringstream  iss(str);
    if (!(iss >> d.year >> dash1 >> d.month >> dash2 >> d.day) || (dash1 != '-') || (dash2 != '-'))
        throw std::invalid_argument("Error: bad input => " + str);
    if ((d.year > 2026 || d.year < 0) || (d.month > 12 || d.month < 1) || (!validDate(d)))
        throw std::invalid_argument("Error: bad input => " + str);
    return (d);
}

template <typename T>
T   BitcoinExchange<T>::getValue(const std::string& str) const
{
    T   value;
    std::istringstream  iss(str);
    if (!(iss >> value) || !iss.eof())
        throw std::invalid_argument("Error: invalid Value");
    if (!validValue(value))
        throw std::invalid_argument("Error: invalid Value");
    return (value);
}

template <typename T>
T   BitcoinExchange<T>::getNumber(const std::string& str) const
{
    T   number;
    std::istringstream  iss(str);
    if (!(iss >> number) || !iss.eof())
        throw std::invalid_argument("Error: invalid Number");
    if (!validNumber(number))
    {
        if (number < 0)
            throw std::invalid_argument("Error: not a positive number.");
        else if (number > 1000)
            throw std::invalid_argument("Error: too large number");
        else
            throw std::invalid_argument("Error: invalid Number");
    }
    return (number);
}

template <typename T>
T   BitcoinExchange<T>::TotalPrice(const T value, const T number) const
{
    if (validNumber(number) && validValue(value))
        return (value * number);
    else if (number < 0)
        throw std::invalid_argument("Error: not a positive number.");
    else if (number > 1000)
        throw std::invalid_argument("Error: too large number");
    else
        throw std::invalid_argument("Error: invalid Number");
}

template <typename T>
Line    BitcoinExchange<T>::parseLineNumber(const std::string& str) const
{
    Line    line;
    size_t  pos;

    pos = getPosition(str, '|');
    if (pos == 0)
        throw std::invalid_argument("Error: bad input => " + str);
    line.datestr = str.substr(0, pos);
    line.valuestr = str.substr(pos + 1);
    return (line);
}

template <typename T>
Line    BitcoinExchange<T>::parseLineValue(const std::string& str) const
{
    Line    line;
    size_t  pos;

    pos = getPosition(str, ',');
    if (pos == 0)
        throw std::invalid_argument("Error: bad input => " + str);
    line.datestr = str.substr(0, pos);
    line.valuestr = str.substr(pos + 1);
    return (line);
}

template <typename T>
std::vector<Line>   BitcoinExchange<T>::getLines(const std::string &filename) const
{
    Line                myLine;
    std::vector<Line>   lines;
    std::string         line;
    std::ifstream    file(filename.c_str());

    if (!file.is_open())
        throw std::invalid_argument("Error: could not open file.");
    std::getline(file, line);
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        try
        {
            myLine = parseLineValue(line);
            lines.push_back(myLine);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << ": " << line << '\n';
        }
        
    }
    return (lines);  
}

template <typename T>
std::vector<Date> BitcoinExchange<T>::myDates(const std::vector<Line> lines) const
{
    Date    date;
    std::vector<Date>   dates;
    
    for (size_t i = 0; i < lines.size(); i++)
    {
        try
        {
            date = getDate(lines[i].datestr);
            dates.push_back(date);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << ": " << lines[i].datestr << '\n';
        }   
    }
    return (dates);
}

template <typename T>
std::vector<T> BitcoinExchange<T>::myValues(const std::vector<Line> lines) const
{
    T    value;
    std::vector<T>   values;
    
    for (size_t i = 0; i < lines.size(); i++)
    {
        try
        {
            value = getValue(lines[i].valuestr);
            values.push_back(value);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << ": " << lines[i].valuestr << '\n';
        }   
    }
    return (values);
}

template <typename T>
size_t    BitcoinExchange<T>::findDate(const Date myDate, const std::vector<Date> dates) const
{  
    for (size_t i = 0; i < dates.size(); i++)
    {
        if (compareDates(myDate, dates[i]))
            return (i);
        if (!dateOrder(myDate, dates[i]))
        {
            if (i == 0)
                return (0);
            return (i - 1);
        }
    }
    return (dates.size() - 1);
}


template <typename T>
void    BitcoinExchange<T>::printData(const std::string &filename1, const std::string &filename2) const
{
    std::vector<Line>   dbLines = getLines(filename1);
    std::vector<Date>   dbDates = myDates(dbLines);
    std::vector<T>      dbValues = myValues(dbLines);
    Line                lineparsed;
    Date                date;
    T                   number;
    T                   rate;
    T                   total;
    size_t              index;
    std::ifstream file(filename2.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        try
        {
            lineparsed = parseLineNumber(line);
            date = getDate(lineparsed.datestr);
            number = getNumber(lineparsed.valuestr);
            index = findDate(date, dbDates);
            rate = dbValues[index];
            total = rate * number;

            std::cout << date.year << "-";
            if (date.month < 10) std::cout << "0";
            std::cout << date.month << "-";
            if (date.day < 10) std::cout << "0";
            std::cout << date.day << " => " 
                      << number << " = " 
                      << total << std::endl;
        }
        catch(const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    file.close();
}
