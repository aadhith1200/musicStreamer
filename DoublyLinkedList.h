#pragma once
#include"Node.h"

class DoublyLinkedList
{
public:
	Node *front, *rear;
	bool isEmpty()
	{
		return rear == NULL;
	}

	DoublyLinkedList() : front(NULL), rear(NULL) {};

	Node* add_page_to_head(string key, string value);
	void move_page_to_head(Node *page);
	void remove_rear_page();
	Node* get_rear_page();

};


