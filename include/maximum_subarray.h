

#include <vector>

template <class T>
T maximum_subarray(std::vector<T>& arr)
{
	T max = 0,curr = 0;
	int ml=0,mr=0,cl=0,cr=0;
	for(int i = 0; i < arr.size(); i++)
	{
		curr = curr + arr[i];

		if(curr >=0) //shift right border
		{
			cr++;
		}
		else //reinitialise left border and nullify sum
		{
			cl = i+1;
			curr = 0;
		}


		if (curr > max)
		{
			max = curr;
			ml = cl;
			mr = cr;
		}	

	}
	return max;
}

template <class T>
T maximum_subarray_bruteforce(std::vector<T>& arr)
{
	T max = 0;
	for (int i = 0; i < arr.size(); i++) //begin of array
	{
		T sum = 0;
		for (int j = i; j < arr.size(); j++)
		{
			sum = sum + arr[j];
			if (sum > max)
				max = sum;
		}
	}
	return max;
}



