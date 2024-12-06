// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<PmergeMe.cpp>>

#include "PmergeMe.hpp"

typedef std::pair<int, int>	__pair;
typedef std::chrono::time_point<std::chrono::high_resolution_clock>	__time;

#define cont	template <template <class T> class C>

#define mcstime	std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()

cont static inline C<int>	_sort(C<int> &c);

void	PmergeMe::sort(std::list<int> &seq, const uint8_t &cnt)
{
	std::deque<int>::iterator	i;
	std::list<int>::iterator	j;
	std::deque<int>				deq;
	std::list<int>				lst;
	__time						start;
	__time						end;

	if (!seq.size())
		return ;
	for (j = seq.begin(); j != seq.end();) {
		std::cout << *j;
		if (++j !=seq.end())
			std::cout << " ";
	}
	std::cout << "\n";
	if (cnt & PMM_DEQUE) {
		deq = std::deque(seq.begin(), seq.end());
		start = std::chrono::high_resolution_clock::now();
		deq = _sort(deq);
		end = std::chrono::high_resolution_clock::now();
		std::cout << "\e[38;5;42;1mDEQUE\e[m (" << mcstime << "µs)\n";
		for (i = deq.begin(); i != deq.end();) {
			std::cout << *i;
			if (++i != deq.end())
				std::cout << " ";
		}
		std::cout << "\n";
	}
	if (cnt & PMM_LIST) {
		lst = std::list(seq);
		start = std::chrono::high_resolution_clock::now();
		lst = _sort(lst);
		end = std::chrono::high_resolution_clock::now();
		std::cout << "\e[38;5;42;1mLIST\e[m (" << mcstime << "µs)\n";
		for (j = lst.begin(); j != lst.end();) {
			std::cout << *j;
			if (++j != lst.end())
				std::cout << " ";
		}
		std::cout << "\n";
	}
}

cont static inline C<int>	_sort(C<int> &c)
{
	int							a;
	int							b;
	int							odd;
	C<__pair>					pairs;
	typename C<int>::iterator	i;

	if (c.size() == 1)
		return c;
	for (i = c.begin(); i != c.end(); i++) {
		a = *i++;
		if (i == c.end())
			break ;
		b = *i;
		pairs.push_back(__pair(a, b));
	}
	odd = (c.size() & 1) ? c.back() : -1;
	c.clear();
	for (__pair &pair : pairs) {
		if (pair.second < pair.first)
			std::swap(pair.first, pair.second);
		c.push_back(pair.second);
	}
	if (odd != -1)
		c.push_back(odd);
	_sort(c);
	for (__pair &pair : pairs) {
		i = c.begin();
		while (*i < pair.first)
			i++;
		c.insert(i, pair.first);
	}
	return c;
}
