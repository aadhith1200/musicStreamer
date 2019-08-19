#include "pch.h"
#include "LRUCache.h"
#include<string>

LRUCache::LRUCache()
{
	capacity = 3;
	size = 0;
	pageList = new DoublyLinkedList();
	pageMap = map<string, Node*>();
}

LRUCache::LRUCache(int capacity)
{
	this->capacity = capacity;
	size = 0;
	pageList = new DoublyLinkedList();
	pageMap = map<string, Node*>();
}

//function to get the download link with input song
string LRUCache::get(string key)
{
	if (pageMap.find(key) == pageMap.end())
	{
		return "no match";
	}
	else
	{
		string val = pageMap[key]->value;
		// move the page to front
		pageList->move_page_to_head(pageMap[key]);
		return val;
	}
}

//function to add song to cache
void LRUCache::put(string key, string value)
{
	if (pageMap.find(key) != pageMap.end())
	{
		// if key already present, update value and move page to head
		pageMap[key]->value = value;
		pageList->move_page_to_head(pageMap[key]);
		return;
	}

	if (size == capacity)
	{
		// remove rear page
		string k = pageList->get_rear_page()->key;
		pageMap.erase(k);
		pageList->remove_rear_page();
		size--;
	}

	// add new page to head to Queue
	Node *page = pageList->add_page_to_head(key, value);
	size++;
	pageMap[key] = page;
}

LRUCache::~LRUCache()
{
	map<string, Node*>::iterator i1;
	for (i1 = pageMap.begin(); i1 != pageMap.end(); i1++)
	{
		delete i1->second;
	}
	delete pageList;
}

