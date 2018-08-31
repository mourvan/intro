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