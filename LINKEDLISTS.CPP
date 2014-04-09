/*
CS2134 Exam III: Implementing Linked Lists and Iterators

David Stancu
Polytechnic Institute of NYU
dstancu@nyu.edu

*/

// CAUTION: do not #include <list> or similar, our class names overlap!
#include <iostream>

// Some forward declarations
template <class Object>
class Node;

template <class Object>
class List;

template <class Object>
class ListIterator;

// The Node class is our basic container structure for our List class.
template <class Object>
class Node
{
private:
	Node* next;
	Object data;
public:
	// We use the default constructor for the 'zeroth' node
	Node() : next(NULL) {}
	Node(const Object& data, Node<Object>* next) : data(data), next(next) {}

	friend class List<Object>;
};

template <class Object>
class List
{
private:
	// This implementation will always have a default-constructed header node as the zeroth element.
	Node<Object>* header;
	// Unsigned, length is always positive. STL uses size_t as well :)
	size_t len;

	// We walk the list until we find the last member; we want this private so morons won't interfere.
	Node<Object>* findLast()
	{
		// We walk the list until we find the container which has a NULL value for next
		Node<Object>* dummy = header;
		// NULL, nullptr, and nullptr_t evaluate as false (just as zero does according to C++ standards
		while (dummy->next) dummy = dummy->next;
		return dummy;
	}

public:
	List() : header(new Node<Object>()), len(0) {}

	size_t size()
	{
		if (len) return len;

		// This is not necessary, but useful to have.
		else
		{
			Node* dummy = header;
			size_t ret = 0;
			while (dummy) ++ret;
			return ret;
		}
	}

	// Basic append function
	void push_back(const Object& x) 
	{ 
		findLast()->next = new Node<Object>(x, NULL); 
		++len;
	}

	// Basic prepend function
	void push_front(const Object& x)
	{
		// The right-hand side of the expression is evaluated first, therefore, there is no need to make a 'dummy' pointer.
		header->next = new Node(x, header->next->next);
		++len;

		/*
		The less elegant solution is, however, clearer:

		Node* dummy = header->next;
		header->next = new Node(x, dummy);
		*/
	}

	void pop_back()
	{
		// If we have an empty list there's nothing to pop out.
		if (!len) return;
		Node* dummy = header;
		// We walk the list to find the penultimate element
		while (dummy->next->next) dummy = dummy->next;
		delete dummy->next;
		dummy->next = NULL;
		--len;
	}

	void pop_front()
	{
		// If we have an empty list there's nothing to pop out.
		if (!len) return;
		
		// I can't think of a more elegant solution for this :(
		Node* dummy = header->next->next;
		delete header->next;
		header->next = dummy;
		--len;
	}

	void make_empty()
	{
		// Self explanatory at this point
		if (!len) return; 
		while (len) pop_front();

		/*
		Another less elegant, but more visible solution:

		Node* dummy = header->next;
		Node* temp;
		while (dummy)
		{
			temp = dummy;
			dummy = dummy->next;
			delete temp;
		}
		*/
	}

	friend class ListIterator<Object>;
};

// We want to give our users forward-iterable capability but we don't think they're smart enough to use pointers.
template <class Object>
class ListIterator
{
private:
	Node<Object>* current;
	bool isValid;
public:
	ListIterator(const List& list) : current(list->header->next), isValid(current != NULL) {}
	Object& operator*()
	{
		if (isValid) return current->data;

		// This is only for illustrative purposes, the right way to do this is with exception handling!
		else return *new Object&();
	}
	void operator++()
	{
		if (!isValid) break;
		// We advance
		current = current->next;
		// It's possible that we can advance to a NULL variant
		(current) ? (isValid = true) : (isValid = false);
	}
	bool operator==(const ListIterator<Object>& rhs)
	{
		// Both need to be valid or else your comparison doesn't even matter
		if (isValid && rhs.isValid) return (current->data == rhs.current->data);
		return false;
	}
	bool valid() { return isValid; }
};

int main(void)
{
	List<int> test;
	test.push_back(10);
	test.push_back(20);
	test.push_back(30);
	std::cout << "Hello world!";
}
