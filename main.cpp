/********************************/
/*  INTRODUCTION TO ALGORITMS   */
/*                              */
/********************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#include "include/everything.h"

using namespace std;

template<class T>
void print_vector(vector<T>& arr)
{
	for(int i = 0; i < arr.size(); ++i)
		cout << arr[i] << " ";
	cout << endl;
}


int main()
{
	vector<long long int> arr = {0,3,5,2,4,7,4,1,9,8,7,6,5,4,3,2,1,9,8,7,6,5,4,3,2,1,9,8,7,6};
	vector<int> arr1 = {9,8,7,6,5,4,3,2,1};
	vector<int> arr2 = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	vector<float> arr3 = {0.02f,0.47f,0.113445f,0.5754f,0.874f,0.6f,0.11f};
	//print_vector(arr);
	//insertion_sort(arr);
	//merge_sort(arr);
	//selection_sort(arr1);
	//HeapSort(arr);
	//RandomQuicksort(arr2);
	//simple_counting_sort(arr1,9);
	//arr = counting_sort(arr,9);
	//cout << integers_in_range(1,4,arr,9) << " integers in range" << endl;
	//bucket_sort(arr3);
	//radix_sort(arr);


	//print_vector(arr);


	
	//int data;
	//int* data1 = new int;
	//int* data2 = new int;
	//int* data3 = new int;
	/*
	DLinkedList<int, int*> lst;
	lst.Insert(1, data1);
	lst.Insert(2, data2);
	lst.Insert(3, data3);

	if(lst.Search(1, data1) == true)
	{
		cout << data1 << endl;
	}
	else
	{
		cout << "not found" << endl;
	}

	if(lst.Delete(1) == true)
	{
		cout << "deleted" << endl;
	}
	else
	{
		cout << "not deleted" << endl;
	}
	

	*/

	/*
	HashTable_OA<float, int*> t(100000);
	for(int i = 0; i < 50000; i++)
		t.Insert(i, data1);

	if(t.Search(41, data1) == true)
	{
		cout << data1 << endl;
	}
	else
	{
		cout << "not found" << endl;
	}

	if(t.Delete(41) == true)
	{
		cout << "deleted" << endl;
	}
	else
	{
		cout << "not deleted" << endl;
	}
	*/


	srand(time(NULL));
	//BinarySearchTree<int, int> tr;
	OSTree<int, int> tr;
	std::vector<int> lol= {10,8 ,12,7,9 ,11,13};
	std::vector<int> kek= {14,16,13,8,20,12,19};
	for(int i = 0; i < (int)lol.size(); i++)
	{
		tr.Insert(lol[i], lol[i]);
	}
	for(int i = 0; i < (int)lol.size(); i++)
	{
	//	cout << tr.Rank(lol[i]) << endl;
	}

	BSAUTree<int,int> at;
	for(int i = 0; i < (int)lol.size(); i++)
	{
		at.Insert(lol[i], lol[i]);
	}
	at.inorder_tree_walk_i();

	IntervalTree<int,int> it;
	for(int i = 0; i < (int)lol.size(); i++)
	{
		it.Insert(lol[i],kek[i],lol[i]);
	}
	it.inorder_tree_walk_i();
	interval<int> in(3,4);
	if(it.isOverlapped(in, kek[1]))
		cout << "is overlapped" << endl;
	else
		cout << "not overlapped" << endl;
	//RBTree<int, int> rbt;

	//tr.inorder_tree_walk_i();

	//cout << maximum_subarray(arr2) << endl;
	//cout << maximum_subarray_bruteforce(arr2) << endl;
	//cout << binary_search_i(arr1, 7) << endl;
	//cout << binary_search_r(arr1, 12, 0, arr1.size()-1) << endl;

	return 0;
}