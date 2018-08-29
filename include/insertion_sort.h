#include <vector>

template <class T>
void insertion_sort(std::vector<T>& a)
{
	for(int i = 1; i < (int)a.size(); ++i) //insert a[i] into sorted array
	{
		T key = a[i];
		int j = i-1;
		while (j >= 0 && a[j] > key)
		{
			//sliding
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
	}
}