#include <iostream>
#include "BKtree.h"
using namespace std;


int main()
{

	string file_name;
	string text;

	{
		fstream fread;

		cout << "Enter text file name.......";
		cin >> file_name;

		fread.open(file_name, ios::in | ios::binary | ios::ate);

		if (!fread)
		{
			cerr << "open file error";
			system("pause");
			exit(1);
		}

		long long int	temp_length = fread.tellg();
		int				length = (int)temp_length;
		vector<char>	buff(length);

		fread.seekg(0, ios::beg);
		fread.read(&buff[0], length);
		text = string(&buff[0], length);

		fread.close();
	}
	cout << "Enter output dictionary file name.....";
	cin >> file_name;

	string answer;	
	
	cout << "Choose your edit distance.......\n(A)Traditional Edit Distance\n(B)Levenshtein Edit Distance\n(C)Damerau-Levenshtein Distance\n";
	cout << "Your answer ...........";
	cin>>answer;
	BKtree* dis;

	stringstream ss(text);
	string word;
	
	if(answer == "A")
	dis = new BKtreeEdit();
	else if (answer =="B")
	dis = new BKtreeL();
	else if (answer == "C")
	dis = new BKtreeDL();
	else 
	{
		cout<<"error answer";
		system("pause");
		return 0;
	}

    	while(ss>>word)
    	{
       		dis->insert(word);
    	}

    dis->save(file_name);
    cout<<"create successful !!"<<endl;

	system("pause");
	return 0;
}

