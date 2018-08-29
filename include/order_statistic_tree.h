
template <class T, class D>
struct node_os
{
	T key;
	D data;
	node_os<T,D>* parent;
	node_os<T,D>* left;
	node_os<T,D>* right;
	node_os(T kkey, D ddata);
	node_os();
	bool color;
	unsigned size;
};

template <class T, class D>
node_os<T,D>::node_os(T kkey, D ddata)
{
	key = kkey;
	data = ddata;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = true;
	size = 1;
}

template <class T, class D>
node_os<T,D>::node_os() {}


template <class T, class D>
class OSTree : public basic_tree<node_os<T,D>> //TODO: pointer to last_searched?? to 
{
	node_os<T,D>* nil; //sentinel
	static const bool red = true;
	static const bool black = false;

	node_os<T,D>* find_leaf(node_os<T,D>* x);
	node_os<T,D>* search_r(T key, node_os<T,D>* ptr);
	node_os<T,D>* search_i(T key);
	node_os<T,D>* successor(node_os<T,D>* x);
	node_os<T,D>* predecessor(node_os<T,D>* x);
	node_os<T,D>* min(node_os<T,D>* x); 			//min at subtree x
	node_os<T,D>* max(node_os<T,D>* x); 			//max at subtree x
	void insert(node_os<T,D>* x);
	void remove(node_os<T,D>* z);
	void left_rotate(node_os<T,D>* x);
	void right_rotate(node_os<T,D>* x);
	void OSTree_insert_fixup(node_os<T,D>* z);
	void OSTree_remove_fixup(node_os<T,D>* x);
	void transplant(node_os<T,D>* u, node_os<T,D>* v);
	node_os<T,D>* select(node_os<T,D>* x, unsigned i); //node with rank i
	unsigned rank(node_os<T,D>* x);

public:
	void inorder_tree_walk_i();
	OSTree();
	~OSTree();
	void Insert(T key, D data);
	bool Search(T key, D& data);
	bool Search_and_Delete(T key, D& data);
	bool Delete(T key);  //not working atm
	T Select(unsigned i, D& data);
	unsigned Rank(T key);

};

template<class T, class D>
unsigned OSTree<T,D>::rank(node_os<T,D>* x)
{
	unsigned r = x->left->size + 1;
	while(x != this->root)
	{
		if(x == x->parent->right)
		{
			r = r + x->parent->left->size + 1;
		}
		x = x->parent;
	}
	return r;
}

template<class T, class D>
unsigned OSTree<T,D>::Rank(T key)
{
	node_os<T,D>* x = search_i(key);
	if(x == nil)
	{
		std::cout << "not found" << std::endl;
		return 0;
	}
	else
	{
		return rank(x);
	}
}

template<class T, class D>
T OSTree<T,D>::Select(unsigned i, D& data)
{
	node_os<T,D>* x = select_i(this->root, i);
}

template<class T, class D>
node_os<T,D>* select_r(node_os<T,D>* x, unsigned i)
{
	unsigned r = x->left->size + 1;
	if(r == i)
	{
		return x;
	}
	else if(i < r)
	{
		return select(x->left, i);
	}
	else
	{
		return select(x->right, i - r);
	}
}

template<class T, class D>
node_os<T,D>* select_i(node_os<T,D>* x, unsigned i)
{
	unsigned r = x->left->size + 1;
	while(r != i)
	{
		if(r > i)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
			r = i - r;
		}
	}
	return x;
}

template<class T, class D>
void OSTree<T,D>::inorder_tree_walk_i()
{
	node_os<T,D>* x = min(this->root);
	std::cout << x->key << std::endl;
	for(int i = 0; i < this->size-1; i++)
	{
		x = successor(x);
		if(x != nil)
		{
			std::cout << x->key << std::endl; 
		}
		else return;
	}
}


template <class T, class D>
void OSTree<T,D>::transplant(node_os<T,D>* u, node_os<T,D>* v)
{
	if(u->parent == nil)
	{
		this->root = v;
	}
	else if(u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

template <class T, class D>
void OSTree<T,D>::left_rotate(node_os<T,D>* x) //assuming (x->right != NULL)
{
	node_os<T,D>* y = x->right;
	x->right = y->left;
	if(y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if(x->parent == nil)
		this->root = y;
	else if(x->parent->left == x)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

template <class T, class D>
void OSTree<T,D>::right_rotate(node_os<T,D>* x)
{
	node_os<T,D>* y = x->left;
	x->left = y->right;
	if(y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if(x->parent == nil)
		this->root = y;
	else if(x->parent->right == x)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

template <class T, class D>
void OSTree<T,D>::insert(node_os<T,D>* z)
{
	node_os<T,D>* x, *y;
	x = this->root; y = nil;
	while(x != nil)
	{
		x->size++;
		y = x;
		if(z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y == nil)
		this->root = z;
	else if(z->key < y->key)
		y->left = z;
	else
		y->right = z; 
	z->left = nil;
	z->right = nil;
	z->color = red;
	z->size = 1;
	OSTree_insert_fixup(z);
}

template <class T, class D>
void OSTree<T,D>::OSTree_insert_fixup(node_os<T,D>* z)
{
	while(z->parent->color == red)
	{
		if(z->parent == z->parent->parent->left)
		{
			node_os<T,D>*y = z->parent->parent->right;
			if(y->color == red)
			{
				z->parent->color = black;
				y->color = black;
				z->parent->parent->color = red;
				z = z->parent->parent;
			}
			else 
			{
				if(z == z->parent->right)
				{
					z = z->parent;
					left_rotate(z);
				}
				//else??
				z->parent->color = black;
				z->parent->parent->color = red;
				right_rotate(z->parent->parent);
			}
		}
		else
		{
			node_os<T,D>*y = z->parent->parent->left;
			if(y->color == red)
			{
				z->parent->color = black;
				y->color = black;
				z->parent->parent->color = red;
				z = z->parent->parent;
			}
			else 
			{
				if(z == z->parent->left)
				{
					z = z->parent;
					right_rotate(z);
				}
				//else??
				z->parent->color = black;
				z->parent->parent->color = red;
				left_rotate(z->parent->parent);
			}
		}
	}
	this->root->color = black;
}

template <class T, class D>
void OSTree<T,D>::remove(node_os<T,D>* z)
{
	bool y_orig_color;
	node_os<T,D>* x,*y;
	y = z;
	y_orig_color = y->color;
	if(z->left == nil)
	{
		x = z->right;
		transplant(z, z->right);
	}
	else if (z->right == nil)
	{
		x = z->left;
		transplant(z,z->left);
	}
	else
	{
		y = min(z->right);
		y_orig_color = y->color;
		x = y->right;
		if(y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z,y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if(y_orig_color == black)
	{
		OSTree_remove_fixup(x);
	}
	delete z;
}

template <class T, class D>
void OSTree<T,D>::OSTree_remove_fixup(node_os<T,D>* x)
{
	node_os<T,D>* w;
	while(x != this->root && x->color == black)
	{
		if(x == x->parent->left)
		{
			w = x->parent->right;
			if(w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				left_rotate(x->parent);
				w = x->parent->right;
			}
			if(w->left->color == black && w->right->color == black)
			{
				w->color = red;
				x = x->parent;
			}
			else
			{
				if(w->right->color == black)
				{
					w->left->color = black;
					w->color = red;
					right_rotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = black;
				w->right->color = black;
				left_rotate(x->parent);
				x = this->root;
			}
		}
		else
		{
			w = x->parent->left;
			if(w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				right_rotate(x->parent);
				w = x->parent->left;
			}
			if(w->right->color == black && w->left->color == black)
			{
				w->color = red;
				x = x->parent;
			}
			else
			{
				if(w->left->color == black)
				{
					w->right->color = black;
					w->color = red;
					left_rotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = black;
				w->left->color = black;
				right_rotate(x->parent);
				x = this->root;
			}
		}
	}
	x->color = black;
}

template <class T, class D>
bool OSTree<T,D>::Delete(T key)
{
	node_os<T,D>* x = search_i(key);
	if(x == nil) 
	{
		return false;
	}
	else
	{
		remove(x);
		return true;
	}
}

template<class T, class D>
bool OSTree<T,D>::Search(T key, D& data)
{
	node_os<T,D>* x = search_i(key);
	if(x == nil)
	{
		return false;
	}
	else
	{
		data = x->data;
		return true;
	}
}


template<class T, class D>
bool OSTree<T,D>::Search_and_Delete(T key, D& data)
{
	node_os<T,D>* x = search_i(key);
	if(x == nil)
	{
		return false;
	}
	else
	{
		data = x->data;
		remove(x);
		return true;
	}
}

template<class T, class D>
void OSTree<T,D>::Insert(T key, D data)
{
	node_os<T,D>* x = new node_os<T,D>(key, data);
	insert(x);
	this->size++;
}

template <class T, class D>
OSTree<T,D>::OSTree()
{
	nil = new node_os<T,D>;
	nil->color = black;
	nil->size = 0;
	this->root = nil;
}

template <class T, class D>
node_os<T,D>* OSTree<T,D>::find_leaf(node_os<T,D>* x)
{
	while(x->left != nil || x->right != nil)
	{
		if(x->left != nil)
			x = x->left;
		else if(x->right != nil)
			x = x->right;
	}
	return x;
}

template <class T, class D>
OSTree<T,D>::~OSTree()
{
	node_os<T,D>* x = nil;
	node_os<T,D>* y = this->root;
	while(y != nil)
	{
		x = find_leaf(y);
		y = x->parent;
		if(y != nil)
		{
			if(x == y->left) 
				y->left = nil;
			else 
				y->right = nil;
		}
		delete x;
	}
	delete nil;
}

template <class T, class D>
node_os<T,D>* OSTree<T,D>::min(node_os<T,D>* x)
{
	if(x == nil)
		return x;
	while(x->left != nil)
	{
		x = x->left;
	}
	return x;
}

template <class T, class D>
node_os<T,D>* OSTree<T,D>::max(node_os<T,D>* x)
{
	if(x == nil)
		return x;
	while(x->right != nil)
	{
		x = x->right;
	}
	return x;
}

template <class T, class D>
node_os<T,D>* OSTree<T,D>::successor(node_os<T,D>* x)
{
	if(x->right != nil)
	{
		return min(x->right);
	}
	node_os<T,D>* y = x->parent;
	while (y != nil && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template <class T, class D>
node_os<T,D>* OSTree<T,D>::predecessor(node_os<T,D>* x)
{
	if(x->left != nil)
	{
		return max(x->left);
	}
	node_os<T,D>* y = x->parent;
	while (y != nil && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template<class T, class D>
node_os<T,D>* OSTree<T,D>::search_r(T key, node_os<T,D>* ptr)
{
	if(ptr == nil || ptr->key == key ) return ptr;
	if(key < ptr->key)
	{
		return search_r(key, ptr->left);
	}
	else
	{
		return search_r(key, ptr->right);
	}
}

template<class T, class D>
node_os<T,D>* OSTree<T,D>::search_i(T key)
{
	node_os<T,D>* x = this->root;
	while(x != nil && x->key != key)
	{
		if(key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	return x;
}