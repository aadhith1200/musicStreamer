#pragma once
#include"LRUCache.h"

class User
{
public:
	User();
	User(string uname, string pwd, string nname, string loc);

protected:
	string username;
	string password;
	string nickname;
	string location;
};

