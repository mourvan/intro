template <class T, class D>
class BinarySearchTree : public basic_tree<node_tr<T,D>> //TODO: Trie, AVL, Treap
{
	//void inorder_tree_walk_r(node_tr<T,D>* x);
	//void inorder_tree_walk_i();
	node_tr<T,D>* search_r(T key, node_tr<T,D>* ptr);
	node_tr<T,D>* search_i(T key);
	node_tr<T,D>* successor(node_tr<T,D>* x);
	node_tr<T,D>* predecessor(node_tr<T,D>* x);
	node_tr<T,D>* min(node_tr<T,D>* x); 			//min at subtree x
	node_tr<T,D>* max(node_tr<T,D>* x); 			//max at subtree x
	void insert(node_tr<T,D>* x);
	void remove(node_tr<T,D>* z);
	void transplant(node_tr<T,D>* u, node_tr<T,D>* v);

public:
	~BinarySearchTree();
	void Insert(T key, D data);
	bool Search(T key, D& data);
	bool Search_and_Delete(T key, D& data);
	bool Delete(T key);
	void inorder_tree_walk_i();
	void inorder_tree_walk_r(node_tr<T,D>* x);
};

template <class T, class D>
void BinarySearchTree<T,D>::transplant(node_tr<T,D>* u, node_tr<T,D>* v)
{
	if(u->parent == nullptr)
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
	if(v != nullptr)
	{
		v->parent = u->parent;
	}
}

template <class T, class D>
void BinarySearchTree<T,D>::remove(node_tr<T,D>* z)
{
	if(z->left == nullptr)
		transplant(z, z->right);
	else if(z->right == nullptr)
		transplant(z,z->right);
	else
	{
		node_tr<T,D>* y = min(z->right);
		if(y->parent != z)
		{
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z,y);
		y->left = z->left;
		y->left->parent = y;
	}
	delete z;
}

template <class T, class D>
bool BinarySearchTree<T,D>::Delete(T key)
{
	node_tr<T,D>* x = search_i(key);
	if(x == nullptr) 
	{
		return false;
	}
	else
	{
		remove(x);
		return true;
	}
}

template <class T, class D>
node_tr<T,D>* BinarySearchTree<T,D>::min(node_tr<T,D>* x)
{
	if(x == nullptr)
		return x;
	while(x->left != nullptr)
	{
		x = x->left;
	}
	return x;
}

template <class T, class D>
node_tr<T,D>* BinarySearchTree<T,D>::max(node_tr<T,D>* x)
{
	if(x == nullptr)
		return x;
	while(x->right != nullptr)
	{
		x = x->right;
	}
	return x;
}

template <class T, class D>
node_tr<T,D>* BinarySearchTree<T,D>::successor(node_tr<T,D>* x)
{
	if(x->right != nullptr)
	{
		return min(x->right);
	}
	node_tr<T,D>* y = x->parent;
	while (y != nullptr && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template <class T, class D>
node_tr<T,D>* BinarySearchTree<T,D>::predecessor(node_tr<T,D>* x)
{
	if(x->left != nullptr)
	{
		return max(x->left);
	}
	node_tr<T,D>* y = x->parent;
	while (y != nullptr && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template <class T, class D>
void BinarySearchTree<T,D>::insert(node_tr<T,D>* z)
{
	node_tr<T,D>* x, *y;
	x = this->root; y = nullptr;
	while(x != nullptr)
	{
		y = x;
		if(z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y == nullptr)
		this->root = z;
	else if(z->key < y->key)
		y->left = z;
	else
		y->right = z; 
}


template<class T, class D>
void BinarySearchTree<T,D>::inorder_tree_walk_r(node_tr<T,D>* x)
{
	if(x != nullptr)
	{
		//std::cout << x->key << " " << std::endl;
		inorder_tree_walk_r(x->left);
		//std::cout << x->key << " " << std::endl;
		inorder_tree_walk_r(x->right);
		std::cout << x->key << " " << std::endl;
	}
}


template<class T, class D>
node_tr<T,D>* BinarySearchTree<T,D>::search_r(T key, node_tr<T,D>* ptr)
{
	if(ptr == nullptr || ptr->key == key ) return ptr;
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
node_tr<T,D>* BinarySearchTree<T,D>::search_i(T key)
{
	node_tr<T,D>* x = this->root;
	while(x != nullptr && x->key != key)
	{
		if(key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	return x;
}


template<class T, class D>
bool BinarySearchTree<T,D>::Search(T key, D& data)
{
	node_tr<T,D>* x = search_i(key);
	if(x == nullptr)
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
bool BinarySearchTree<T,D>::Search_and_Delete(T key, D& data)
{
	node_tr<T,D>* x = search_i(key);
	if(x == nullptr)
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
void BinarySearchTree<T,D>::Insert(T key, D data)
{
	node_tr<T,D>* x = new node_tr<T,D>(key, data);
	insert(x);
	this->size++;
}

/*
template<class T, class D>
void BinarySearchTree<T,D>::inorder_tree_walk_i()
{

	//отматываем налево до упора, печатаем
	//если есть путь направо,уходим 1 раз направо и мотаем налево до упора
	//иначе, поднимаемся на родителя,печатаем родителя
	//если есть путь направо,уходим 1 раз направо и мотаем налево до упора

	if(this->root == nullptr)
	{
		return;
	}

	node_tr<T,D>* x = this->root;
	node_tr<T,D>* visited = nullptr;

	while(x->left != nullptr)
	{
			x = x->left;
	}
	std::cout << x->key << " ";
	//now x is the leftmost element

	for(int i = 0; i < 5; i++)
	{

		if(x->right != nullptr && (x->right != visited))
		{
			x = x->right;
			while(x->left != nullptr)
			{
				x = x->left;
			}
			std::cout << x->key << " ";
		}
		else //нужно понять, печатаем ли мы при поднятии
			 //если поднимаемся c правогосына на родителя - не печатаем
			 //если поднимаемся с левого сына на родителя - печатаем
			 //трекаем глубину?
		{	

			if(!(x->left == nullptr && x->right != nullptr))
				std::cout << x->key << " ";
			visited = x;
			x = x->parent;
		}
	}
}
*/

template<class T, class D>
void BinarySearchTree<T,D>::inorder_tree_walk_i()
{
	node_tr<T,D>* x = min(this->root);
	std::cout << x->key << std::endl;
	for(int i = 0; i < this->size-1; i++)
	{
		x = successor(x);
		if(x != nullptr)
		{
			std::cout << x->key << std::endl; 
		}
		else return;
	}
}

template <class T, class D>
node_tr<T,D>* find_leaf(node_tr<T,D>* x)
{
	while(x->left != nullptr || x->right != nullptr)
	{
		if(x->left != nullptr)
			x = x->left;
		else if(x->right != nullptr)
			x = x->right;
	}
	return x;
}

template <class T, class D>
BinarySearchTree<T,D>::~BinarySearchTree()
{
	node_tr<T,D>* x = nullptr;
	node_tr<T,D>* y = this->root;
	while(y != nullptr)
	{
		x = find_leaf(y);
		y = x->parent;
		if(y != nullptr)
		{
			if(x == y->left) 
				y->left = nullptr;
			else 
				y->right = nullptr;
		}
		delete x;
	}
}

