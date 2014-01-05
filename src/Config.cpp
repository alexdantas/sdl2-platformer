#include <fstream>
#include <vector>
#include "Config.hpp"
#include "Utils.hpp"
#include "Log.hpp"

// Initializing static thingies.
std::string Config::filename;
std::map<std::string, std::string> Config::config;

Config::Config()
{ }

bool Config::load(std::string filename)
{
	Config::config.clear();

	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		Log::error("Config::load: Couldn't open '" + filename + "'");
		return false;
	}

	// This gets a single line, splits it based on '=' and
	// stores on `current` first the key and then the value.
	//
	// After checking for key duplicates, it inserts on our
	// map.

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line, '\n');

		if (line.empty())
			continue;

		// Ignoring comments
		if (line[0] == COMMENT_CHAR)
			continue;

		std::vector<std::string> current = Utils::String::split(line, '=');

		if (Config::has(current.front()))
		{
			Log::warning("Config::load: Existing key '" +
			             current.front() +
			             "' that maps to '" +
			             current.back() +
			             "'");
			continue;
		}

		Config::config.insert(std::pair<std::string, std::string>(current.front(), current.back()));
	}

	return true;
}
bool Config::reload()
{
	return (Config::load(Config::filename));
}
bool Config::has(std::string key)
{
	// Ugly type!
	std::map<std::string, std::string>::iterator it = Config::config.find(key);

	return (it != Config::config.end());
}
std::string Config::get(std::string key)
{
	std::map<std::string, std::string>::iterator it = Config::config.find(key);

	// I wonder if this is redundant, since the user
	// will HAVE to check this outside anyways.
	if (it == Config::config.end())
	{

		Log::warning("Config::get: Tried to get unexisting key '" +
		             key +
		             "'");
		return "";
	}
	return (*it).second;
}
bool Config::getBool(std::string key, bool defaultVal)
{
	std::string value = Config::get(key);
	if (value.empty())
		return defaultVal;

	if ((value.compare("true") == 0) ||
	    (value.compare("yes")  == 0))
		return true;

	return false;
}
int Config::getInt(std::string key, int defaultVal)
{
	std::string value = Config::get(key);
	if (value.empty())
		return defaultVal;

	return Utils::stringToInt(value);
}

