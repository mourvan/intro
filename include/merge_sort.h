#pragma once
#include <vector>

template <class T>
std::vector<T> merge(std::vector<T>& a, std::vector<T>& b)
{
	std::vector<T> res(a.size()+b.size());
	int ai=0;
	int bi=0;
	int i;

	for(i = 0; i < res.size() && bi<b.size() && ai<a.size(); i++)
	{
		if(a[ai] < b[bi])
		{
			res[i] = a[ai];
			ai++;
		}
		else
		{
			res[i] = b[bi];
			bi++;
		}
	}

	for(; i < res.size(); i++)
	{
		if(bi < b.size())
		{
			res[i] = b[bi];
			bi++;
		}
		else
		{
			res[i] = a[ai];
			ai++;
		}
	}
	return res;
}


template <class T>
void merge_sort(std::vector<T>& a)
{
	if(a.size() > 1)
	{
		int q = a.size()/2;
		std::vector<T> a1(&a[0],&a[q]);
		std::vector<T> a2(&a[q],&a[a.size()]);
		merge_sort(a1);
		merge_sort(a2);
		a = merge(a1, a2);
	}
}