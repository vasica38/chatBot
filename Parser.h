#ifndef PARSER_H
#define PARSER_H

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>

#include <string>
#include <vector>

#include "ParserEnum.h"

using namespace std;

void parse(std::string& filename, vector < pair<string, vector<string> > >& user, vector < pair<string, vector<string> > >& bot, map <string, string>& scopes) {
	using boost::property_tree::ptree;

	ptree pt;

	try {
		read_xml(filename, pt);
	}
	catch (std::exception& e)
	{
		std::cout << "Loading xml Error: " << e.what() << "\n";
	}

	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("aiml"))
	{
		if (v.first == "category")
		{
			string pattern = v.second.get<std::string>("pattern");
			string type = v.second.get<std::string>("type");
			string scope = v.second.get<std::string>("scope");
			scopes[pattern] = scope;
			//std::cout << type;

			vector<string> templates{ };

			BOOST_FOREACH(ptree::value_type const& v1, v.second.get_child("template"))
			{
				if (v1.first == "li")
				{
					std::string lol = v1.second.data();
					//std::cout << lol << "+\n";
					templates.push_back(lol);
				}
			}

			if (type == "user") {
				user.push_back({ pattern, templates });
			}
			else
			{
				bot.push_back({ pattern, templates });
			}
		}
	}
 }

bool isMatching(string wildCard, string text)
{
	boost::regex e(wildCard);
	boost::match_results<std::string::const_iterator> what;

	if (boost::regex_match(text, what, e, boost::match_default) == 0)
	{
		return false;
	}
	try
	{
		if (what[0].matched)
		{
			return true;
		}

	}
	catch (const std::exception&)
	{

	}

	return false;
}

std::string getAnswer(string wildCard, string text, string scope)
{
	if (scope == "none") {
		return "none";
	}

	boost::regex e(wildCard);
	boost::match_results<std::string::const_iterator> what;

	if (boost::regex_match(text, what, e, boost::match_default) == 0)
	{
		return "none";
	}

	if (scope == "age")
	{
		return what[3];
	}

	if (scope == "name")
	{
		return what[4];
	}

	return "none";
}




#endif // !PARSER_H
