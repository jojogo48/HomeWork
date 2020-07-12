#include <iostream>
#include "BKtree.h"
using namespace std;


int main()
{
	string text_fn, dic_fn, out_fn;
	string text, word, answer;
	int	   tol;
	BKtree* dis;
	{
		fstream fread;

		cout << "Enter text file name.......";
		cin >> text_fn;

		fread.open(text_fn, ios::in | ios::binary | ios::ate);

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

	cout << "Enter dictionary file name.....";
	cin >> dic_fn;
	cout << "Enter output file name.....";
	cin >> out_fn;
	cout << "Choose your edit distance.......\n(A)Traditional Edit Distance\n(B)Levenshtein Edit Distance\n(C)Damerau-Levenshtein Distance\n";
	cout << "Your answer.......";
	cin >> answer;
	cout << "Enter tolerance .....";
	cin >> tol;


	if (answer == "A")
		dis = new BKtreeEdit();
	else if (answer == "B")
		dis = new BKtreeL();
	else if (answer == "C")
		dis = new BKtreeDL();
	else
	{
		cout << "error answer";
		system("pause");
		return 0;
	}
	dis->read(dic_fn);

	stringstream ss;
	ss << text;

	int err_w = 0;
	int total_w = 0;
	int err_c = 0;
	int total_com = 0;

	int ss_size = ss.str().size();
	while (ss >> word)
	{
		total_w++;
		pair<int, string> corr_w = dis->search(word, tol);
		total_com += corr_w.first;
		if (corr_w.second != "")
		{
			err_w++;
			err_c += dis->Edit_Distance(corr_w.second, word);
			int ss_pos = ss.tellg();

			if (ss_pos == -1)
			{
				ss_pos = ss_size;
			}

			int displace = ss_size - ss_pos + word.size();
			int start = text.size() - displace;
			text = text.replace(start, word.size(), corr_w.second);
		}
	}
	cout << "total compare times " << total_com << endl;
	cout << "word error number "<< err_w<<endl<<"word error rate " << (double)err_w / total_w << endl;
	cout << "character error number " << err_c << endl << "character error rate " << (double)err_c / ss_size << endl;

	fstream fw;
	fw.open(out_fn, ios::trunc | ios::out | ios::binary);
	fw.write(text.c_str(), text.size());
	system("pause");
	return 0;
}

