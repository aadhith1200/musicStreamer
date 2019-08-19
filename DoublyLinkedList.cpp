#include "pch.h"
#include "DoublyLinkedList.h"
#include<string>

//function to add the node to head (Use: when user searches a song which is not in the current cache)
Node* DoublyLinkedList::add_page_to_head(string key, string value)
{
	Node *page = new Node(key, value);
	if (!front && !rear)
	{
		front = rear = page;
	}
	else
	{
		page->next = front;
		front->prev = page;
		front = page;
	}
	return page;
}

//function to move the node to head (Use: when user searches a song which is already in the current cache)
void DoublyLinkedList::move_page_to_head(Node *page)
{
	if (page == front)
	{
		return;
	}
	if (page == rear)
	{
		rear = rear->prev;
		rear->next = NULL;
	}
	else
	{
		page->prev->next = page->next;
		page->next->prev = page->prev;
	}
	page->next = front;
	page->prev = NULL;
	front->prev = page;
	front = page;
}

//function to remove last node when capacity is breached
void DoublyLinkedList::remove_rear_page()
{
	if (isEmpty())
	{
		return;
	}
	if (front == rear)
	{
		delete rear;
		front = rear = NULL;
	}
	else
	{
		Node *temp = rear;
		rear = rear->prev;
		rear->next = NULL;
		delete temp;
	}
}

//function to get the rear page
Node* DoublyLinkedList::get_rear_page()
{
	return rear;
}
