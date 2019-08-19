#include"pch.h"
#include<tchar.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<conio.h>
#include"Node.h"
#include"DoublyLinkedList.h"
#include"LRUCache.h"
#include"Admin.h"
#include"Customer.h"

using namespace std;

//admin username and password is fixed
string admin_username = "aadhith";
string admin_password = "shuki";

void clrscr()
{
	system("cls");
}

//create a new account
void sign_up()
{
	string uname, pwd, usr, nname, loc;
	int flag = 0;
	ifstream fuserin;
	fstream fuserout;
	fuserin.open("users.txt");
	fuserout.open("users.txt", ios::app);
	do
	{
		flag = 0;
		clrscr();
		cout << "\n\tWELCOME : CREATE YOUR ACCOUNT\n\n";
		getchar();
		cout << "\tEnter your user name : ";
		getline(cin, uname);
		while (fuserin) //check if username already exist
		{
			getline(fuserin, usr);
			if (usr == uname)
			{
				flag = 1;
				cout << "\n\nUser name already exists\n\nTry another user name\n\n\n";
				_getch();
				break;
			}
		}
	} while (flag == 1);
	cout << "\n\tEnter the password : ";
	cin >> pwd;
	cout << "\n\tEnter the Nickname : ";
	cin >> nname;
	cout << "\n\tEnter your Location : ";
	cin >> loc;
	//writing on file to store users details
	fuserout << uname << endl;
	fuserout << pwd << endl;
	fuserout << nname << endl;
	fuserout << loc << endl;
	cout << "\n\n\tACCOUNT SUCCESSFULLY CREATED\n\n";
	fuserin.close();
	fuserout.close();
	getchar();
	_getch();
}

int main()
{
	string t, s;
	int ch, chc, coice;

	do
	{

		clrscr();
		cout << "-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*";
		cout << "\n\n\t\tWELCOME TO OUR PROJECT : MUSIC STREAMER \n\n";
		cout << "-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*";
		cout << "\n\n\t1.Sign up\n";
		cout << "\t2.Log in\n";
		cout << "\t3.Exit\n\n";
		cout << "\tEnter your choice : ";
		cin >> ch;
		clrscr();
		if (ch == 1)
		{
			sign_up();
		}

		else if (ch == 2)
		{

			do
			{
				clrscr();
				cout << "\n\n\tWELOCOME TO LOGIN PAGE\n\n";
				cout << "\t1.Admin\n\n\t2.Customer\n\n\t3.Exit\n\n";
				cout << "Enter your choice : ";
				cin >> chc;
				if (chc == 1)
				{
					cout << "\n\tEnter admin's username : ";
					cin >> t;
					cout << "\n\tEnter admin's password : ";
					cin >> s;
					_getch();
					//check if admin username and password matches
					if (t == admin_username && s == admin_password)
					{
						do
						{
							clrscr();
							Admin a(t, s);
							cout << "\tHey admin\n\n\tHow can i help you ?\n\n";
							cout << "\t1.View Users search history \n\t2.View users caches\n\t3.Exit\n\n";
							cout << "\tEnter your choice : ";
							cin >> coice;
							if (coice == 1)
							{
								clrscr();
								cout << "\n\tSearch History\n\n";
								//view search history of all users
								a.view_search_hist();
								_getch();
							}

							else if (coice == 2)
							{
								//view current cache of all users
								a.view_users_cache();
								_getch();
							}

							else if (coice == 3) {}

							else
							{
								cout << "\n\tEnter a valid option\n";
							}

							_getch();

						} while (coice != 3);
					}

					else
					{
						clrscr();
						cout << "\n\n\tAdmin username and password does not match\n\n";
						_getch();
					}
				}

				else if (chc == 2)
				{
					cout << "\n\n\tEnter customer username : ";
					cin >> t;
					cout << "\n\tEnter customer password : ";
					cin >> s;
					Customer c(t, s);
					//login as customer
					c.login_customer(t, s);
				}

				else if (chc == 3) {}

				else
				{
					cout << "\nEnter a valid option\n";
				}


			} while (chc != 3);
		}

		else if (ch == 3) {}

		else
		{
			cout << "\n\nEnter a valid option\n\n";
		}

	} while (ch != 3);

	return 0;
}
