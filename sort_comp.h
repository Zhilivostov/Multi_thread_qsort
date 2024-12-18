#pragma once
//#include <iterator>
#include <algorithm>
#include <vector>
#include <future>
//#include <functional>
#include "scheme_policies.h"



namespace quicksort
{
	template< class Iterator, class Compare>
	void q_sort(Iterator first, Iterator last, Compare comp)
	{
		const auto size = std::distance(first, last);
		if (size <= 1)
		{
			return;
		}
		const auto repoint = *first;
		auto left = first;
		auto right = last - 1;

		while (left < right)
		{
			while (comp(*left, repoint))
			{
				left++;
			}
			while (comp(repoint, *right))
			{
				right--;
			}
			std::iter_swap(left, right);
		}
		q_sort(first, left, comp);
		q_sort(left + 1, last, comp);
	}
}

template <class Iterator>

concept RandomAccessIterator = requires(Iterator k, const int n)
{
	{ k + n } -> std::same_as<Iterator>;
	{ k - n } -> std::same_as<Iterator>; 
};
template <class Compare, class... Iterator>
concept Compare_r = std::invocable<Compare, Iterator...>;

template <RandomAccessIterator Iterator, class Compare_r = std::less<>>
void my_sort(Iterator first, Iterator last, Compare_r comp = Compare_r(), const SchemePolicy&& policy = AutoPolicy())
{
	//quicksort::q_sort(first, last, comp);
	auto size = std::distance(first, last);
	auto count_thread = policy.get_count_of_thread(size);
	std::vector<Iterator> parts;
	int repoint = size / count_thread;
	for (int i = 0; i < count_thread; ++i)
	{
		auto part = first + i * repoint;
		parts.push_back(part);
	}
	parts.push_back(last);
	std::vector<std::future<void>> all_threads;
	if (count_thread == 1)
	{
		all_threads.push_back(std::async(std::launch::deferred, quicksort::q_sort<Iterator, Compare_r>, std::ref(parts[0]), std::ref(parts[1]), std::ref(comp)));
	}
	else
	{
		for (int i = 0; i < parts.size() - 1; ++i) //сделать чтобы при одном потоке он использовал не async, а например std::deferred. //готово!
		{
			all_threads.push_back(std::async(std::launch::async, quicksort::q_sort<Iterator, Compare_r>, std::ref(parts[i]), std::ref(parts[i + 1]), std::ref(comp)));
		}
	}

	for (auto& thread : all_threads)
	{
		thread.wait();
	}

	for (int i = 0; i < parts.size() - 2; ++i)
	{
		std::inplace_merge(parts[0], parts[i + 1], parts[i + 2], comp);
	}
}


//1.
//
//копировать
//const SchemePolicy && policy
//
//Заметь, что у тебя политика может приходить только по rvalue ссылке.А теперь подумай что с твоими классами не так.
//2.
//
//C++
//if (count_thread != 1)
//{
//	std::vector<Iterator> parts;
//	int repoint = size / count_thread;
//	for (int i = 0; i < count_thread; ++i)
//	{
//		auto part = first + i * repoint;
//		parts.push_back(part);
//	}
//	parts.push_back(last);
//	std::vector<std::future<void>> all_threads;
//	for (int i = 0; i < parts.size() - 1; ++i)
//	{
//		all_threads.push_back(std::async(std::launch::async, quicksort::q_sort<Iterator, Compare_r>, std::ref(parts[i]), std::ref(parts[i + 1]), std::ref(comp)));
//	}
//	for (auto& thread : all_threads)
//	{
//		thread.wait();
//	}
//	for (int i = 0; i < parts.size() - 2; ++i)
//	{
//		std::inplace_merge(parts[0], parts[i + 1], parts[i + 2], comp);
//	}
//	//////ðàçäåëÿåì è ñîðòèðóåì ÷åðåç std::async èëè std::launch::async
////std::inplace_merge ñøèâàåò ðåçóëüòàòû â ãîòîâûé îòâåò
//}
//else { quicksort::q_sort(first, last, comp); }
//
//Вот тут кажется можно вообще обойтись без проверок на количество потоков.Если у тебя один поток - ну и ладно.В std::inplace_merge он уже не зайдет никак, создаст всего одну промис, который отсортирует весь массив.Только надо бы в таком случае запустить его через std::deffered, чтоб однопоточность имитировать.
//3.
//int min_size = 100;
//Что это за магическое число ?
//const int max_count_of_threads = 8;
//И это как получил ?
//4.
//std::array<float, 5> ar = { 11.0, 5.0, 2.0, 34.0, 15.0 };
//Для чисел с плавающей точкой нужен специальный компаратор.


//1. 
//2. переделал!
//3. объяснял ранее!
//4. сделано!