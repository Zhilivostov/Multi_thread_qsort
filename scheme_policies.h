#pragma once
#include <thread>
#include <map>

class SchemePolicy
{
private:
	const int max_count_of_threads = 8;

public:
	SchemePolicy() = default;
	virtual int get_count_of_thread(int size) const = 0;
	virtual ~SchemePolicy() = default;
};

class AutoPolicy : public SchemePolicy
{
private:
	std::map<int, int> optimal_threads
	{
		{1024, 2},
		{2048, 3},
		{4096, 4},
		{8192, 5},
		{16384, 6},
		{32768, 7}
	};

public:
	AutoPolicy() = default;
	virtual int get_count_of_thread(int size) const override
	{
		if (size <= 1024) { return 1; }
		auto it = optimal_threads.lower_bound(size); //ищет первый ключ, равный или следующий(больший) за ним
		return (--it)->second;
	}
	virtual ~AutoPolicy() = default;
	 
};
  
class CountThreadPolicy : public SchemePolicy
{
private:
	int count_of_threads;
	//int min_size = 512;
	int min_size = 100;

public:
	CountThreadPolicy(int count) : count_of_threads(count) {};
	virtual int get_count_of_thread(int size) const override
	{
		int size_of_thread = size / count_of_threads;
		if (size_of_thread > min_size)
		{
			return count_of_threads+1;
		}
		return count_of_threads;
	}
	virtual ~CountThreadPolicy() = default;

};

class OneThreadPolicy : public SchemePolicy
{
public:
	OneThreadPolicy() = default;
	virtual int get_count_of_thread(int size) const override { return 1; }
	virtual ~OneThreadPolicy() = default;

};