#pragma once
#include <vector>

template <class T>
int binary_search_i(std::vector<T>& arr, T elem) //return index of element, -1 if not found
{
	int i = arr.size()/2, l = 0, r = arr.size()-1;
	while(r-l > 0)
	{
		if(arr[i] == elem)
		{
			return i;
		}
		else if (arr[i] > elem)
		{
			r = r/2;
			i = (l+r)/2;
		}
		else
		{
			l = i+1;
			i = (l+r)/2;
		}
	}
	if(arr[i] == elem)
		return i;
	else 
		return -1;
}

template <class T>
int binary_search_r(std::vector<T>& arr, T elem, int l, int r) //return index of element, -1 if not found
{
	int i = (l+r)/2;
	if (arr[i] == elem)
	{
		return i;
	}

	if (r-l > 0)
	{
		if (arr[i] > elem)
		{
			return binary_search_r(arr, elem, l, r/2);
		}
		else 
		{
			return binary_search_r(arr, elem, i+1, r);
		}
	}
	else 
	{
		return -1;
	}
}