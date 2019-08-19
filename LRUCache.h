#pragma once
#include"DoublyLinkedList.h"
#include<map>

class LRUCache
{
	int capacity, size;
public:
	DoublyLinkedList *pageList;
	map<string, Node*> pageMap;
	LRUCache();
	LRUCache(int capacity);
	string get(string key);
	void put(string key, string value);
	~LRUCache();
};


