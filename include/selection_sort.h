
template <class T>
void selection_sort(std::vector<T>& arr)
{
	int n = arr.size();					//
	for(int i = 0; i < n-1; i++) 		//	always n-1
	{									//
		int min = i;    				//	always n-1
		for(int j = i+1; j < n; j++)	//	(n-1) + (n-2) + (n-3) + ... + 1 == 1/2 * (n-2)* (n-1)
		{								//
			if(arr[j] < arr[min])		//
				min = j;				//
		}								//
		T temp = arr[i];				//
		arr[i] = arr[min];				//
		arr[min] = temp;				//
	}
}

/* Why does it need to run for only the first n   1 elements, rather than for all n elements? */
	/* - because last element remaining is always the biggest - */

/* Give the best-case and worst-case running times of selection sort in ‚O-notation. */
	/*Best case = worst case* = O-(n^2) */ 
