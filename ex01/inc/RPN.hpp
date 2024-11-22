// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<RPN.hpp>>

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <cstdint>
# include <sstream>
# include <exception>

class RPN
{
	private:

		std::stack<uint64_t>	_stack;

	public:

		RPN(void);
		RPN(const RPN &copy) = delete;
		RPN &operator=(const RPN &copy) = delete;
		~RPN(void);

		// misc

		void	solve(std::stringstream &expr);

		// exception

		class InvalidExpressionException: public std::exception {
			const char	*what(void) const noexcept;
		};
};

#endif
