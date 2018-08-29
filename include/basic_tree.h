template <class T, class D>
struct node_tr
{
	T key;
	D data;
	node_tr<T,D>* parent;
	node_tr<T,D>* left;
	node_tr<T,D>* right;
	node_tr();
	node_tr(T kkey, D ddata);
};

template <class T, class D>
node_tr<T,D>::node_tr(T kkey, D ddata)
{
	key = kkey;
	data = ddata;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

template <class T, class D>
node_tr<T,D>::node_tr()
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

template <class T>
class basic_tree
{
protected:
	T* root;
	unsigned size;
public:
	basic_tree();
	unsigned Size() const;
};

template<class T>
unsigned basic_tree<T>::Size() const
{
	return size;
}

template <class T>
basic_tree<T>::basic_tree() : root(nullptr), size(0) {}