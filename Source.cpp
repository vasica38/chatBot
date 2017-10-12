#include <iostream>
#include <boost\algorithm\cxx11\is_sorted.hpp>
#include <vector>
#include <fstream>
#include <map>

#include "Parser.h"

string getRandomAnswer(vector < pair<string, vector<string> > >& result, int index)
{
	srand(time(NULL));

	int random = rand() % result[index].second.size();

	return result[index].second[random];
}

void save(string name, string age, string occupation, string moodAtWork)
{
	ofstream f("save.xml");
	f << "<name>" << name << "</name>\n";
	f << "<age>" << age << "</age>\n";
	f << "<occupation>" << occupation << "</occupation>\n";
	f << "<moodAtWork>" << moodAtWork << "</moodAtWork>\n";

	f.close();
}

string name;
string age;
string occupation;
string moodAtWork;

bool nameIsSet = false;
bool ageIsSet = false;
bool occupationIsSet = false;
bool moodAtWorkIsSet = false;


string personalizeMessageName(string s)
{
	if (s[0] != '#') return s;
	string result = s;
	if (nameIsSet) {
		result.erase(result.begin(), result.begin() + 1);
		return name + result;
	}
	else
	{
		result.erase(result.begin(), result.begin() + 2);
		return result;
	}
}


int main()
{
	std::string filename("1.xml");
	vector < pair<string, vector<string> > > bot;
	vector < pair<string, vector<string> > > user;
	map <string, string> scopes;

	parse(filename, user, bot, scopes);
	//std::cout << result;

	//for (int i = 0; i < bot.size(); ++i)
	//{
	//	std::cout << bot[i].first << "\n";
	//	for (int j = 0; j < bot[i].second.size(); ++j)
	//	{
	//		std::cout << bot[i].second[j] << "\n";
	//	}
	//}
	bool botTurn = false;
	int whoToAsk = 0;
	while (1)
	{
		bool answerIsGiven{ false };

		if (!whoToAsk) {
			std::cout << "USER:";
			std::string textFromUser;
			std::getline(std::cin, textFromUser);


			std::transform(textFromUser.begin(), textFromUser.end(), textFromUser.begin(), ::toupper);


			for (int i = 0; i < user.size(); ++i)
			{
				if (isMatching(user[i].first, textFromUser))
				{
					answerIsGiven = true;
					cout << "BOT:" << personalizeMessageName(getRandomAnswer(user, i)) << "\n";
					break;
				}
			}
			whoToAsk++;
		}

		if (!answerIsGiven)
		{
			cout << "BOT:" << "I DON'T UNDERSTANT!\n";
		}

		if (whoToAsk) {
			srand(time(nullptr));
			int nr = rand() % bot.size();

			cout << "BOT:" << personalizeMessageName(getRandomAnswer(bot, nr)) << "\n";
			std::string textFromUser;
			std::cout << "USER:";
			std::getline(std::cin, textFromUser);
			string answer = getAnswer(bot[nr].first, textFromUser, scopes[bot[nr].first]);

			for (int i = 0; i < user.size(); ++i)
			{
				if (isMatching(user[i].first, textFromUser))
				{
					cout << "BOT:" << personalizeMessageName(getRandomAnswer(user, i)) << "\n";
					break;
				}
			}

			if (answer == "none") continue;

			if (scopes[bot[nr].first] == "name")
			{
				name = answer;
				nameIsSet = true;
			}

			if (scopes[bot[nr].first] == "age")
			{
				age = answer;
				ageIsSet = true;
			}

			if (scopes[bot[nr].first] == "occupation")
			{
				occupation = answer;
				occupationIsSet = true;
			}

			if (scopes[bot[nr].first] == "occupationMood")
			{
				moodAtWork = answer;
				moodAtWorkIsSet = true;
			}
			whoToAsk = 0;
		}
	}
		
	std::cin.get();

	return 0;
}