//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <stdio.h>
#include <cstdarg>
#include <cstring>
#include <ctime>
#include "DBGL/System/OS/OS.h"

#define LOG dbgl::Log::getDefault()

namespace dbgl
{
    /**
     * @brief Implements methods to log errors to standard output and logfile
     */
    class Log
    {
	public:
	    /**
	     * @brief Log severity level
	     */
	    enum class Level
	    {
		DBG, //!< DBG Log all messages
		INFO,//!< INFO Log all messages marked as "info", "warning" or "error"
		WARN,//!< WARN Log all messages marked as "warning" or "error"
		ERR  //!< ERR Log all messages marked as "error"
	    };

	    /**
	     * @brief Constructor
	     * @param filename Path and name of the file to write to
	     * @param bashOutput Indicates if all log messages shall be mirrored on std::out / std::err
	     * @param redirectStd Indicates if all mesages to std::out / std::err shall be written to log as well
	     */
	    Log(std::string filename, bool bashOutput = true, bool redirectStd = false);

	    /**
	     * @brief Destructor
	     */
	    virtual ~Log();

	    /**
	     * @brief Creates a default logfile if not already present
	     * @return Pointer to default logfile
	     */
	    static Log& getDefault();

	    /**
	     * @brief Set the severity of messages to log
	     * @param lvl Minimum level messages need to have to be logged
	     */
	    void setLogLevel(Level lvl);

	    /**
	     * @brief Logs messages in case the logger is in debug mode
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void debug(const char* format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in debug mode
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void debug(std::string const& format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in info mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void info(const char* format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in info mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void info(std::string const& format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in warning mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void warning(const char* format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in warning mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void warning(std::string const& format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in error mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void error(const char* format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in error mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename... Args> void error(std::string const& format, Args... args);

	private:
	    Level m_logLevel;
	    std::string m_filename;
	    bool m_bashOutput = true;
	    bool m_redirectStd = false;
	    std::streambuf* m_pOldCout, *m_pOldCerr;

	    static const int m_maxBuffer = 1024;

	    /**
	     * @brief Writes a message to logfile
	     * @param msg Message to write
	     */
	    void writeLog(std::string msg);

	    /**
	     * @brief Generates a string with current date and time.
	     * @param date Flag indicating, if a date string should be appended
	     * @return A string with the current time
	     */
	    std::string getCurTime(bool date = false);

	    /**
	     * @brief Generates a brief OS description
	     * @return String describing the operating system running the application
	     */
	    std::string getOSDescription();

	    /**
	     * @brief Formats a message
	     * @param[out] msg String to write message to
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    template <typename T, typename... Args> void format(std::string& msg, const char* format, T val, Args... args);

	    /**
	     * @brief Dummy method used to stop recursion
	     * @param[out] msg String to write message to
	     * @param format Format string
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     * 		It's also possible to specify floating point accuracy by using %{precision}.
	     */
	    void format(std::string& msg, const char* format);

	    /**
	     * @brief Inner class used for streams
	     */
	    class Logger : public std::ostream
	    {
		private:
		    /**
		     * @brief Buffer for Logger class
		     */
		    class LogBuf: public std::stringbuf
		    {
			private:
			    Level m_loglevel;
			public:
			    LogBuf(Level loglevel);
			    ~LogBuf();
			    int sync();
		    };
		public:
		    Logger(Level loglevel);
		    ~Logger();
	    };
	    /**
	     * @brief Debug stream
	     */
	    static Logger dbg;
	    /**
	     * @brief Info stream
	     */
	    static Logger inf;
	    /**
	     * @brief Warning stream
	     */
	    static Logger wrn;
	    /**
	     * @brief Error stream
	     */
	    static Logger err;
    };

} /* namespace dbgl */


#include "Log.imp"

#endif /* LOG_H_ */

