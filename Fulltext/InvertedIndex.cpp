#include "InvertedIndex.h"


string InvertedIndex::toLowerCase(string word)
{
	int i = 0;
	while (word[i])
	{
		word[i] = tolower(word[i]);
		i++;
	}
	return word;
}

void InvertedIndex::addWord(string word, int position, const Article & tempArticle)
{
	//word is found
	if (word != "")
	{
		//change to lower case
		word = toLowerCase(word);
		//check if the word was found before in this article
		//if yes, do nothing, if no, add the word

		if (invIndex.find(word) != invIndex.end())
		{
			//if word is in map
			bool addWord = true;
			auto pair_keyValue = *invIndex.find(word);
			for (auto iter = pair_keyValue.second.begin(); iter != pair_keyValue.second.end(); ++iter)
			{
				if ((iter->first) == tempArticle.identifier)
				{
					addWord = false;
				}
			}
			if (addWord)
			{
				pair <string, int> p = make_pair(tempArticle.identifier, position);
				invIndex[word].insert(p);
			}
		}
		else
		{
			set<pair<string, int>, set_compare> s;
			pair <string, int> p = make_pair(tempArticle.identifier, position);
			s.insert(p);
			invIndex[word] = s;
		}
	}
}

void InvertedIndex::saveWords(const ArticleDatabase & database)
{
	//save words to multimap invIndex by going through all articles
	for (Article tempArticle : database.allArticles)
	{
		string toParse = tempArticle.content;
		string word = "";
		int position = 0;
		int i = 0;
		for (string::iterator it = toParse.begin(); it != toParse.end(); ++it)
		{
			i++;
			char c = *it;
			if (isalpha(c))
			{
				word = word + c;
			}
			else
			{
				addWord(word, position, tempArticle);
				word = "";
				position = i;
			}
		}
		if (word.length() > 0) addWord(word, position, tempArticle);
	}
}

InvertedIndex::InvertedIndex()
{
}


InvertedIndex::~InvertedIndex()
{
}
