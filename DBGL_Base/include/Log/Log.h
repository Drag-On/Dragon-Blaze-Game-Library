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

#include <stdio.h>
#include <fstream>
#include <cstdarg>
#include <string.h>
#include <time.h>

#define LOG DBGL::Log::get()

namespace DBGL
{

    /**
     * Defines what is actually logged
     */
    enum LOGLEVEL
    {
	DBG,
	INFO,
	WARN,
	ERR
    };

    /**
     * @brief Implements methods to log errors to standard output and logfile
     */
    class Log
    {
	public:

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
	    void setLogLevel(int lvl);

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
	    int _logLevel;
	    static const int _maxBuffer = 1024;

	    static Log* s_pInstance;

	    /**
	     * @brief Writes a message to logfile
	     * @param msg Message to write
	     */
	    void writeLog(const char* msg, ...);

	    /**
	     * @brief Generates a string with current date and time. Needs to be deleted manually!
	     * @param date Flag indicating, if a date string should be appended
	     * @return A string with the current time
	     */
	    const char* getCurTime(bool date = false);
    };

} /* namespace DBGL */

#endif /* LOG_H_ */

