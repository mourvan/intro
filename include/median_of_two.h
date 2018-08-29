

template <class T>
T median_of_two(std::vector<T>& x, std::vector<T>& y)
{
	int xn = x.size();
	int yn = y.size();
	while(xn > 0 && yn > 0 && xn < x.size() && yn < y.size())
	{
		if(x[xn/2] == y[yn/2])//continue to search in lower part of X and upper of Y
		{
			return x[xn/2];
		}
		else if(x[xn/2] > y[yn/2])
		{
			xn = xn/2;
			yn = yn+ yn/2;
		}
		else
		{
			xn = xn + xn/2;
			yn = yn/2;
		}
	}
}