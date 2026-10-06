/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:28:00 by ombatkam          #+#    #+#             */
/*   Updated: 2026/09/30 16:08:16 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: Invalid arguments." << std::endl;
        return (1);
    }
    try
    {
        RPN rpn;
        rpn.parseStr(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    return (0);
}