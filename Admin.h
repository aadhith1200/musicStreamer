#pragma once
#include"User.h"

class Admin : public User
{
public:
	Admin();
	Admin(string usrname, string pwd);
	void view_search_hist();
	void view_users_cache();


};
