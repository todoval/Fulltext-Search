#include "ArticleDatabase.h"

bool ArticleDatabase::isIdentifier(string line)
{
	bool isId = true;
	for (size_t i = 0; i < line.length(); i++)
	{
		if (!isdigit(line[i]) && !isupper(line[i]))
		{
			isId = false;
			break;
		}
	}
	return isId;
}

bool ArticleDatabase::processInput(string soubor_clanky)
{
	//process clanky
	ifstream infile(soubor_clanky);
	if (infile.is_open() && infile.good())
	{
		string line;
		Article tempArt;
		tempArt.resetArticle(); //reset article to default values
		if (infile.good())
		{
			getline(infile, line);
			while (infile.good())
			{
				//process soubor_clanky
				if (line.length() <= 10 && isIdentifier(line))
				{
					tempArt.resetArticle();
					//get identifier
					tempArt.identifier = line;
					//get name
					getline(infile, line);
					if (line.length() <= 60)
						tempArt.name = line;
					else cout << "Name of " + tempArt.identifier + " is not in the right format";
				}
				//get content
				getline(infile, line);
				while (line.length() > 10 && !isIdentifier(line) && infile.good())
				{
					tempArt.content = tempArt.content + line;
					getline(infile, line);
				}
				//process tempArt
				if (tempArt.identifier != "")
					allArticles.push_back(tempArt);
			}
			infile.close();
		}
		return true;
	}
	else
	{
		cout << "soubor_clanky.txt does not exist \n";
		return false;
	}
}

ArticleDatabase::ArticleDatabase()
{
}


ArticleDatabase::~ArticleDatabase()
{
}
