#pragma once
#include <iostream>
namespace mine 
{
	template <typename T>
	struct ListNode
	{
		ListNode(const T& e) : data(e), next(0), prev(0) {}
		T data;
		ListNode<T>* next;
		ListNode<T>* prev;
	};

	template <typename T>
	class list
	{
	public:
		//ITERATOR SUB-CLASS
		class iterator
		{
		public:
			iterator(ListNode<T>* p = 0);
			T& operator*();
			T* operator->();
			iterator& operator++();
			iterator& operator++(int);
			iterator& operator--();
			iterator& operator--(int);
			bool operator!=(const iterator& compare);
			bool operator==(const iterator& compare);
		private:
			ListNode<T>* it_pos;
		};
		//LIST
		//CONSTRUCTOR - DESTRUCTORS
		list() : head_(0), tail_(0), size_(0) {}
		list(typename mine::list<T>::iterator&& begin_, typename mine::list<T>::iterator&& end_);
		//list(std::vector<T>& vec);
		// r values
		//list(typename std::vector<T>::iterator&& itB, typename std::vector<T>::iterator&& itE);
		~list();
		//queries
		void display();
		int size() { return size_; }
		T& front();
		T& back();
		iterator begin();
		iterator end();
		bool empty();
		//list methods
		void insert(const T& data, ListNode<T>* pos);
		void remove(ListNode<T>* pos);
		void push_back(const T& e);
		void push_front(const T& e);
		void pop_back();
		void pop_front();
		/*print the list*/
		/*destructor*/
		void printList();
		bool search(const T& e);

	private:
		ListNode<T>* head_;
		ListNode<T>* tail_;
		int size_;
	};
}
