template <class T, class D>
struct node_ll
{
	T key;
	D data;
	node_ll<T,D>* next;
	node_ll<T,D>* prev;
	node_ll(T kkey, D ddata);
};

template <class T, class D>
node_ll<T,D>::node_ll(T kkey, D ddata)
{
	key = kkey;
	data = ddata;
}

template <class T, class D>
class DLinkedList
{
	node_ll<T,D>* head;
	int size;
	node_ll<T,D>* search(T key);
	void insert(node_ll<T,D>* x);
	void remove(node_ll<T,D>* x);
public:
	DLinkedList();
	~DLinkedList();
	void Insert(T key, D data);
	bool Delete(T key);
	bool Search(T key, D& data);
};

template <class T, class D>
void DLinkedList<T,D>::Insert(T key, D data)
{
	node_ll<T,D>* x = new node_ll<T,D>(key, data);
	insert(x);
	size++;
}

template <class T, class D>
bool DLinkedList<T,D>::Search(T key, D& data)
{
	node_ll<T,D>* x = search(key);
	if(x != nullptr)
	{
		data = x->data;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T, class D>
bool DLinkedList<T,D>::Delete(T key) //deletes first found element with such a key
{
	node_ll<T,D>* x = search(key);
	if(x != nullptr)
	{
		remove(x);
		size--;
		return true;
	}
	else
	{
		return false;
	}
}



template <class T, class D>
node_ll<T,D>* DLinkedList<T,D>::search(T key) //returns nullptr if not found
{
	node_ll<T,D>* x = head;
	while(x != nullptr && x->key != key)
	{
		x = x->next;
	}
	return x;
}

template <class T, class D>
void DLinkedList<T,D>::insert(node_ll<T,D>* x) //insert at head
{
	x->next = head;
	x->prev = nullptr;

	if(head != nullptr)
	{
		head->prev = x;
	}

	head = x;
}

template <class T, class D>
void DLinkedList<T,D>::remove(node_ll<T,D>* x)
{
	if(x->prev != nullptr)
	{
		x->prev->next = x->next;
	}
	else
	{
		head = x->next;
	}

	if(x->next != nullptr)
	{
		x->next->prev = x->prev;
	} 

	delete x;
}

template <class T, class D>
DLinkedList<T,D>::DLinkedList()
{
	head = nullptr;
	size = 0;
}

template <class T, class D>
DLinkedList<T,D>::~DLinkedList()
{
	while(head != nullptr)
	{
		node_ll<T,D>* x = head;
		head = head->next;
		delete x;
	}
}





