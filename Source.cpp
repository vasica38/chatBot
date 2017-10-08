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
string name;
string age;
string occupation;
string moodAtWork;

int main()
{
	std::vector<int> lol{ 1,2,3,4 };
	//std::cout << boost::algorithm::is_sorted(lol);

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
					cout << "BOT:" << getRandomAnswer(user, i) << "\n";
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

			cout << "BOT:" << getRandomAnswer(bot, nr) << "\n";
			std::string textFromUser;
			std::cout << "USER:";
			std::getline(std::cin, textFromUser);
			string answer = getAnswer(bot[nr].first, textFromUser, scopes[bot[nr].first]);

			if (answer == "none") continue;

			if (scopes[bot[nr].first] == "name")
			{
				name = answer;
			}

			if (scopes[bot[nr].first] == "age")
			{
				age = answer;
			}

			if (scopes[bot[nr].first] == "occupation")
			{
				occupation = answer;
			}

			if (scopes[bot[nr].first] == "occupationMood")
			{
				moodAtWork = answer;
			}
			whoToAsk = 0;
		}
	}
		
	std::cin.get();

	return 0;
}