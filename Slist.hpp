#pragma once
#include <iostream>
#include <cassert>
using namespace std;

/*Linked List ADT*/
template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* link;
};

template <class Type>
class linkedListType
{
public:
	template <class Type>
	class linkedListIterator
	{
	public:
		linkedListIterator()
		{
			current = NULL;
		}
		linkedListIterator(nodeType<Type>* ptr)
		{
			current = ptr;
		}
		Type& operator*()
		{
			return current->info;
		}
		linkedListIterator<Type> operator++()
		{
			current = current->link;
			return *this;
		}
		bool operator==(const linkedListIterator<Type>& right) const
		{
			return (current == right.current);
		}
		bool operator!=(const linkedListIterator<Type>& right) const
		{
			return (current != right.current);
		}
	private:
		nodeType<Type>* current; //pointer to point to the current
		//node in the linked list
	};

public:
	const linkedListType<Type>& operator=(const linkedListType<Type>& otherList)
	{
		if (this != &otherList) //avoid self-copy
		{
			copyList(otherList);
		}//end else
		return *this;
	}
	void initializeList()
	{
		destroyList();
	}
	bool isEmptyList() const
	{
		return (first == NULL);
	}
	void print() const
	{
		nodeType<Type>* current; //pointer to traverse the list
		current = first; //set current point to the first node
		while (current != NULL) //while more data to print
		{
			cout << current->info << " ";
			current = current->link;
		}
	}//end print
	int length() const
	{
		return count;
	}
	void destroyList()
	{
		nodeType<Type>* temp; //pointer to deallocate the memory
		//occupied by the node
		while (first != NULL) //while there are nodes in the list
		{
			temp = first; //set temp to the current node
			first = first->link; //advance first to the next node
			delete temp; //deallocate the memory occupied by temp
		}
		last = NULL; //initialize last to NULL; first has already
		//been set to NULL by the while loop
		count = 0;
	}
	Type& front() const
	{
		assert(first != NULL);
		return first->info; //return the info of the first node
	}//end front
	Type& back() const
	{
		assert(last != NULL);
		return last->info; //return the info of the last node
	}//end back
	virtual bool search(const Type& searchItem) const = 0;
	virtual void insertFirst(const Type& newItem) = 0;
	virtual void insertLast(const Type& newItem) = 0;
	virtual void deleteNode(const Type& deleteItem) = 0;
	linkedListIterator<Type> begin()
	{
		linkedListIterator<Type> temp(first);
		return temp;
	}
	linkedListIterator<Type> end()
	{
		linkedListIterator<Type> temp(NULL);
		return temp;
	}
	linkedListType()
	{
		first = NULL;
		last = NULL;
		count = 0;
	}
	linkedListType(const linkedListType<Type>& otherList)
	{
		first = NULL;
		copyList(otherList);
	}//end copy constructor
	~linkedListType()
	{
		destroyList();
	}
protected:
	int count; //variable to store the number of elements in the list
	nodeType<Type>* first; //pointer to the first node of the list
	nodeType<Type>* last; //pointer to the last node of the list
private:
	void copyList(const linkedListType<Type>& otherList)
	{
		nodeType<Type>* newNode; //pointer to create a node
		nodeType<Type>* current; //pointer to traverse the list
		if (first != NULL) //if the list is nonempty, make it empty
			destroyList();
		if (otherList.first == NULL) //otherList is empty
		{
			first = NULL;
			last = NULL;
			count = 0;
		}
		else
		{
			current = otherList.first; //current points to the
			//list to be copied
			count = otherList.count;
			//copy the first node
			first = new nodeType<Type>; //create the node
			first->info = current->info; //copy the info
			first->link = NULL; //set the link field of the node to NULL
			last = first; //make last point to the first node
			current = current->link; //make current point to the next
			// node
			//copy the remaining list
			while (current != NULL)
			{
				newNode = new nodeType<Type>; //create a node
				newNode->info = current->info; //copy the info
				newNode->link = NULL; //set the link of newNode to NULL
				last->link = newNode; //attach newNode after last
				last = newNode; //make last point to the actual last
				//node
				current = current->link; //make current point to the
				//next node
			}//end while
		}//end else
	}//end copyList
};

template <class Type>
class unorderedLinkedList : public linkedListType<Type>
{
public:
	bool search(const Type& searchItem) const
	{
		nodeType<Type>* current; //pointer to traverse the list
		bool found = false;
		current = this->first; //set current to point to the first
		//node in the list
		while (current != NULL && !found) //search the list
			if (current->info == searchItem) //searchItem is found
				found = true;
			else
				current = current->link; //make current point to
				//the next node
		return found;
	}
	
	void insertFirst(const Type& newItem)
	{
		nodeType<Type>* newNode; //pointer to create the new node
		newNode = new nodeType<Type>; //create the new node
		newNode->info = newItem; //store the new item in the node
		newNode->link = this->first; //insert newNode before first
		this->first = newNode; //make first point to the actual first node
		this->count++; //increment count
		if (this->last == NULL) //if the list was empty, newNode is also
		//the last node in the list
			this->last = newNode;
	}
	void insertLast(const Type& newItem)
	{
		nodeType<Type>* newNode; //pointer to create the new node
		newNode = new nodeType<Type>; //create the new node
		newNode->info = newItem; //store the new item in the node
		newNode->link = NULL; //set the link field of newNode to NULL
		if (this->first == NULL) //if the list is empty, newNode is
		//both the first and last node
		{
			this->first = newNode;
			this->last = newNode;
			this->count++; //increment count
		}
		else //the list is not empty, insert newNode after last
		{
			this->last->link = newNode; //insert newNode after last
			this->last = newNode; //make last point to the actual
			//last node in the list
			this->count++; //increment count
		}
	}
	void deleteNode(const Type& deleteItem)
	{
		nodeType<Type>* current; //pointer to traverse the list
		nodeType<Type>* trailCurrent; //pointer just before current
		bool found;
		if (this->first == NULL) //Case 1; the list is empty.
			cout << "Cannot delete from an empty list."
			<< endl;
		else
		{
			if (this->first->info == deleteItem) //Case 2
			{
				current = this->first;
				this->first = this->first->link;
				this->count--;
				if (this->first == NULL) //the list has only one node
					this->last = NULL;
				delete current;
			}
			else //search the list for the node with the given info
			{
				found = false;
				trailCurrent = this->first; //set trailCurrent to point
				//to the first node
				current = this->first->link; //set current to point to
				//the second node
				while (current != NULL && !found)
				{
					if (current->info != deleteItem)
					{
						trailCurrent = current;
						current = current->link;
					}
					else
						found = true;
				}//end while
				if (found) //Case 3; if found, delete the node
				{
					trailCurrent->link = current->link;
					this->count--;
					if (this->last == current) //node to be deleted was the
					//last node
						this->last = trailCurrent; //update the value of last
					delete current; //delete the node from the list
				}
				else
					cout << "The item to be deleted is not in "
					<< "the list." << endl;
			}//end else
		}//end else
	}//end deleteNode
	
};
template <class Type>
class orderedLinkedList : public linkedListType<Type>
{
public:
	bool search(const Type& searchItem) const
	{
		bool found = false;
		nodeType<Type>* current; //pointer to traverse the list
		current = this->first; //start the search at the first node
		while (current != NULL && !found)
			if (current->info >= searchItem)
				found = true;
			else
				current = current->link;
		if (found)
			found = (current->info == searchItem); //test for equality
		return found;
	}//end search
	
	void insert(const Type& newItem)
	{
		nodeType<Type>* current = nullptr; //pointer to traverse the list
		nodeType<Type>* trailCurrent = nullptr; //pointer just before current
		nodeType<Type>* newNode = nullptr; //pointer to create a node
		bool found;
		newNode = new nodeType<Type>; //create the node
		newNode->info = newItem; //store newItem in the node
		newNode->link = NULL; //set the link field of the node
		//to NULL
		if (this->first == NULL) //Case 1
		{
			this->first = newNode;
			this->last = newNode;
			this->count++;
		}
		else
		{
			current = this->first;
			found = false;
			while (current != NULL && !found) //search the list
				if (current->info >= newItem)
					found = true;
				else
				{
					trailCurrent = current;
					current = current->link;
				}
			if (current == this->first) //Case 2
			{
				newNode->link = this->first;
				this->first = newNode;
				this->count++;
			}
			else //Case 3
			{
				trailCurrent->link = newNode;
				newNode->link = current;
				if (current == NULL)
					this->last = newNode;
				this->count++;
			}
		}//end else
	}//end insert
	
	void insertFirst(const Type& newItem)
	{
		insert(newItem);
	}//end insertFirst
	
	void insertLast(const Type& newItem)
	{
		insert(newItem);
	}
	
	void deleteNode(const Type& deleteItem)
	{
		nodeType<Type>* current = nullptr; //pointer to traverse the list
		nodeType<Type>* trailCurrent = nullptr; //pointer just before current
		bool found;
		if (this->first == NULL) //Case 1
			cout << "Cannot delete from an empty list." << endl;
		else
		{
			current = this->first;
			found = false;
			while (current != NULL && !found) //search the list
				if (current->info >= deleteItem)
					found = true;
				else
				{
					trailCurrent = current;
					current = current->link;
				}
			if (current == NULL) //Case 4
				cout << "The item to be deleted is not in the list."
				<< endl;
			else
				if (current->info == deleteItem) //the item to be
				//deleted is in the list
				{
					if (this->first == current) //Case 2
					{
						this->first = this->first->link;
						if (this->first == NULL)
							this->last = NULL;
						delete current;
					}
					else //Case 3
					{
						trailCurrent->link = current->link;
						if (current == this->last)
							this->last = trailCurrent;
						delete current;
					}
					this->count--;
				}
				else //Case 4
					cout << "The item to be deleted is not in the "
					<< "list." << endl;
		}
	}//end deleteNode
	
};
