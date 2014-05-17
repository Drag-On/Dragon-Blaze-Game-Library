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

#define LOG dbgl::Log::get()

namespace dbgl
{
    /**
     * @brief Implements methods to log errors to standard output and logfile
     */
    class Log
    {
	public:
	    /**
	     * @brief
	     */
	    enum class Level
	    {
		DBG, //!< DBG
		INFO,//!< INFO
		WARN,//!< WARN
		ERR  //!< ERR
	    };

	    /**
	     * Constructor
	     */
	    Log();

	    /**
	     * Destructor
	     */
	    virtual ~Log();

	    /**
	     * @return Pointer to log object
	     */
	    static Log* get();

	    /**
	     * Free memory of log object
	     */
	    static void del();

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
	     */
	    template <typename... Args> void debug(const char* format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in info mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     */
	    template <typename... Args> void info(const char* format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in warning mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     */
	    template <typename... Args> void warning(const char* format, Args... args);

	    /**
	     * @brief Logs messages in case the logger is in error mode or lower
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     * @details The placeholder for (any) variable is %. To print the character '%' you have to type '%%'.
	     */
	    template <typename... Args> void error(const char* format, Args... args);

	private:
	    Level m_logLevel;
	    std::streambuf* m_pOldCout, *m_pOldCerr;

	    static const int m_maxBuffer = 1024;
	    static Log* s_pInstance;

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
	     * @brief Formats a message
	     * @param[out] msg String to write message to
	     * @param format Format string
	     * @param args Arguments to replace in \p format
	     */
	    template <typename T, typename... Args> void format(std::string& msg, const char* format, T val, Args... args);

	    /**
	     * @brief Dummy method used to stop recursion
	     * @param[out] msg String to write message to
	     * @param format Format string
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

