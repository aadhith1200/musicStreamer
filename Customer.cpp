#include "pch.h"
#include "Customer.h"
#include<iostream>
#include<fstream>
#include<map>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<stdlib.h>
#include<string>
#define CURL_STATICLIB
#ifdef _DEBUG
#pragma comment(lib,"curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif
#include "curl/curl.h"
using namespace std;



Customer::Customer()
{
	//ctor
}



Customer::Customer(string usrname, string pwd)
{

	username = usrname;
	password = pwd;

}

//function to download songs from firebase server
int Customer::audio_dwnl(char urlinp[], char sngnm[])
{
	CURL *curl;
	FILE *fp;
	CURLcode res;
	char url[200];
	strcpy_s(url, 200, urlinp);
	char dm[5] = ".mp3";
	char outfilename[100];
	strcpy_s(outfilename, 100, sngnm);
	strcat_s(outfilename, 100, dm);
	curl = curl_easy_init();

	if (curl)
	{
		fopen_s(&fp, outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	cout << "Playing Song \n";
	char fileloc[70] = "";
	strcat_s(fileloc, 70, outfilename);
	system(fileloc);
	return 0;
}


//function to search a song
void Customer::song_search()
{
	string song, line, url;
	ofstream fout;
	int flag2 = 0;
	//we use map to retrieve song and download link in O(1) time
	map<string, string> sngs;
	ifstream fin;
	fin.open("songs.txt");
	//writing songs and links into map
	while (fin)
	{
		string t, s;
		getline(fin, t);
		getline(fin, s);
		sngs.insert(pair<string, string>(t, s));
	}
	fin.close();
	system("cls");
	getchar();
	cout << "\n\n\t\tstream.io\n";
	cout << "SONG NAME\n\n";
	cout << "1.animals\n";
	cout << "2.azhage\n";
	cout << "3.bad_eyes\n";
	cout << "4.enna_nadandhalum\n";
	cout << "5.kanave\n";
	cout << "6.machi_engalukku\n";
	cout << "7.neram\n";
	cout << "8.pakkam_vandhu\n";
	cout << "9.back_to_you\n";
	cout << "10.showkali\n";
	cout << "11.thalli_poghadhey\n\n\n";
	cout << "\nEnter song : ";
	getline(cin, song);
	//retrieving download link of input song in url
	url = sngs[song];
	if (url != "\0")//check if song exists in our server
	{
		flag2 = 1;
	}
	if (flag2)
	{
		fstream fp1;
		//write the data searched at a time in data.csv for admin's usage
		fp1.open("data.csv", ios::app);
		char temptime[26];
		time_t now = time(0);
		ctime_s(temptime,26,&now);
		fp1 << nickname + "," << song + "," << temptime << endl;
		fp1.close();
		flag2 = 0;
		string link;
		//retrieve the song link
		link = memory.get(song);
		if (link == "no match")//song is not already available in our cache
		{
			//As our cache size is three , we check three conditions
			//checks if any of the cache is empty
			if ((&memory.pageList->front->key != NULL) &&(&memory.pageList->front->next->key != NULL) &&(&memory.pageList->front->next->next->key != NULL))
			{
				string sng_lsname = memory.pageList->front->next->next->key;
				memory.put(song, url);
				link = memory.get(song);
				char link_temp[400], song_temp[100];
				strcpy_s(link_temp, 400, link.c_str());
				strcpy_s(song_temp, 100, song.c_str());
				cout << "Downloading Song....\n";
				//song is downloaded from server
				audio_dwnl(link_temp, song_temp);
				string path_loc = sng_lsname + ".mp3";
				//least recently used song is deleted from our local drive
				remove(path_loc.c_str());
			}
			else  //if cache not empty
			{
				memory.put(song, url);
				link = memory.get(song);
				char link_temp[400], song_temp[100];
				strcpy_s(link_temp, 400, link.c_str());
				strcpy_s(song_temp, 100, song.c_str());
				cout << "Downloading Song....\n";
				//download from server and play
				audio_dwnl(link_temp, song_temp);
			}

		}
		else //song already available in cache
		{
			//play song from local directory
			string path_loc = song + ".mp3";
			cout << "Playing Song\n";
			system(path_loc.c_str());

		}
		//write the new cache into file
		fout.open("mem1.txt");
		if (&memory.pageList->front->next->next->key != NULL)
		{
			fout << memory.pageList->front->next->next->key << endl << memory.pageList->front->next->next->value << endl;
		}
		if (&memory.pageList->front->next->key != NULL)
		{
			fout << memory.pageList->front->next->key << endl << memory.pageList->front->next->value << endl;
		}
		if (&memory.pageList->front->key)
		{
			fout << memory.pageList->front->key << endl << memory.pageList->front->value;
		}
		fout.close();
		remove(customer_fn);
		rename("mem1.txt", customer_fn);
	}

	else //song not available in the server
	{
		cout << "\n\n\tWe are sorry :( song not found\n\n";
	}
	Sleep(2500);

}

//function to view current cache of the user
void Customer::see_cache()
{
	string key, val;
	ifstream fin2;
	system("cls");
	fin2.open(customer_fn);
	cout << "\n\tCURRENT CACHE\n\n";
	int cnt = 0;
	while (cnt < 3)
	{
		getline(fin2, key);
		getline(fin2, val);
		cout << "SONG : " << key << "\tURL : " << val << "\n\n";
		cnt++;
	}
	cout << endl;
	Sleep(2500);
}

//function to create file for user in his name and store his cache in it
//Example: If users name is shuki..his cache will be stored in shuki.txt
void Customer::create_file(string uname)
{
	string un=uname+".txt";
	int len, i;
	len = un.length();
	for (i = 0; i < len; i++)
	{
		customer_fn[i] = un[i];
	}
	customer_fn[len] = '\0';
	fstream foutt;
	foutt.open(customer_fn, ios::app);
	foutt.close();
}

//function to read from cache file of user and put it in memory for usage in program
void Customer::write_to_memory()
{
	string k, v;
	ifstream fin1;
	fin1.open(customer_fn);
	while (!fin1.eof())
	{
		getline(fin1, k);
		getline(fin1, v);
		memory.put(k, v);
	}
	fin1.close();
}

//function to check if the login of the user is valid
int Customer::login_check(string usrname, string pwd)
{
	int f;
	string temp1, temp2, temp3, temp4;
	ifstream fupin;
	fupin.open("users.txt");
	while (fupin)
	{
		f = 0;
		getline(fupin, temp1);
		getline(fupin, temp2);
		getline(fupin, temp3);
		getline(fupin, temp4);
		if (temp1 == usrname && temp2 == pwd)
		{
			f = 1;
			cout << "\n\n\tLogin successful\n\n";
			nickname = temp3;
			location = temp4;
			Sleep(2500);
			break;
		}
	}
	if (f == 0)
	{
		cout << "\n\n\tUser name and password do not match\n\n";
		Sleep(2500);
	}
	fupin.close();
	return f;
}

//function for customer login
void Customer::login_customer(string usr_name, string pass)
{
	int f = 0, choice;
	do
	{
		f = 0;
		f = login_check(usr_name, pass);
		cout << f;

	} while (f == 0);

	if (f == 1)
	{
		create_file(usr_name);
		write_to_memory();
		do
		{
			system("cls");
			cout << "\n\tHEY USER HOW CAN I HELP YOU :)";
			cout << "\n\n\t1.Search for a song" << endl;
			cout << "\t2.View my cache" << endl;
			cout << "\t3.Exit" << endl;
			cout << "\nEnter your choice : ";
			cin >> choice;
			if (choice == 1)
			{
				song_search();
			}

			else if (choice == 2)
			{
				see_cache();
			}

			else if (choice == 3) {}

			else
			{
				cout << "\n\nEnter a valid option\n\n";
			}

		} while (choice != 3);

	}
}
