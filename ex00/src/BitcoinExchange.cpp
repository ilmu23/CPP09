// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<BitcoinExchange.cpp>>

#include <cfenv>
#include <fstream>
#include <sstream>
#include <iostream>
#include "BitcoinExchange.hpp"

#define _isleapyear(x)		(x % 4 == 0 && (x % 100 != 0 || x % 400 == 0))
#define _inrange(x, y, z)	(x >= y && x <= z)

static inline uint16_t	_addLeapDays(const uint16_t &year);
static inline uint16_t	_getDays(const uint16_t &month);

BitcoinExchange::BitcoinExchange(void)
{
	this->loadData();
}

BitcoinExchange::~BitcoinExchange(void) {}

// misc

double	BitcoinExchange::getValue(const std::string &date, const double &amount) const
{
	std::vector<pricedata_t>::const_iterator	i;
	uint64_t									ts;
	double										out;

	if (amount < 0)
		throw BitcoinExchange::InvalidAmountException();
	i = this->_prices.cbegin();
	ts = dateToTimeStamp(date);
	while (i != this->_prices.cend() && (*i).timestamp < ts)
		i++;
	if ((*i).timestamp != ts && i != this->_prices.cbegin())
		i--;
	std::feclearexcept(FE_OVERFLOW);
	out = amount * (*i).price;
	if (std::fetestexcept(FE_UNDERFLOW))
		throw BitcoinExchange::ValueTooLargeException();
	return out;
}

// exception

const char	*BitcoinExchange::InvalidDateException::what(void) const noexcept
{
	return "Invalid date";
}

const char	*BitcoinExchange::InvalidAmountException::what(void) const noexcept
{
	return "Invalid amount";
}

const char	*BitcoinExchange::ValueTooLargeException::what(void) const noexcept
{
	return "Value too large";
}

// private methods

uint64_t	BitcoinExchange::dateToTimeStamp(const std::string &date) const
{
	std::stringstream	_date;
	std::string			tmp;
	uint16_t			year;
	uint16_t			month;
	uint16_t			day;
	uint64_t			ts;

	_date = std::stringstream(date);
	std::getline(_date, tmp, '-');
	year = std::stoi(tmp); 
	std::getline(_date, tmp, '-');
	month = std::stoi(tmp); 
	std::getline(_date, tmp, '-');
	day = std::stoi(tmp); 
	if (!_date.eof() || !_inrange(year, 0, 9999))
		throw BitcoinExchange::InvalidDateException();
	switch (month) {
		case 1:
			if (!_inrange(day, 1, 31))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 2:
			if (!_inrange(day, 1, 28 + (_isleapyear(year)) ? 1 : 0))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 3:
			if (!_inrange(day, 1, 31))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 4:
			if (!_inrange(day, 1, 30))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 5:
			if (!_inrange(day, 1, 31))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 6:
			if (!_inrange(day, 1, 30))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 7:
			if (!_inrange(day, 1, 31))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 8:
			if (!_inrange(day, 1, 31))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 9:
			if (!_inrange(day, 1, 30))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 10:
			if (!_inrange(day, 1, 31))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 11:
			if (!_inrange(day, 1, 30))
				throw BitcoinExchange::InvalidDateException();
			break ;
		case 12:
			if (!_inrange(day, 1, 31))
				throw BitcoinExchange::InvalidDateException();
			break ;
		default:
			throw BitcoinExchange::InvalidDateException();
	}
	ts = year * 12 * 365;
	ts += _getDays(month);
	ts += day;
	if (_isleapyear(year) && month > 2)
		ts++;
	return ts + _addLeapDays(year);
}

double	BitcoinExchange::getPrice(const std::string &price) const
{
	if (price.find(".") != std::string::npos)
		return std::stod(price);
	return static_cast<double>(std::stoull(price));
}

void	BitcoinExchange::loadData(void)
{
	std::ifstream	f;
	std::string		buf;

	f.open("data.csv");
	if (!f.is_open()) {
		std::cout << "btc: unable to open database file\n";
		return ;
	}
	std::getline(f, buf);
	while (!f.eof()) {
		std::getline(f, buf);
		if (buf.empty())
			break ;
		this->_prices.push_back({
			.timestamp = dateToTimeStamp(buf.substr(0, buf.find(','))),
			.price = getPrice(buf.substr(buf.find(',') + 1))
		});
	}
	f.close();
}

static inline uint16_t	_addLeapDays(const uint16_t &year)
{
	uint16_t	ldays;
	uint16_t	_year;

	for (ldays = _year = 0; _year < year; _year += 4) {
		if (_isleapyear(_year))
			ldays++;
	}
	return ldays++;
}

static inline uint16_t	_getDays(const uint16_t &month)
{
	static const uint8_t	dayarr[11] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
	uint16_t				days;
	size_t					i;

	for (i = days = 0; i < static_cast<size_t>(month - 1); i++)
		days += dayarr[i];
	return days;
}
