template <class T, class D>
class HashTable
{
	std::vector<DLinkedList<T,D>> table;
	unsigned size; //size < 200.000
	unsigned hash(T key);
	unsigned hash(std::string key);
	unsigned a,b,p;
public:
	HashTable(unsigned ssize, unsigned prime = 224569);
	void Insert(T key, D data);
	bool Search(T key, D& data);
	bool Delete(T key);
};

template <class T, class D>
unsigned HashTable<T,D>::hash(T key) 
{
	//every key is from 0..p-1
	std::cout << "index is " <<((a*(unsigned)key+b)%p)%size << std::endl;
	return ((a*(unsigned)key+b)%p)%size;

}

template<class T, class D>
unsigned HashTable<T,D>::hash(std::string key)
{
	//stub
	return 0;
}

template <class T, class D>
HashTable<T,D>::HashTable(unsigned ssize, unsigned prime)  : table(ssize)
{
	//generate a from 1..p-1
	//generate b from 0..p-1
	size = ssize;
	p = prime;
	srand(time(NULL));
	a = (rand() % 224568)+1;
	b = rand() % 224569;
}

template <class T, class D>
void HashTable<T,D>::Insert(T key, D data)
{
	table[hash(key)].Insert(key, data);
}

template <class T, class D>
bool HashTable<T,D>::Search(T key, D& data)
{
	return table[hash(key)].Search(key, data);
}

template <class T, class D>
bool HashTable<T,D>::Delete(T key)
{
	return table[hash(key)].Delete(key);
}