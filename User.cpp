#include "pch.h"
#include "User.h"
#include<string>

User::User()
{

}

User::User(string uname, string pwd, string nname, string loc)
{
	username = uname;
	password = pwd;
	nickname = nname;
	location = loc;

}
