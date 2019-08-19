#pragma once
#include"User.h"
#include"LRUCache.h"

class Customer : public User
{
public:
	Customer();
	Customer(string usrname, string pwd);
	LRUCache memory;
	char customer_fn[100];
	void song_search();
	void see_cache();
	void create_file(string uname);
	void write_to_memory();
	int login_check(string usrname, string pwd);
	void login_customer(string usr_nam, string pass);
	int audio_dwnl(char urlinp[], char sngnm[]);
};
