#include "Requests.h"


//parse line into words
vector<string> Requests::parseToWords(string line)
{
	vector<string> parsedLine;
	string word = "";
	//read words from one line
	for (size_t i = 0; i <= line.length(); i++)
	{
		while (isalpha(line[i]) && i <= line.length())
		{
			char c = tolower(line[i]);
			word = word + c;
			i++;
		}
		if (word != "") parsedLine.push_back(word);
		word = "";
	}
	return parsedLine;
}

string Requests::findMinimalElement(vector <pair<string, int>> toDelete)
{
	string min = toDelete[0].first;
	//find minimal element
	for (size_t k = 1; k < toDelete.size(); k++)
	{
		if (min.compare(toDelete[k].first) > 0)
		{
			min = toDelete[k].first;
		}
	}
	return min;
}

void Requests::processRequestsFromFile(string soubor_dotazy)
{
	//process dotazy
	ifstream dotazy(soubor_dotazy);
	if (dotazy.is_open() && dotazy.good())
	{
		//process soubor_dotazy
		string line;
		while (getline(dotazy, line))
		{
			if (line == "") break;
			string word = "";
			vector <string> allWords = parseToWords(line); //parsed line
			processWords(allWords);
		}
	}
	else cout << "File soubor_dotazy does not exist";
}

void Requests::processRequestsFromConsole()
{
	string line;
	getline(cin, line);
	while (line != "") //ending input with newline
	{
		vector<string> allWords;
		allWords = parseToWords(line);
		processWords(allWords);
		getline(cin, line);
	}
}

//save output of program to file
void Requests::processWords(vector<string> allWords)
{
	if (allWords.empty())
	{
		cout << "No result \n \n";
	}
	else
	{
		bool allExist = true;
		for (string word : allWords)
		{
			if (_index.invIndex.find(word) == _index.invIndex.end())
			{
				allExist = false;
				break;
			}
		}
		if (!allExist) cout << "No result \n \n";
		else
		{
			//all words exist in invIndex
			//save their occurences into allSets (pairs of identifiers and positions)
			vector <set<pair<string, int>, set_compare>> allSets;
			for (const string word : allWords)
			{
				auto s = _index.invIndex.at(word);
				allSets.push_back(s);
			}
			//find union of all sets in allWords
			vector <pair<string, int>> allUnions;
			bool unionExists = true;
			do
			{
				//create a vector of first pairs in every element of allSets vector
				vector <pair<string, int>> tempSets;
				for (size_t i = 0; i < allSets.size(); i++)
				{
					auto it = allSets[i].begin();
					if (it == allSets[i].end())
					{
						unionExists = false;
						break;
					}
					else
					{
						tempSets.push_back(*it);
					}
				}
				if (unionExists)
				{
					//vector tempSets now contains first pairs of each set
					//compare
					bool areTheSame = true;
					for (size_t j = 0; j < tempSets.size() - 1; j++)
					{
						if (tempSets[j].first != tempSets[j + 1].first)
						{
							areTheSame = false;
							break;
						}
					}
					if (areTheSame)
					{
						//if there was union
						allUnions.push_back(tempSets[0]); //add first element
						for (size_t j = 0; j < allSets.size(); j++) //erase all elements from the first position
						{
							auto iterSets = allSets[j].begin();
							if (iterSets != allSets[j].end()) allSets[j].erase(iterSets);
						}

					}
					else
					{
						//no union
						//delete all minimal elements
						string min = findMinimalElement(tempSets);
						for (size_t k = 0; k < allSets.size(); k++)
						{
							auto iterSets = allSets[k].begin();
							if (allSets[k].begin()->first == min)
							{
								allSets[k].erase(iterSets);
							}
						}
					}
				}
			} while (unionExists);
			//write out the output
			if (allUnions.empty())
			{
				//allUnions is empty, write "No result"
				cout << "No result \n \n";
			}
			else
			{
				//return all unions from allUnions
				for (pair<string, int> tempUnion : allUnions) //pairs of <identifier, starting position>
				{
					for (size_t j = 0; j < _database.allArticles.size(); j++)
					{
						if (_database.allArticles[j].identifier == tempUnion.first)
						{
							cout << "[" << tempUnion.first << "] " << _database.allArticles[j].name << " \n"; //first line
																											 //first 75 chars
							for (int pos = 0; pos < 75; pos++)
							{
								if (_database.allArticles[j].content[pos + tempUnion.second] == '\0')
									break;
								else cout << _database.allArticles[j].content[pos + tempUnion.second];
							}
							cout << "... \n"; //second line
							break;
						}
					}
				}
				cout << "\n";
			}
		}
	}
}


Requests::~Requests()
{
}
