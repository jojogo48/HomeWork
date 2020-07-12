#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <time.h>
using namespace std;

class StringMatching
{
public:
	StringMatching() {}
	StringMatching(string text){this->text= char_to_char16(text);}


	vector<int> brute_force();
	vector<int> Horspool();
	vector<int> Boyer_Moore();
	void set_pattern(string pattern);
	void print_string_char16();
	void print_table();

	int comparision = 0;
private:
	int*                   generate_good_suffix_table();
	string				   ch16_to_str(char16_t a);
	map<char16_t, int>     generate_shift_table();
	basic_string<char16_t> char_to_char16(string text);


	basic_string<char16_t> text;
	basic_string<char16_t> pattern;

};


int main()
{


	StringMatching test ;

	{
		string fn;

		cout << "Enter file name...............";
		cin >> fn;

		ifstream in(fn, ios::in | ios::binary | ios::ate);

		if (!in)
		{
			cerr << "open file error";
			system("pause");
			exit(1);
		}

		long long int	temp_length = in.tellg();
		int				length		= (int)temp_length;
		vector<char>	buff(length);

		in.seekg(0, ios::beg);
		in.read(&buff[0], length);

		test = StringMatching(string(&buff[0], length));
		cout << "file size  " << length << endl;

		in.close();
	}


	string print_file = "N";
	cout << "Do you want to print out the log file(Y or N)";
	cin >> print_file;
	if (print_file == "Y")
	{
		test.print_string_char16();
	}
    string		str = "\n";
	getline(cin, str);

	/*fstream time,compare;
	time.open("time.csv",ios::out|ios::trunc);
	compare.open("compare.csv", ios::out|ios::trunc);
	int count = 1;*/
	while (true)
	{
		string		sear_w;
		vector<int> ans;
		cout << "Enter search word.............";

		getline(cin, sear_w);
		if (sear_w == "")continue;
		cout<<"pattern     " << sear_w << endl;

		/*time << count << ",";
		compare << count++<< ",";*/

		test.set_pattern(sear_w);
		cout << endl;
		test.print_table();
		cout << endl;

		time_t start, end;
		start = clock();
		ans = test.brute_force();
		end = clock();
		cout << "Brute force " << test.comparision << " comparision "<<" time "<<end - start<<" answer size " <<ans.size() <<endl;
		/*for (size_t i = 0; i < ans.size(); i++)
			cout << ans[i] << " ";
		cout << endl;*/
		
		/*time << end - start << ",";
		compare << test.comparision << ",";*/
	
		start = clock();
		ans = test.Horspool();
		end = clock();
		cout << "Horspool    " << test.comparision << " comparision " << " time " << end - start<<" answer size " <<ans.size() <<endl;
		/*for (size_t i = 0; i < ans.size(); i++)
			cout << ans[i] << " ";
		cout << endl;*/

		/*time << end - start << ",";
		compare << test.comparision << ",";*/

		start = clock();
		ans = test.Boyer_Moore();
		end = clock();
		cout << "Boyer_Moore " << test.comparision << " comparision " << " time " << end - start<<" answer size " <<ans.size() <<endl;
		/*for (size_t i = 0; i < ans.size(); i++)
			cout << ans[i] << " ";
		cout << endl << endl;*/

		/*time << end - start <<endl;
		compare << test.comparision << endl;*/
	}
	/*time.close();
	compare.close();*/
	system("pause");
	return 0;
}

void					StringMatching::set_pattern(string pattern)
{
	this->pattern = char_to_char16(pattern);
}

void					StringMatching::print_string_char16()
{
	cout << "size  " << text.size() << endl;
	for (unsigned int i = 0; i < this->text.size(); i++)
	{
		cout << ch16_to_str(this->text[i]);
	}
	cout << endl;
}

void					StringMatching::print_table()
{
	int*							good_suffix_table	= this->generate_good_suffix_table();
	map<char16_t, int>				bad_shift_table		= this->generate_shift_table();
	map<char16_t, int>::iterator	it;

	cout << "---bad table---" << endl;
	for (it = bad_shift_table.begin(); it != bad_shift_table.end(); it++)
	{
		cout << "|" <<setw(6)<< this->ch16_to_str(it->first) << "|"<<setw(5) << it->second << "|" << endl;
	}

	cout << "|" << setw(6) << string("other")<<"|" << setw(5) << pattern.size() << "|" <<endl;
	cout << "---bad suffix---" << endl;

	cout << "---good suffix---" << endl;
	for (size_t i = 0; i < pattern.size(); i++)
	{
		cout << "|" << setw(6) << string("d"+to_string(i)) << "|"<<setw(5) << good_suffix_table[i] <<"|"<< endl;
	}
	cout << "--good suffix--" << endl;

	delete good_suffix_table;
}

string					StringMatching::ch16_to_str(char16_t a)
{
	string	re;
	char	heigh	= (char)(a >> 8);
	char	low		= (char)a;

	if ((int)heigh != 0)
	{
		re += heigh;
	}
	re += low;
	return re;
}

basic_string<char16_t>	StringMatching::char_to_char16(string text)
{
	basic_string<char16_t> text16;

	for (unsigned int i = 0; i < text.size(); i++)
	{
		if ((int)text[i] < 0)
		{
			char16_t heigh	= ((char16_t)text[i] & 0x00ff) << 8;
			char16_t low	= ((char16_t)text[++i]) & 0x00ff;
			text16 += heigh + low;

			continue;
		}
		text16 += (char16_t)text[i];
	}
	return text16;
}

vector<int>				StringMatching::brute_force()
{
	int			m			= pattern.size();
	int			n			= text.size()	;
	vector<int> index_table					;

	comparision = 0;
	for (int i = 0; i < n - m + 1; i++)
	{
		bool is_match = true;
		for (int j = 0; j < m; j++)
		{
			comparision++;
			if (text[i + j] != pattern[j])
			{
				is_match = false;
				break;
			}
		}

		if (is_match)
		{
			index_table.push_back(i);
			i += m - 1;
		}
	}
	return index_table;
}

vector<int>				StringMatching::Horspool()
{
	int					m			= pattern.size()				;
	int					n			= text.size()					;
	int					i			= m - 1							;
	vector<int>			index_table									;
	map<char16_t, int>	bad_table	= this->generate_shift_table()	;

	comparision = 0;

	while (i < n)
	{
		bool is_match = true;

		for (int j = 0; j < m; j++)
		{
			comparision++;
			if (text[i - j] != pattern[m - 1 - j])
			{
				is_match = false;
				break;
			}
		}

		if (is_match)
		{
			index_table.push_back(i - (m - 1));
			i += m;
			continue;
		}

		if (bad_table.find(text[i]) != bad_table.end())
		{
			i += bad_table[text[i]];
		}
		else
		{
			i += m;
		}
	}
	return index_table;
}

vector<int>				StringMatching::Boyer_Moore()
{
	int					m					= pattern.size();
	int					n					= text.size();
	int					i					= m - 1;
	int*				good_suffix_table	= this->generate_good_suffix_table();
	map<char16_t, int>	bad_shift_table		= this->generate_shift_table();
	vector<int>			index_table;
	comparision = 0;

	while (i < n)
	{
		bool is_match		= true;
		int	 correct_num	= 0;

		for (int j = 0; j < m; j++)
		{
			comparision++;

			if (text[i - j] != pattern[m - 1 - j])
			{
				is_match = false;
				break;
			}
			correct_num++;
		}

		if (is_match)
		{
			index_table.push_back(i - (m - 1));
			i += m;
			continue;
		}

		int bad_move	= m - correct_num;
		int good_move	= good_suffix_table[correct_num];

		if (bad_shift_table.find(text[i - correct_num]) != bad_shift_table.end())
		{
			bad_move = bad_shift_table[text[i - correct_num]] - correct_num;
		}
		if (bad_move <= 0)
		{
			bad_move = 1;
		}

		i += (bad_move > good_move) ? bad_move : good_move;
	}

	delete good_suffix_table;
	return index_table;
}

map<char16_t, int>		StringMatching::generate_shift_table()
{
	map<char16_t, int> table;
	int m = pattern.size();

	for (int i = m - 2; i >= 0; i--)
	{
		if (table.find(pattern[i]) == table.end())
		{
				table[pattern[i]] = m - 1 - i ;
		}
	}
	return table;
}

int*					StringMatching::generate_good_suffix_table()
{
	int		m					= pattern.size();
	int*	good_suffix_table	= new int[m]();
	int* shift = new int[m]();

	shift[0] = m;
	good_suffix_table[m - 1] = m;
	for (int i = m - 2; i >= 0; i--)
	{
		int j ;
		for (j = 0; j <= i; j++)
		{
			if (pattern[i - j] != pattern[m - 1 - j])
			{
				break;
			}
		}
		shift[(m - 1) - i] = j;
		good_suffix_table[i] = m;
	}


	for (int i = m - 1; i >= 0; i--)
	{
		if (shift[i] == m - i)
		{
			for (int j = m - i + 1 ; j < m ; j++)
			{
					good_suffix_table[j] = i;
			}
		}
	}

	for (int i = m - 1; i >= 1; i--)
	{
		good_suffix_table[shift[i]] = i;
	}
	good_suffix_table[0] = 0;
	delete[] shift;
	return good_suffix_table;
}

