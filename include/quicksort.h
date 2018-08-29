

template<class T>
int partition(std::vector<T>& arr, int l, int r)
{
	T x = arr[r]; //select arr[r] as pivot element, then compute its position
	int i = l-1;
	for(int j=l; j<r; ++j)
	{
		if(arr[j] <= x)
		{
			i++;
			std::swap(arr[i],arr[j]);
		}	
	}
	std::swap(arr[i+1],arr[r]);
	return i+1;
}

template<class T>
void quicksort(std::vector<T>& arr, int l, int r)
{
	if(l < r)
	{
		int q = partition(arr,l,r);
		quicksort(arr,l,q-1);
		quicksort(arr,q+1,r);
	}
}

template<class T>
void Quicksort(std::vector<T>& arr)
{
	quicksort(arr, 0, arr.size()-1);
}

template<class T>
int randomised_partition(std::vector<T>& arr, int l, int r)
{
	int i = (rand()%(r-l+1))+l; 
	std::swap(arr[r], arr[i]);
	return partition(arr,l,r);
}

template<class T>
void randomised_quicksort(std::vector<T>& arr, int l, int r)
{
	if(l < r)
	{
		int q = randomised_partition(arr,l,r);
		randomised_quicksort(arr,l,q-1);
		randomised_quicksort(arr,q+1,r);
	}
}

template<class T>
void RandomQuicksort(std::vector<T>& arr)
{
	randomised_quicksort(arr, 0, arr.size()-1);
}



