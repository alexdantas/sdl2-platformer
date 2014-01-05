#ifndef CONFIG_H_DEFINED
#define CONFIG_H_DEFINED

#include <map>
#include <string>

#define COMMENT_CHAR '#'

/// Handles global game customizations and settings based
/// on a config file.
///
/// @note It parses files with the INI format. Here's an example:
///
///     # Comments start with '#'
///
///     key       = value
///     other_key = 22
///     some_val  = true
///
/// ## Usage
///
///     // TODO
///
class Config
{
public:
	/// Starts the class and waits for you to call `load()`.
    Config();

    /// Opens, loads and parses configuration file `filename`.
	static bool load(std::string filename);

    /// Reloads same configuration file last called with `load()`.
    static bool reload();

	/// Tells if the configuration has `key` defined.
	static bool has(std::string key);

	/// Returns the value defined with `key`.
	///
	/// @return Empty string if value is not found.
	///
	static std::string get(std::string key);

	/// Returns the boolean value associated with `key`.
	///
	/// @note It recognizes "true" and "yes" as valid
	///       strings. Everything else is false.
	///
	static bool getBool(std::string key, bool defaultVal);

	/// Returns the int value associated with `key`.
	///
	static int getInt(std::string key, int defaultVal);

    // /// Restarts all values with their hardcoded defaults.
    // static void reset();

private:
	/// Filename of the last call to `load()`.
	static std::string filename;

	/// Actual internal map of std::string keys to values.
	static std::map<std::string, std::string> config;
};

#endif /* CONFIG_H_DEFINED */

