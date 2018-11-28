#pragma once
#include <string>

using namespace std;

class Article
{

public:
	Article();
	~Article();
	string identifier;
	string name;
	string content;

	void resetArticle();

};

