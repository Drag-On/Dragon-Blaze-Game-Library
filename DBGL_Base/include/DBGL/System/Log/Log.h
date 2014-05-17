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
	     * @param msg Message to log
	     */
	    void debug(const char* msg, ...);

	    /**
	     * @brief Logs messages in case the logger is in info mode or lower
	     * @param msg Message to log
	     */
	    void info(const char* msg, ...);

	    /**
	     * @brief Logs messages in case the logger is in warning mode or lower
	     * @param msg Message to log
	     */
	    void warning(const char* msg, ...);

	    /**
	     * @brief Logs messages
	     * @param msg Message to log
	     */
	    void error(const char* msg, ...);

	private:
	    Level m_logLevel;
	    std::streambuf* m_pOldCout, *m_pOldCerr;

	    static const int m_maxBuffer = 1024;
	    static Log* s_pInstance;

	    /**
	     * @brief Writes a message to logfile
	     * @param msg Message to write
	     */
	    void writeLog(const char* msg, ...);

	    /**
	     * @brief Generates a string with current date and time.
	     * @param date Flag indicating, if a date string should be appended
	     * @return A string with the current time
	     */
	    std::string getCurTime(bool date = false);

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

#endif /* LOG_H_ */

