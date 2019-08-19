#include "pch.h"
#include "Admin.h"
#include<fstream>
#include<iostream>
#include<string.h>
#include<windows.h>
#include<string>
using namespace std;

Admin::Admin()
{
	//ctor
}

Admin::Admin(string usrname, string pwd)
{
	username = usrname;
	password = pwd;
}

//function to view all the users cache
void Admin::view_users_cache()
{
	system("CLS");
	ifstream fin;
	int len, usr_count = 0;
	string temp1, temp2, temp3, temp4;
	char usr[100];
	fin.open("users.txt");
	while (fin)
	{
		getline(fin, temp1);
		getline(fin, temp2);
		getline(fin, temp3);
		getline(fin, temp4);
		usr_count++;
		ifstream fp1;
		string tempr = temp1 + ".txt";
		fp1.open(tempr.c_str());
		string tempre1,tempre2;
		cout << temp1 << "\n\n";
		int cnt = 0;
		while (cnt<3)
		{
			getline(fp1, tempre1);
			getline(fp1, tempre2);
			cout << tempre1 << endl;
			cnt++;
		}
		fp1.close();
		cout << "\n\n";
	}
	
	fin.close();
	
}

//function to see search history  of all users with date and time of the search
void Admin::view_search_hist()
{
	ifstream fp1;
	fp1.open("Data.csv");
	string temp;
	while (fp1)
	{
		getline(fp1, temp);
		cout << temp << endl;
	}
	fp1.close();
}
