// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<main.cpp>>

#include <fstream>
#include <iomanip>
#include <iostream>
#include "BitcoinExchange.hpp"

#define FLTCFG	std::fixed << std::setprecision(2)

#define _stod(x)	((x.find('.')) ? std::stod(x) : static_cast<double>(std::stoull(x)))
#define _trim(x)	(x.substr(x.find_first_not_of("\t\n\v\r\f "), x.find_last_not_of("\t\n\v\r\f ") - x.find_first_not_of("\t\n\v\r\f ") + 1))

int32_t	main(int32_t ac, char **av)
{
	BitcoinExchange	FTX;
	std::ifstream	file;
	std::string		line;
	std::string		date;
	double			amount;
	double			val;

	if (ac != 2) {
		if (ac < 2)
			std::cout << "Missing input file\n";
		else
			std::cout << "Too many arguments\n";
		return 1;
	}
	file.open(av[1]);
	if (!file.is_open()) {
		std::cout << "Unable to open file '" << av[1] << "'\n";
		return 1;
	}
	std::getline(file, line);
	while (!file.eof()) {
		std::getline(file, line);
		if (!line.empty() && line.find('|') != std::string::npos) {
			try {
				date = line.substr(0, line.find('|'));
				date = _trim(date);
				try {
					amount = _stod(_trim(line.substr(line.find('|') + 1)));
				} catch (std::exception &e) {
					std::cout << "Error: '" << line << "': Invalid Amount\n";
				}
				val = FTX.getValue(date, amount);
				std::cout << FLTCFG << amount << " BTC @ " << date << " = " << val << "\n";
			} catch (BitcoinExchange::InvalidDateException &e) {
				std::cout << "Error: '" << line << "': Invalid date\n";
			} catch (BitcoinExchange::InvalidAmountException &e) {
				std::cout << "Error: '" << line << "': Invalid Amount\n";
			} catch (BitcoinExchange::ValueTooLargeException &e) {
				std::cout << "Error: '" << line << "': Value too large\n";
			}
		} else if (!line.empty())
			std::cout << "Error: '" << line << "': Invalid input\n";
	}
	file.close();
	return 0;
}
