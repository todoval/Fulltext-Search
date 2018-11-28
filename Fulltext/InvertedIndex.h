#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Article.h"
#include <ctype.h>
#include <map>
#include <algorithm>
#include <set>
#include "ArticleDatabase.h"


//structure for sorting words in invIndex by first pair value
struct set_compare
{
	bool operator() (const pair<string, int> &i, const pair<string, int> &j) const
	{
		return i.first < j.first;
	}
};

class InvertedIndex
{
private:
	string toLowerCase(string word);
	void addWord(string word, int position, const Article & tempArticle);

public:
	void saveWords(const ArticleDatabase& database);

	map<string, set<pair<string, int>, set_compare>> invIndex;

	InvertedIndex();
	~InvertedIndex();
};

