#pragma once
#include<iostream>
using namespace std;

class Node
{
public:
	string key, value;
	Node *prev, *next;
	Node(string k, string v);
};