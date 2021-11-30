#pragma once

#include "PriorityQueueLinkedList.h"

template<class T>
class PriorityQueue
{
public:
	PriorityQueue(int size)
	{
		assert(size > 0);
		m_size = size;
	}
	~PriorityQueue() {}

	// Priority Queue Functions
	void push(T val, int priority)
	{
		assert(m_elements.GetSize() < m_size);

		if (m_elements.GetSize() == 0)
		{
			m_elements.Push_Back(val, priority);
		}
		else
		{
			LinkIterator<T> it;
			it = m_elements.Begin();

			while (it.isValid())
			{
				if (it.GetPriority() > priority)
				{
					break;
				}
				it++;
			}
			if (it.isValid())
			{
				// If valid we have found an iterator pointing to a higher priority
				m_elements.Insert_Before(it, val, priority);
			}
			else
			{
				// If it is nullptr list is either empty or we have hit the end
				m_elements.Push_Back(val, priority);
			}
		}
	}

	void pop()
	{
		m_elements.Pop_Front();
	}

	LinkIterator<T> front()
	{
		LinkIterator<T> it;
		it = m_elements.Begin();

		return it;
	}
	LinkIterator<T> back()
	{
		LinkIterator<T> it;
		it = m_elements.Last();

		return it;
	}

	// Helper functions
	bool isEmpty()
	{
		return (m_elements.GetSize() == 0);
	}

private:
	LinkedList<T> m_elements; // Priority Queue Linked List
	int m_size;
};