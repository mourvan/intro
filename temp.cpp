#include <iostream>

template <class T>
struct Pointers
{
	T* left;
	T* right;
	T* parent;
};

template <class T, class D>
struct Node_tr : public Pointers<Node_tr<T,D>>
{
	T key;
	D data;
};

template<class T, class D>
struct Node_rb : public Node_tr<T,D>, public Pointers<Node_rb<T,D>>
{
	bool color;
};

template<class T, class D>
struct Node_ost : Node_rb<T,D>,public Pointers<Node_ost<T,D>>
{
	int size;
};

int main()
{
	std::cout << "sizeof(Node_tr) is " << sizeof(Node_tr<int,int>) << std::endl;
	std::cout << "sizeof(Node_rb) is " << sizeof(Node_rb<int,int>) << std::endl;
	std::cout << "sizeof(Node_ost) is " << sizeof(Node_ost<int,int>) << std::endl;

	//Node_ost<int, int> lol;
	//std::
	//lol.Node_tr::left = nullptr;
}