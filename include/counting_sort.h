

std::vector<int> counting_sort(std::vector<int> arr, int range)
{
	int size = arr.size();
	std::vector<int> c(range+1,0);
	std::vector<int> b(size);
	for(int i = 0; i < size; ++i)
	{
		c[arr[i]]++;
	}

	for(int i = 1; i <= range; ++i)
	{
		c[i] = c[i] + c[i-1];
		/*
		now c[i] shows how much elements are 
		less than i
		*/
	}

	for(int i = size-1; i>=0; --i)
	{
		b[c[arr[i]]-1] = arr[i];
		c[arr[i]]--;
	}

	return b;
}

void simple_counting_sort(std::vector<int>& arr, int range)
{
	int size = arr.size();
	std::vector<int> c(range+1,0);
	for(int i = 0; i < size; ++i)
	{
		c[arr[i]]++;
	}

	int j = 0;
	for (int i = 0; i <= range; ++i)
	{
		while(c[i] > 0)
		{
			arr[j] = i;
			++j;
			c[i]--;
		}
	}
}


int integers_in_range(int a, int b, std::vector<int>& arr, int range)
{
	int size = arr.size();
	std::vector<int> c(range+1,0);

	for(int i = 0; i < size; ++i)
	{
		c[arr[i]]++;
	}

	for(int i = 1; i <= range; ++i)
	{
		c[i] = c[i] + c[i-1];
		/*
		now c[i] shows how much elements are 
		less or equal than i
		*/
	}
	if(a==0)
		return c[b];
	else
		return (c[b] - c[a-1]);
}


