#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int count_word_symbols(string& word, string& symbols)
{
	int count = 0;
	for (int j = 0; j < word.length(); j++)
	{
		if (symbols.find(word[j]) != -1)
		{
			count++;
		}
	}
	return count;
}

string* split(string& line, int& n)
{
	string* words = new string[line.length()];
	int index = 0;
	int start = 0;
	while (start < line.length())
	{
		int next_space = line.find(' ', start);
		if (next_space == -1)
		{
			next_space = line.length();
		}

		string word = line.substr(start, next_space - start);
		words[index] = word;
		index++;
		start = next_space + 1;
	}
	n = index;
	return words;
}

void sort_words(string* words, int count, string& symbols)
{
	bool sorted;
	do
	{
		sorted = true;
		for (int i = 1; i < count; i++)
		{
			int count1 = count_word_symbols(words[i], symbols);
			int count2 = count_word_symbols(words[i - 1], symbols);
			if (count1 > count2)
			{
				swap(words[i], words[i - 1]);
				sorted = false;
			}
		}
	}
	while (!sorted);
}

int main()
{
	setlocale(LC_ALL, "russian");

	string symbols;
	getline(cin, symbols);

	ifstream f1("f1.txt");
	ofstream f2("f2.txt");

	while (!f1.eof())
	{
		string line;
		getline(f1, line);

		int count;
		string* words = split(line, count);

		sort_words(words, count, symbols);

		for (int i = 0; i < count; i++)
		{
			if (count_word_symbols(words[i], symbols))
			{
				f2 << words[i] << " ";
			}
		}

		delete[] words;
	}

	f1.close();
	f2.close();

	system("pause");
}
