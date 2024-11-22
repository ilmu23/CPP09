// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<BitcoinExchange.hpp>>

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <list>
# include <string>
# include <cstdint>
# include <exception>

typedef struct pricedata	pricedata_t;

struct pricedata {
	uint64_t	timestamp;
	double		price;
};

class BitcoinExchange
{
	private:

		std::list<pricedata_t>	_prices;

		uint64_t	dateToTimeStamp(const std::string &date) const;
		double		getPrice(const std::string &price) const;
		void		loadData(void);

	public:

		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &copy) = delete;
		BitcoinExchange &operator=(const BitcoinExchange &copy) = delete;
		~BitcoinExchange(void);

		// misc

		double	getValue(const std::string &date, const double &amount) const;

		// exception

		class InvalidDateException: public std::exception {
			const char	*what(void) const noexcept;
		};

		class InvalidAmountException: public std::exception {
			const char	*what(void) const noexcept;
		};

		class ValueTooLargeException: public std::exception {
			const char	*what(void) const noexcept;
		};
};

#endif