#include <iostream>
#include "PriorityQueue.h"
using namespace std;

int main()
{
	// Intro
	cout << "===================" << endl;
	cout << "Assignment #2 Demo: " << endl;
	cout << "===================" << endl << endl;

	// Create Priority Que
	const int SIZE = 6;
	PriorityQueue<string> que(SIZE);

	// Initialize strings
	string string1 = "This message is the first to be input";
	string string2 = "This message is of the highest priority";
	string string3 = "This message is also highest priority but is input after";
	string string4 = "This message just wants in the linked list";
	string string5 = "This message will be last";
	string string6 = "This message should be somewhere in the middle";

	// Push Strings
	que.push(string1, 2);
	que.push(string2, 1);
	que.push(string3, 1);
	que.push(string4, 4);
	que.push(string5, 5);
	que.push(string6, 3);

	// Display the queue
	while (que.isEmpty() == false)
	{
		LinkIterator<string> it = que.front();
		cout << "  Priority: " << it.GetPriority();
		cout << " \tContent: " << it.GetData();
		cout << endl;

		que.pop();
	}

	cout << endl;

	// Notify que is now empty
	if (que.isEmpty() == true)
	{
		cout << "The container is empty." << endl;
	}
	else
	{
		cout << "The container is NOT empty." << endl;
	}

	return 0;
}