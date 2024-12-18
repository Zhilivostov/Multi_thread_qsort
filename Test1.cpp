//#pragma once
#include "sort_comp.h"
#include "scheme_policies.h"
#include <gtest/gtest.h>
#include <deque>
#include <array>
#include <vector>

using namespace std;

template<typename T>
bool comp_less(const T& x, const T& y)
{
	return (x < y);
}

template<typename T>
bool comp_more(const T& x, const T& y)
{
	return (x > y);
}

static bool comp_less(const float& x, const float& y)  //добавлены компараторы для float
{
	return (x < y);
}

static bool comp_more(const float& x, const float& y)
{
	return (x > y);
}

//TEST(Vector, Int_less)
//{
//	std::vector<int> vec1 = { 5, 8, 4, 12, 6, 3, 9 };
//	my_sort(vec1.begin(), vec1.end(), comp_less<int>);
//	EXPECT_TRUE(std::is_sorted(vec1.begin(), vec1.end(), comp_less<int>));
//}
//
//TEST(Vector, Int_more)
//{
//	std::vector<int> vec1 = { 5, 8, 4, 12, 6, 3, 9 };
//	my_sort(vec1.begin(), vec1.end(), comp_more<int>);
//	EXPECT_TRUE(std::is_sorted(vec1.begin(), vec1.end(), comp_more<int>));
//}
//
//TEST(Vector, Double_less)
//{
//	std::vector<double> vec1 = { 5.0, 8.0, 4.0, 12.0, 6.0, 3.0, 9.0 };
//	my_sort(vec1.begin(), vec1.end(), comp_less<double>);
//	EXPECT_TRUE(std::is_sorted(vec1.begin(), vec1.end(), comp_less<double>));
//}
//
//TEST(Vector, Double_more)
//{
//	std::vector<double> vec1 = { 5.0, 8.0, 4.0, 12.0, 6.0, 3.0, 9.0 };
//	my_sort(vec1.begin(), vec1.end(), comp_more<double>);
//	EXPECT_TRUE(std::is_sorted(vec1.begin(), vec1.end(), comp_more<double>));
//}
//
//TEST(Deque, Char_less)
//{
//	std::deque<char> deq1 = { 'c', 'a', 'e', 'd', 'b' };
//	my_sort(deq1.begin(), deq1.end(), comp_less<char>);
//	EXPECT_TRUE(std::is_sorted(deq1.begin(), deq1.end(), comp_less<char>));
//}
//
//TEST(Deque, Double_more)
//{
//	std::deque<double> deq1 = { 3.0, 56.0, 12.0, 45.0, 33.0 };
//	my_sort(deq1.begin(), deq1.end(), comp_more<double>);
//	EXPECT_TRUE(std::is_sorted(deq1.begin(), deq1.end(), comp_more<double>));
//}
//
//TEST(STDArray, float)
//{
//	std::array<float, 5> ar = { 11.0, 5.0, 2.0, 34.0, 15.0 };
//	my_sort(ar.begin(), ar.end());
//	EXPECT_TRUE(std::is_sorted(ar.begin(), ar.end()));
//}
//
//TEST(String, string)
//{
//	std::string abc = "random";
//	my_sort(abc.begin(), abc.end());
//	EXPECT_TRUE(std::is_sorted(abc.begin(), abc.end()));
//}
//
//TEST(Policy, Auto)
//{
//	AutoPolicy p;
//	EXPECT_EQ(p.get_count_of_thread(100), 1);
//	EXPECT_EQ(p.get_count_of_thread(2000), 2);
//}

//TEST(BIGDATA, test)
//{
//	int size = 320;
//	int i = 0;
//	std::vector<int> arr;
//	while (i < size)
//	{
//		arr.push_back(std::rand());
//		++i;
//	}
//	my_sort(arr.begin(), arr.end(), comp_more<int>);
//	EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end(), comp_more<int>));
//}

//TEST(Policy, AutoPolicy)
//{
//	AutoPolicy policy;
//	EXPECT_EQ(policy.get_count_of_thread(100), 1);
//	EXPECT_EQ(policy.get_count_of_thread(2000), 2);
//	int size = 320;
//	int i = 0;
//	std::vector<int> arr;
//	while (i < size)
//	{
//		arr.push_back(std::rand());
//		++i;
//	}
//	my_sort(arr.begin(), arr.end(), comp_less<int>, std::move(policy));
//	EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
//}

TEST(Policy, CountThreadPolicy)
{
	CountThreadPolicy policy(3);
	int size = 320;
	int i = 0;
	std::vector<int> arr;
	while (i < size)
	{
		arr.push_back(std::rand());
		++i;
	}
	my_sort(arr.begin(), arr.end(), comp_less<int>, std::move(policy));
	EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

//TEST(Policy, OneThreadPolicy)
//{
//	OneThreadPolicy policy;
//	int size = 320;
//	int i = 0;
//	std::vector<int> arr;
//	while (i < size)
//	{
//		arr.push_back(std::rand());
//		++i;
//	}
//	my_sort(arr.begin(), arr.end(), comp_less<int>, std::move(policy));
//	EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
//}