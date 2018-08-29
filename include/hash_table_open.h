template <class T, class D>
struct node_oa
{
	T key;
	D data;
	bool deleted;
	bool free;
	node_oa() : deleted(false), free(true) {}
	node_oa(T kkey, D ddata) :  key(kkey), data(ddata), free(false) {}
};


template <class T, class D>
class HashTable_OA
{
	std::vector<node_oa<T,D>> table;
	unsigned size; //size < 200.000
	unsigned hash(T key, unsigned attempt);
	unsigned hash1(T key);
	unsigned hash2(T key);
	unsigned a1,b1,a2,b2,p;
public:
	HashTable_OA(unsigned ssize, unsigned prime = 224569);
	bool Insert(T key, D data);
	bool Search(T key, D& data);
	bool Delete(T key);
};


template <class T, class D>
HashTable_OA<T,D>::HashTable_OA(unsigned ssize, unsigned prime)  : table(ssize)
{
	//generate a from 1..p-1
	//generate b from 0..p-1
	size = ssize;
	p = prime;
	srand(time(NULL));
	a1 = (rand() % (p-1))+1;
	b1 = rand() % p;
	a2 = (rand() % (p-1))+1;
	b2 = rand() % p;
}

template <class T, class D>
unsigned HashTable_OA<T,D>::hash1(T key) 
{
	//every key is from 0..p-1
	//std::cout << "index is " <<((a1*(unsigned)key+b1)%p)%size << std::endl;
	return ((a1*(unsigned)key+b1)%p)%size;

}

template <class T, class D>
unsigned HashTable_OA<T,D>::hash2(T key) 
{
	//every key is from 0..p-1
	//std::cout << "index is " <<((a2*(unsigned)key+b2)%p)%size << std::endl;
	return ((a2*(unsigned)key+b2)%p)%size;

}

template <class T, class D>
unsigned HashTable_OA<T,D>::hash(T key, unsigned attempt) 
{
	
	return (hash1(key) + attempt*hash2(key)) % size;

}


template <class T, class D>
bool HashTable_OA<T,D>::Insert(T key, D data)
{
	unsigned i = 0;
	while(i < size)
	{
		unsigned j = hash(key,i);
		if(table[j].free || table[j].deleted)
		{
			table[j] = node_oa<T,D>(key,data);

			return true;
		}
		else
		{
			i++;
		}
	}
	return false;
}

template <class T, class D>
bool HashTable_OA<T,D>::Search(T key, D& data)
{
	unsigned i = 0;
	unsigned j;
	do
	{
		j = hash(key, i);
		if(table[j].key == key)
		{
			data = table[j].data;
			return true;
		}
		i++;
	}
	while(i < size && table[j].free == false);
	return false;
}

template <class T, class D>
bool HashTable_OA<T,D>::Delete(T key)
{
	unsigned i = 0;
	unsigned j;
	do
	{
		j = hash(key, i);
		if(table[j].key == key)
		{
			table[j].deleted = true;
			return true;
		}
		i++;
	}
	while(i < size && table[j].free == false);
	return false;
}