#include <cmath>


void bucket_sort(std::vector<float>& arr)
{
	std::vector<std::vector<float> > b(arr.size());
	int n = arr.size();

	for(int i = 0; i < n; i++)
	{
		b[std::floor((float)n * arr[i])].push_back(arr[i]);
	}

	for(int i = 0; i < n; i++)
	{
		insertion_sort(b[i]);
	}

	int k = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < (int)b[i].size(); j++)
		{
			arr[k] = b[i][j];
			k++;
		}
	}
}