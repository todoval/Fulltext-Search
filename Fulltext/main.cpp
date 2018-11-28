//Lucia Todova

#include "Article.h"
#include "InvertedIndex.h"
#include "Requests.h"
#include <ctype.h>

using namespace std;


int main(int argc, char** argv)
{ 
	ArticleDatabase database;
	InvertedIndex invIndex;

	if (argc > 3 || argc < 2)
	{
		cout << "Wrong number of arguments" << endl;
		exit(0);
	}
	string soubor_clanky = argv[1];
	if (database.processInput(soubor_clanky)) //if soubor_clanky exists
	{
		invIndex.saveWords(database);
		Requests dotazy(database, invIndex);
		if (argc == 2)
		{
			dotazy.processRequestsFromConsole();
		}
		else
		{
			string soubor_dotazy = argv[2];
			ifstream requests(soubor_dotazy);
			if (requests.good()) //soubor_dotazy exists
			{
				dotazy.processRequestsFromFile(soubor_dotazy);
			}
			else dotazy.processRequestsFromConsole();
		}
	}
}

