#include "list.hpp"

template<typename T>
mine::list<T>::iterator::iterator(ListNode<T>* p)
{
	it_pos = p;
}
//OVERLAODS {
template<typename T>// to return a non-const reference.
T& mine::list<T>::iterator::operator*()
{
	return it_pos->data;
}

template<typename T>//its return type must be a pointer or an object of a class to which you can apply.
T* mine::list<T>::iterator::operator->()
{
	return &(it_pos->data);
}

template<typename T>// return an iterator
typename mine::list<T>::iterator& mine::list<T>::iterator::operator++()
{
	it_pos = it_pos->next;
	return *this;//reference to itself(iterator)
}

template<typename T>
typename mine::list<T>::iterator& mine::list<T>::iterator::operator++(int)
{
	it_pos = it_pos->next;
	return *this;
}

template<typename T>
typename mine::list<T>::iterator& mine::list<T>::iterator::operator--()
{
	it_pos = it_pos->prev;
	return *this;
}

template<typename T>
typename mine::list<T>::iterator& mine::list<T>::iterator::operator--(int)
{
	it_pos = it_pos->prev;
	return *this;
}

template<typename T>
bool mine::list<T>::iterator::operator!=(const mine::list<T>::iterator& compare)
{
	return this->it_pos != compare.it_pos;
}

template<typename T>
bool mine::list<T>::iterator::operator==(const mine::list<T>::iterator& compare)
{
	return this->it_pos == compare.it_pos;
}

//OVERLADS }
// iterators BEGIN(), END()
template<typename T>//HEAD
typename mine::list<T>::iterator mine::list<T>::begin()
{
	return mine::list<T>::iterator(head_);
}

template<typename T>// NEXT OF LAST ELEMENT
typename mine::list<T>::iterator mine::list<T>::end()
{
	return mine::list<T>::iterator(0);
}

//LIST STUFF
/*
template<typename T>
mine::list<T>::list(std::vector<T>& vec)
{
	for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		this->push_back(*it);
	}
}

template<typename T>
mine::list<T>::list(typename std::vector<T>::iterator&& itB, typename std::vector<T>::iterator&& itE)
{
	while (itB != itE)
	{
		this->push_back(*itB);
		++itB;
	}
}
*/

template<typename T>
mine::list<T>::list(typename mine::list<T>::iterator&& begin_, typename mine::list<T>::iterator&& end_)
{
	while (begin_ != end_)
	{
		this->push_back(*begin_);
		begin_++;
	}
}

template <typename T>
mine::list<T>::~list()
{
	while (!this->empty())
	{
		//std::cout << "[ ELIMINATED FRONT ELEMENT ]" << std::endl;
		this->pop_front();
	}
}

template <typename T>
void mine::list<T>::insert(const T& data, mine::ListNode<T>* pos)
{
	mine::ListNode<T>* n = new mine::ListNode<T>(data);
	size_++;
	n->next = pos;
	if (pos) //pos is not null
	{
		n->prev = pos->prev;
		pos->prev = n;
	}
	else // pos is null => ( "empty" or "the end of list" )
	{
		n->prev = tail_;
		tail_ = n;
	}
	if (n->prev) // "n->prev" IS NOT null
	{
		n->prev->next = n;
	}
	else // "n->prev" IS null => ( "empty" or "head address" )
	{
		head_ = n;
	}
	return;
}

template <typename T>
void mine::list<T>::push_back(const T& e)
{
	insert(e, 0);
}

template<typename T>
bool mine::list<T>::empty()
{
	return !size_;
}

template <typename T>
void mine::list<T>::push_front(const T& e)
{
	insert(e, head_);
}

template <typename T>
void mine::list<T>::pop_back()
{
	remove(tail_);
}

template <typename T>
void mine::list<T>::pop_front()
{
	remove(head_);
}

template<typename T>
void mine::list<T>::printList()
{
	for (const auto& i : *this)
	{
		std::cout << i << '\n';
	}
}

template<typename T>
bool mine::list<T>::search(const T& e)
{
	for (const auto& i : *this)
	{
		if (e == i)
		{
			std::cout << "FOUND\n";
			return 1;
		}
	}
	std::cout << "NOT FOUND\n";
	return 0;
}

template <typename T>
void mine::list<T>::remove(ListNode<T>* pos)
{
	if (pos)// pos is NOT null
	{
		if (pos->prev)// NOT null.. ( re-pointing NEXT-of(pos'prev) to (pos' next) )
			pos->prev->next = pos->next;

		if (pos->next)// NOT null.. ( re-pointing PREV-of(pos'next) to (pos' prev) )
			pos->next->prev = pos->prev;

		if (pos == head_)// NOT null.. ( head bcms "null" or "next node" )
			head_ = pos->next;

		if (pos == tail_)// NOT null.. ( tail bcms "null" or "previus node" )
			tail_ = pos->prev;

		delete pos;
		size_--;
	}
}

template <typename T>
T& mine::list<T>::front()
{
	return head_->data;
}

template <typename T>
T& mine::list<T>::back()
{
	return tail_->data;
}

template <typename T>
void mine::list<T>::display()
{
	typename mine::list<T>::iterator itr;
	for (itr = this->begin(); itr != this->end(); ++itr)
	{
		std::cout << *itr << std::endl;
	}
}
