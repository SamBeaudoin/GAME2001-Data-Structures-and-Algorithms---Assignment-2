#pragma once
#include <cassert>

// Template Class Declarations
template <class T> class LinkIterator;
template <class T> class LinkedList;

// Define a node
template <class T>
class LinkNode
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class LinkedList<T>;

private:

	int m_priority;
	T m_data;

	LinkNode* m_next;	// Self-referencial Pointer
	LinkNode* m_previous;
};

// Define an iterator
template <class T>
class LinkIterator
{
public:
	friend class LinkedList<T>;

	LinkIterator()
	{
		m_node = nullptr;
	}
	~LinkIterator() {}

	// -------- Information Getters ---------------------
	int GetPriority()
	{
		return m_node->m_priority;
	}
	T& GetData()
	{
		return m_node->m_data;
	}

	// ----------- OVERLOADED OPERATORS ------------------
	// Assignmnet operator (=) <-- Set the iterator to point to a node  // a = b
	void operator=(LinkNode<T>* node)
	{
		m_node = node;
	}
	// Incremental operator (++) Prefix and Postfox <-- Move the iterator to the next node
	void operator++(int) // Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}

	// Existence Getter
	bool isValid()
	{
		return (m_node != NULL);
	}

private:
	LinkNode<T>* m_node;	// Pointer to a node in the linked list
};

// Define a linked list itself
template <class T>
class LinkedList
{
public:
	// Constructor and Destructor
	LinkedList() : m_size(0), m_root(nullptr), m_lastNode(nullptr) {}
	~LinkedList()
	{
		while (m_root)
		{
			Pop_Front();
		}
	}
	// --------------- POSITIONING FUNCTIONS ----------------------
	LinkNode<T>* Begin()
	{
		assert(m_root != nullptr);
		return m_root;
	}
	// --------------- PRIORITY QUEUE FUNCTIONS --------------------
	void Insert_Before(LinkIterator<T>& it, T newData, int priority)
	{
		assert(it.m_node != nullptr);

		LinkNode<T>* node = new LinkNode<T>;
		assert(node != nullptr);

		node->m_data = newData;
		node->m_priority = priority;
		node->m_next = it.m_node;
		node->m_previous = it.m_node->m_previous;

		if (node->m_previous != nullptr)
		{
			// Point the previous node to the new node
			node->m_previous->m_next = node;
		}

		it.m_node->m_previous = node;

		// Check to see if the iterator was pointing to the root
		if (it.m_node == m_root)
		{
			m_root = node;
		}

		m_size++;
	}
	// --------------- LINKED LIST OPERATIONS ---------------------
	void Pop_Front()
	{
		assert(m_root != nullptr);

		// Create a temp that will allow us to delete the content as needed
		LinkNode<T>* temp = m_root;

		// Reroute pointers
		m_root = m_root->m_next;

		if (m_root != nullptr)
		{
			m_root->m_previous = nullptr;
		}
		else
		{
			m_lastNode = nullptr;
		}

		delete temp;
		temp = nullptr;

		m_size = (m_size == 0 ? m_size : m_size - 1);
	}
	void Push_Back(T newData, int priority)
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != nullptr);
		node->m_data = newData;
		node->m_priority = priority;
		node->m_next = nullptr;
		node->m_previous = nullptr;

		// Add the new LinkNode to the existing LinkedList
		if (m_lastNode != nullptr) // LinkedList is populated. Push to the end of the list.
		{
			m_lastNode->m_next = node;
			node->m_previous = m_lastNode;
		}
		else // An empty linked list
		{
			m_root = node;
		}

		m_lastNode = node;

		m_size++;
	}
	
	// List Size Getter
	int GetSize()
	{
		return m_size;
	}
private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};
