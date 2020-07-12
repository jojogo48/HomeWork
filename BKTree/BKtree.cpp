#include "BKtree.h"
using namespace std;

void			BKtree::save(string filename)
{
	fstream fout;
	fout.open(filename, ios::out | ios::trunc | ios::binary);

	if (!fout)
	{
		cout << "無法開起";
		system("pause");
		exit(1);
	}

	queue<node*> queue_n;
	queue_n.push(root);

	while (!queue_n.empty())
	{
		node* temp = queue_n.front();
		queue_n.pop();

		fout << temp->word;

		for (map<int, node*>::iterator it = (temp->child).begin(); it != (temp->child).end(); it++)
		{
			fout << " " << it->first;
			queue_n.push(it->second);
		}
		fout << endl;
	}
	fout.close();
}
void			BKtree::read(string filename)
{
	fstream			fin;
	queue<node*>	queue_n;
	string			line;
	stringstream	ss;
	string			word;
	int				child_index;

	fin.open(filename, ios::in | ios::binary);

	if (!fin)
	{
		cout << "無法開起";
		system("pause");
		exit(1);
	}

	queue_n.push(root);
	while (!queue_n.empty())
	{
		node* curr_n = queue_n.front();
		queue_n.pop();

		getline(fin, line);
		ss << line;

		ss >> word;
		curr_n->word = word;

		while (ss >> child_index)
		{
			curr_n->child[child_index] = new node();
			queue_n.push(curr_n->child[child_index]);
		}

		ss.str("");
		ss.clear();
	}

	fin.close();
}

pair<int, string>	BKtree::search(string word, int tol)
{
	pair<int, string>	p;
	int					count = 0;
	int					min_dis = tol + 1;
	string				min_str = "";


	queue<node*>   queue_n;
	queue_n.push(root);

	while (!queue_n.empty())
	{
		node* curr_node = queue_n.front();
		queue_n.pop();

		count++;
		int dis = Edit_Distance(curr_node->word, word);

		if (dis <= tol && min_dis > dis)
		{
			min_dis = dis;
			min_str = curr_node->word;
		}

		int lower = (dis - tol > 0) ? dis - tol : 1;
		int upper = dis + tol;

		map<int, node*>::iterator it;
		for (int i = lower; i <= upper; i++)
		{
			it = curr_node->child.find(i);
			if (it != curr_node->child.end())
			{
				queue_n.push(it->second);
			}
		}
	}
	if (min_dis == 0)
	{
		min_str = "";
	}

	p.first = count;
	p.second = min_str;

	return p;
}

int** BKtree::create_table(int w1len, int w2len)
{
	int** table = new int* [w1len + 1];

	for (int i = 0; i < w1len + 1; i++)
	{
		table[i] = new int[w2len + 1]();
	}

	for (int i = 0; i < w2len + 1; i++)
	{
		table[0][i] = i;
	}
	for (int i = 0; i < w1len + 1; i++)
	{
		table[i][0] = i;
	}
	return table;
}

void			BKtree::delete_table(int** table, int w1len)
{
	for (int i = 0; i <= w1len; i++)
	{
		delete[] table[i];
		table[i] = NULL;
	}
	delete[] table;
	table = NULL;
}

void			BKtree::insert(string word)
{
	if (root->word == "")
	{
		root->word = word;
		return;
	}

	node* curr_node = root;
	int dis = Edit_Distance(curr_node->word, word);

	while (curr_node->child.find(dis) != curr_node->child.end())
	{
		curr_node = curr_node->child[dis];
		dis = Edit_Distance(curr_node->word, word);

	}
	curr_node->child[dis] = new node();
	curr_node->child[dis]->word = word;
}

int				BKtreeEdit::Edit_Distance(string w1, string w2)
{

	int w1len = w1.size();
	int w2len = w2.size();
	int** table = create_table(w1len, w2len);

	for (int i = 1; i <= w1len; i++)
	{
		for (int j = 1; j <= w2len; j++)
		{
			int k = (w1[i - 1] == w2[j - 1]) ? 0 : 1;

			int min = (table[i - 1][j] < table[i][j - 1]) ? table[i - 1][j] + 1 : table[i][j - 1] + 1;
			min = (min < table[i - 1][j - 1] + k) ? min : table[i - 1][j - 1] + k;

			table[i][j] = min;
		}
	}
	int edit_dis = table[w1len][w2len];

	delete_table(table, w1len);

	return edit_dis;
}

int				BKtreeL::Edit_Distance(string w1, string w2)
{
	int w1len = w1.size();
	int w2len = w2.size();
	int** table = create_table(w1len, w2len);

	for (int i = 1; i <= w1len; i++)
	{
		for (int j = 1; j <= w2len; j++)
		{
			int k = (w1[i - 1] == w2[j - 1]) ? 0 : 2;

			int min = (table[i - 1][j] < table[i][j - 1]) ? table[i - 1][j] + 1 : table[i][j - 1] + 1;
			min = (min < table[i - 1][j - 1] + k) ? min : table[i - 1][j - 1] + k;

			table[i][j] = min;
		}
	}
	int edit_dis = table[w1len][w2len];


	delete_table(table, w1len);

	return edit_dis;
}

int				BKtreeDL::Edit_Distance(string w1, string w2)
{
	int w1len = w1.size();
	int w2len = w2.size();
	int** table = create_table(w1len, w2len);
	//int* char_dic = new int[1000]();
	map<char, int> char_dic;

	for (int i = 1; i <= w1len; i++)
	{
		int last_j = 0;
		for (int j = 1; j <= w2len; j++)
		{
			int k = 1;
			int curr_i = 0;

			if (char_dic.find(w2[j - 1]) != char_dic.end())
			{
				curr_i = char_dic[w2[j - 1]];
			}
	

			if (w1[i - 1] == w2[j - 1])
			{
				k = 0;
				last_j = j;
			}

			int min = (table[i - 1][j] < table[i][j - 1]) ? table[i - 1][j] + 1 : table[i][j - 1] + 1;
			min = (min < table[i - 1][j - 1] + k) ? min : table[i - 1][j - 1] + k;

			if (curr_i != 0 && last_j != 0)
			{
				int transposition = table[curr_i - 1][last_j - 1] + (i - curr_i - 1) + 1 + (j - 1 - last_j);
				if (min > transposition)
				{
					min = transposition;
				}
			}
			table[i][j] = min;
		}	
		char_dic[w1[i - 1]] = i;
	}

	int edit_dis = table[w1len][w2len];
	//delete[] char_dic;
	delete_table(table, w1len);
	return edit_dis;
}