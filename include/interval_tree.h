template<class T> 
struct interval
{
	T low;
	T high;
	interval(T l, T h);
	interval() {}
};

template<class T>
interval<T>::interval(T l, T h) : low(l), high(h) {}

template <class T, class D>
struct node_it
{
	interval<T> in; //in.low == key
	T max;
	D data;

	node_it<T,D>* parent;
	node_it<T,D>* left;
	node_it<T,D>* right;
	bool color;

	node_it(interval<T> iin, D ddata);
	node_it(T low, T high, D ddata);
	node_it() {}
};

template <class T, class D>
node_it<T,D>::node_it(T low, T high, D ddata) : in(low,high), data(ddata)
{
	max = in.high;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = true;
}

template <class T, class D>
node_it<T,D>::node_it(interval<T> iin, D ddata) : in(iin), data(ddata)
{
	max = in.high;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = true;
}


template <class T, class D>
class IntervalTree : public basic_tree<node_it<T,D>> //TODO: pointer to last_searched?? to 
{
	node_it<T,D>* nil; //sentinel
	const bool red = true;
	const bool black = false;

	node_it<T,D>* find_leaf(node_it<T,D>* x);
	node_it<T,D>* search_r(interval<T> in, node_it<T,D>* ptr);
	node_it<T,D>* search_i(interval<T> in);
	node_it<T,D>* interval_search(interval<T> in);
	node_it<T,D>* successor(node_it<T,D>* x);
	node_it<T,D>* predecessor(node_it<T,D>* x);
	node_it<T,D>* min(node_it<T,D>* x); 			//min at subtree x
	node_it<T,D>* max(node_it<T,D>* x); 			//max at subtree x
	void insert(node_it<T,D>* x);
	void remove(node_it<T,D>* z);
	void left_rotate(node_it<T,D>* x);
	void right_rotate(node_it<T,D>* x);
	void IntervalTree_insert_fixup(node_it<T,D>* z);
	void IntervalTree_remove_fixup(node_it<T,D>* x);
	void transplant(node_it<T,D>* u, node_it<T,D>* v);

public:
	void inorder_tree_walk_i();
	IntervalTree();
	~IntervalTree();
	void Insert(T low, T high, D data);
	void Insert(interval<T> in, D data);
	bool Search(T low, T high, D& data);
	bool Search(interval<T> in, D& data);
	bool isOverlapped(interval<T>& in, D& data); //if node in the tree overlaps interval<T>in, returns true and changes in to be that intervalss
	//bool Search_and_Delete(T key, D& data);
	bool Delete(T low, T high);
	bool Delete(interval<T> in);

};

template<class T, class D>
void IntervalTree<T,D>::inorder_tree_walk_i()
{
	node_it<T,D>* x = min(this->root);
	for(int i = 0; i < this->size; i++)
	{
		if(x != nil)
		{
			std::cout << "[" << x->in.low << ", " << x->in.high << "]" << std::endl; 
		}
		else return;
		x = successor(x);
	}
}


template <class T, class D>
void IntervalTree<T,D>::transplant(node_it<T,D>* u, node_it<T,D>* v)
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
void IntervalTree<T,D>::left_rotate(node_it<T,D>* x) //assuming (x->right != NULL)
{
	node_it<T,D>* y = x->right;
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

	std::swap(y->max, x->max);
	x->max = std::max(std::max(x->max, x->in.high), std::max(x->left->max, x->right->max));
}

template <class T, class D>
void IntervalTree<T,D>::right_rotate(node_it<T,D>* x)
{
	node_it<T,D>* y = x->left;
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

	std::swap(y->max, x->max);
	x->max = std::max(std::max(x->max, x->in.high), std::max(x->left->max, x->right->max));
}

template <class T, class D>
void IntervalTree<T,D>::insert(node_it<T,D>* z)
{
	node_it<T,D>* x, *y;
	x = this->root; y = nil;
	while(x != nil)
	{
		if(z->in.high > x->max)
		{
			x->max = z->in.high;
		}
		y = x;
		if(z->in.low < x->in.low)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y == nil)
		this->root = z;
	else if(z->in.low < y->in.low)
		y->left = z;
	else
		y->right = z; 
	z->left = nil;
	z->right = nil;
	z->color = red;
	IntervalTree_insert_fixup(z);
}

template <class T, class D>
void IntervalTree<T,D>::IntervalTree_insert_fixup(node_it<T,D>* z)
{
	while(z->parent->color == red)
	{
		if(z->parent == z->parent->parent->left)
		{
			node_it<T,D>*y = z->parent->parent->right;
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
			node_it<T,D>*y = z->parent->parent->left;
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
void IntervalTree<T,D>::remove(node_it<T,D>* z)
{
	bool y_orig_color;
	node_it<T,D>* x,*y;
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
		IntervalTree_remove_fixup(x);
	}
	delete z;
}

template <class T, class D>
void IntervalTree<T,D>::IntervalTree_remove_fixup(node_it<T,D>* x)
{
	node_it<T,D>* w;
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
bool IntervalTree<T,D>::Delete(T low, T high)
{
	interval<T> in(low, high);
	node_it<T,D>* x = search_i(in);
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
bool IntervalTree<T,D>::Search(T low, T high, D& data)
{
	interval<T> in(low,high);
	node_it<T,D>* x = search_i(in);
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
bool IntervalTree<T,D>::Search(interval<T> in, D& data)
{
	node_it<T,D>* x = search_i(in);
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
void IntervalTree<T,D>::Insert(T low, T high, D data)
{
	node_it<T,D>* x = new node_it<T,D>(low, high, data);
	insert(x);
	this->size++;
}

template<class T, class D>
void IntervalTree<T,D>::Insert(interval<T> in, D data)
{
	node_it<T,D>* x = new node_it<T,D>(in, data);
	insert(x);
	this->size++;
}



template <class T, class D>
IntervalTree<T,D>::IntervalTree()
{
	nil = new node_it<T,D>;
	nil->color = black;
	nil->max = std::numeric_limits<T>::lowest();
	this->root = nil;

}

template <class T, class D>
node_it<T,D>* IntervalTree<T,D>::find_leaf(node_it<T,D>* x)
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
IntervalTree<T,D>::~IntervalTree()
{
	node_it<T,D>* x = nil;
	node_it<T,D>* y = this->root;
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
node_it<T,D>* IntervalTree<T,D>::min(node_it<T,D>* x)
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
node_it<T,D>* IntervalTree<T,D>::max(node_it<T,D>* x)
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
node_it<T,D>* IntervalTree<T,D>::successor(node_it<T,D>* x)
{
	if(x->right != nil)
	{
		return min(x->right);
	}
	node_it<T,D>* y = x->parent;
	while (y != nil && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template <class T, class D>
node_it<T,D>* IntervalTree<T,D>::predecessor(node_it<T,D>* x)
{
	if(x->left != nil)
	{
		return max(x->left);
	}
	node_it<T,D>* y = x->parent;
	while (y != nil && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template<class T, class D>
node_it<T,D>* IntervalTree<T,D>::search_r(interval<T> in, node_it<T,D>* ptr)
{
	if(ptr == nil || ptr->in == in) return ptr;
	if(in.low < ptr->in.low)
	{
		return search(in, ptr->left);
	}
	else
	{
		return search(in, ptr->right);
	}
}

template<class T, class D>
node_it<T,D>* IntervalTree<T,D>::search_i(interval<T> in)
{
	node_it<T,D>* x = this->root;
	while(x != nil && x->in != in)
	{
		if(in.low > x->in.low)
			x = x->right;
		else
			x = x-> left;
	}
	return x;
}

template<class T, class D>
node_it<T,D>* IntervalTree<T,D>::interval_search(interval<T> in) //returns pointer to overlapping interval or nil
{
	node_it<T,D>* x = this->root;
	while(x != nil && !(in.low <= x->in.high && x->in.low <= in.high)) //does not overlap  //i:low   i0:high and i0:low   i:high
	{
		if(x->left != nil && x->left->max >= in.low)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template<class T, class D>
bool IntervalTree<T,D>::isOverlapped(interval<T>& in, D& data)
{
	node_it<T,D>* x = interval_search(in);
	if(x == nil)
	{
		return false;
	}
	else
	{
		in = x->in;
		data = x->data;
		return true;
	}
}