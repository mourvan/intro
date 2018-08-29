

template<class T>
class Heap
{
public:
	std::vector<T> heap; //heap[0] - unused;
	int heap_size;
	int Parent(int i);
	int LeftChild(int i);
	int RightChild(int i);
	void MaxHeapify(int i);
	void MinHeapify(int i);
	void BuildMaxHeap();
	void BuildMinHeap();
public:
	std::vector<T> Sort();
	Heap(std::vector<T>& array);
};

template<class T>
Heap<T>::Heap(std::vector<T>& array)
{
	T temp = 0;
	heap.push_back(temp);
	heap.insert(heap.end(), array.begin(), array.end());
	heap_size = heap.size()-1;

}

template<class T>
std::vector<T> Heap<T>::Sort()
{
	BuildMaxHeap();
	for(int i = heap.size()-1; i >= 2; --i)
	{
		std::swap(heap[1],heap[i]);
		--heap_size;
		MaxHeapify(1);
	}
	return std::vector<T>(heap.begin()+1, heap.end());
}




template<class T>
int Heap<T>::Parent(int i) //macros?
{
	return (i/2);
}


template<class T>
int Heap<T>::LeftChild(int i)
{
	return (2*i);
}


template<class T>
int Heap<T>::RightChild(int i)
{
	return (2*i+1);
}


template<class T>
void Heap<T>::MaxHeapify(int i)
{
	//assuming left and right subtrees are maintaining max-heap property
	int l = LeftChild(i);
	int r = RightChild(i);
	int largest = i;

	if(l <= heap_size && heap[l] > heap[i])
	{
		largest = l;
	}

	if(r <= heap_size && heap[r] > heap[largest])
	{
		largest = r;
	}

	if(largest != i)
	{
		std::swap(heap[largest],heap[i]);
		MaxHeapify(largest);
	}
}


template<class T>
void Heap<T>::MinHeapify(int i)
{
	//smallest must be on top
	//assuming subtrees rooted at l and r are min-heaps
	//element at i might be bigger than 
	int l = LeftChild(i);
	int r = RightChild(i);
	int smallest = i;

	if(l <= heap_size && heap[l] < heap[i])
	{
		smallest = l;
	}

	if(r <= heap_size && heap[r] < heap[smallest])
	{
		smallest = r;
	}

	if(smallest != i)
	{
		std::swap(heap[smallest],heap[i]);
		MinHeapify(smallest);
	}

}

template<class T>
void Heap<T>::BuildMaxHeap()
{
	for(int i = (heap_size)/2; i>=1; --i)
	{
		MaxHeapify(i);
	} 
}


template<class T>
void HeapSort(std::vector<T>& array)
{
	Heap<T> h(array);
	array = h.Sort();
}

