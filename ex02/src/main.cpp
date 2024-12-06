// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<main.cpp>>

#include <string>
#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	std::string			opts[3] = { "-b", "-d", "-l"};
	std::list<int>	arg;
	uint8_t				cnt;
	size_t				i;

	if (ac == 1)
		return 0;
	for (i = 0; i < 3; i++) {
		if (std::string(av[1]) == opts[i])
			break ;
	}
	switch (i) {
		case 0:
			cnt = PMM_DEQUE | PMM_LIST;
			i = 2;
			break ;
		case 1:
			cnt = PMM_DEQUE;
			i = 2;
			break ;
		case 2:
			cnt = PMM_LIST;
			i = 2;
			break ;
		default:
			cnt = PMM_DEQUE | PMM_LIST;
			i = 1;
	}
	for (; i < static_cast<size_t>(ac); i++)
		arg.push_back(std::stoi(av[i]));
	PmergeMe::sort(arg, cnt);
	return 0;
}
