#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include<utility>
using namespace std;

typedef struct node
{
	string word;
	map<int, node*> child;
} node;


class BKtree
{
public:
	void			insert(string word);
	pair<int,string>	search(string word, int tol);
	virtual int		Edit_Distance(string w1, string w2) = 0;
	void			save(string filename);
	void			read(string filename);
protected:
	int** create_table(int w1len, int w2len);
	void			delete_table(int** tale, int w1len);
private:
	node* root = new node();
};

class BKtreeEdit : public BKtree
{
public:
	int Edit_Distance(string w1, string w2);
};

class BKtreeL : public BKtree
{
public:
	int Edit_Distance(string w1, string w2);
};

class BKtreeDL : public BKtree
{
public:
	int Edit_Distance(string w1, string w2);
};

