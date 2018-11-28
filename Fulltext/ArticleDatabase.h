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

using namespace std;

class ArticleDatabase
{
private:
	bool isIdentifier(string line);

public:
	bool processInput(string soubor_clanky);
	vector<Article> allArticles;

	ArticleDatabase();
	~ArticleDatabase();
};

