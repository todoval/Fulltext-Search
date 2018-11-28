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
#include "InvertedIndex.h"

class Requests
{
private:
	vector<string> parseToWords(string line);
	const ArticleDatabase & _database;
	const InvertedIndex & _index;
	string findMinimalElement(vector <pair<string, int>> toDelete);

public:
	void processRequestsFromFile(string soubor_dotazy);
	void processRequestsFromConsole();
	void processWords(vector<string> allWords);

	Requests(const ArticleDatabase& database, const InvertedIndex& index) : _database(database), _index(index) {};
	~Requests();
};

