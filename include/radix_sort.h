
#include <cstring> 

template<class T> //works for ints, TODO template with unions to sort float, double
void radix_sort(std::vector<T>& arr)
{
	int size = arr.size();
	unsigned BIT_MASK = 0xf;   
	T mask = (T)BIT_MASK;
	for(int j = 0; j < sizeof(T)*2; j++)
	{
		//int size = arr.size();
		std::vector<int> c(16,0);
		std::vector<T> b(size);
		for(int i = 0; i < size; ++i)
		{
			c[(arr[i] & mask) >> (j*4)]++;
		}

		for(int i = 1; i <= 15; ++i)
		{
			c[i] = c[i] + c[i-1];
		}

		for(int i = size-1; i>=0; --i)
		{
			b[c[(arr[i] & mask) >> (j*4)]-1] = arr[i];
			c[(arr[i] & mask) >> (j*4)]--;
		}
		arr = b;
		mask = mask << 4;
	}
}

void radix_sort(std::vector<float>& arr)
{
	int size = arr.size();
	unsigned BIT_MASK = 0xff;   
	unsigned mask = BIT_MASK;
	for(int j = 0; j < (int)sizeof(float); j++)
	{
		//int size = arr.size();
		std::vector<int> c(256,0);
		std::vector<float> b(size);

		for(int i = 0; i < size; ++i)
		{
			float xd = arr[i];
		    union { unsigned temp; float f; } v;
		    v.f = xd;
			c[(v.temp & mask) >> (j*8)]++;
		}

		for(int i = 1; i <= 255; ++i)
		{
			c[i] = c[i] + c[i-1];
		}

		for(int i = size-1; i>=0; --i)
		{
			float xd = arr[i];
		    union { unsigned temp; float f; } v;
		    v.f = xd;
			b[c[(v.temp & mask) >> (j*8)]-1] = arr[i];
			c[(v.temp & mask) >> (j*8)]--;
		}
		arr = b;
		mask = mask << 8;
	}
}