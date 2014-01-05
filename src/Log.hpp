#ifndef LOG_H_DEFINED
#define LOG_H_DEFINED

#include <iostream>
#include <fstream>
#include <string>

/// Stores information on standard output streams or files.
///
/// By default this class outputs all logging to standard
/// output (_stdout_) and standard error output (_stderr_).
/// You can change that with *setOutput()*.
///
/// @note When logging on _stdout_, it uses _terminal escape codes_.
///       Basically they allow the output to be colorful at
///       terminals.
///       The strange thing is that if you manually redirect
///       _stdout_ to a file you'll se strange stuff like \e[1;31m.
///       To disable this behaviour, call *colors(false)*.
///
/// With this class you can log different levels of information.
/// Currently we have _Error_, _Warning_, _Debug_ and _normal_ logs.
/// Each get printed with it's prefix.
///
/// ## How to use
///
///     // It is a "global" static class.
///     Log::error("Class foo Method bar");
///     Log::warning("You shouldn't do that!");
///
///     Log::debugMode(true);
///     Log::debug("This will only be shown when debugMode(true)");
///
///     Log::colors(false);
///     Log::log("No more colors!");
///
/// ## For developers
///
/// This is a standalone class, can be inserted on any project
/// regardless of library (assuming you have standard C++ I/O
/// classes).
///
class Log
{
public:
	/// Logs *msg* with prefix "Error: ".
	///
	/// @note By default logs to _stderr_.
	static void error(std::string msg);

	/// Logs *msg* with prefix "Warning: ".
	///
	/// @note By default logs to _stderr_.
	static void warning(std::string msg);

	/// Logs *msg*.
	///
	/// @note By default logs to _stdout_.
	static void log(std::string msg);

	/// Logs `msg` without end of line.
	static void log_raw(std::string msg);

	/// Logs *msg* with prefis "Debug: ".
	///
	/// @note Only gets logged if debug mode is on.
	/// @note By default logs to _stdout_.
	static void debug(std::string msg);

	static void verbose(std::string msg);

	/// Turns debug on/off.
	/// This tells if all debug messages will be ignored.
	///
	/// @note By default it is turned off.
	static void debugMode(bool option);

	/// Turns verbose on/off.
	/// This tells if all verbose messages will be ignored.
	///
	/// @note By default it is turned off.
	static void verboseMode(bool option);

	/// Enables/disables terminal escape codes at _stdout_ output.
	///
	static void colors(bool option);

	static void clearLine();

	static std::string intToString(int num);

private:
	static bool isDebugMode;     ///< Tells if we're on debug mode.
	static bool isVerboseMode;   ///< Tells if we're on verbose mode.
	// static std::ostream& stdout; ///< Standard output stream
	// static std::ostream& stderr; ///< Standard error stream
	// static bool isUsingFiles;

	static bool haveEscapeCodes;
};

#endif /* LOG_H_DEFINED */

