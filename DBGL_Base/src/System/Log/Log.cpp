//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "System/Log/Log.h"

namespace dbgl
{

    // Init static variables
    Log* Log::s_pInstance = nullptr;
    Log::Logger Log::dbg(LOGLEVEL::DBG);
    Log::Logger Log::inf(LOGLEVEL::INFO);
    Log::Logger Log::wrn(LOGLEVEL::WARN);
    Log::Logger Log::err(LOGLEVEL::ERR);

    /**
     * Constructor
     */
    Log::Log()
    {
	m_logLevel = WARN;

	// Get current time
	const char* time = getCurTime(true);

	writeLog("-----------------\n");
	writeLog("-----Logfile-----\n");
	writeLog("-----------------\n");
	writeLog("%s\n", time);
	writeLog("-----------------\n");

	delete[] (time);

	// Redirect std streams
	m_pOldCout = std::cout.rdbuf(inf.rdbuf());
	m_pOldCerr = std::cerr.rdbuf(err.rdbuf());
    }

    /**
     * Destructor
     */
    Log::~Log()
    {
	// Restore original std streams
	std::cout.rdbuf(m_pOldCout);
	std::cerr.rdbuf(m_pOldCerr);
    }

    /**
     * @return Pointer to log object
     */
    Log* Log::get()
    {
	if (!Log::s_pInstance)
	{
	    Log::s_pInstance = new Log();
	}
	return Log::s_pInstance;
    }

    /**
     * Free memory of log object
     */
    void Log::del()
    {
	if (Log::s_pInstance)
	{
	    delete (Log::s_pInstance);
	    Log::s_pInstance = NULL;
	}
    }

    /**
     * @brief Set the severity of messages to log
     * @param lvl Minimum level messages need to have to be logged
     */
    void Log::setLogLevel(int lvl)
    {
	m_logLevel = lvl;
    }

    /**
     * @brief Logs messages in case the logger is in debug mode
     * @param msg Message to log
     */
    void Log::debug(const char* msg, ...)
    {
	if (m_logLevel <= DBG)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    const char* time = getCurTime();
	    fprintf(stdout, "%s: DEBUG: %s\n", time, buffer);
	    fflush (stdout);

	    writeLog("%s: DEBUG: %s\n", time, buffer);
	    delete (time);
	}
    }

    /**
     * @brief Logs messages in case the logger is in info mode or lower
     * @param msg Message to log
     */
    void Log::info(const char* msg, ...)
    {
	if (m_logLevel <= INFO)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    const char* time = getCurTime();
	    fprintf(stdout, "%s: INFO: %s\n", time, buffer);
	    fflush (stdout);

	    writeLog("%s: INFO: %s\n", time, buffer);
	    delete (time);
	}
    }

    /**
     * @brief Logs messages in case the logger is in warning mode or lower
     * @param msg Message to log
     */
    void Log::warning(const char* msg, ...)
    {
	if (m_logLevel <= WARN)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    const char* time = getCurTime();
	    fprintf(stderr, "%s: WARNING: %s\n", time, buffer);
	    fflush (stderr);

	    writeLog("%s: WARNING: %s\n", time, buffer);
	    delete (time);
	}
    }

    /**
     * @brief Logs messages
     * @param msg Message to log
     */
    void Log::error(const char* msg, ...)
    {
	if (m_logLevel <= ERR)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    const char* time = getCurTime();
	    fprintf(stderr, "%s: ERROR: %s\n", time, buffer);
	    fflush (stderr);

	    writeLog("%s: ERROR: %s\n", time, buffer);
	    delete (time);
	}
    }

    /**
     * @brief Writes a message to logfile
     * @param msg Message to write
     */
    void Log::writeLog(const char* msg, ...)
    {
	char buffer[m_maxBuffer]; // Buffer for arguments
	va_list pArgList; // List of arguments

	// Make string from arguments
	va_start(pArgList, msg);
	vsprintf(buffer, msg, pArgList);
	va_end(pArgList);

	std::ofstream out("Logfile.txt", std::ios::app);
	out.write(buffer, strlen(buffer));
	out.close();
    }

    /**
     * @brief Generates a string with current date and time. Needs to be deleted manually!
     * @param date Flag indicating, if a date string should be appended
     * @return A string with the current time
     */
    const char* Log::getCurTime(bool date)
    {
	// Get current time
	time_t now = time(0);
	struct tm tstruct;
	char* buf = new char[80];
	tstruct = *localtime(&now);
	if (date)
	    strftime(buf, 80, "%Y-%m-%d.%X", &tstruct);
	else
	    strftime(buf, 80, "%X", &tstruct);
	return buf;
    }

    Log::Logger::LogBuf::LogBuf(LOGLEVEL loglevel) : m_loglevel(loglevel)
    {
    }

    Log::Logger::LogBuf::~LogBuf()
    {
	pubsync();
    }

    int Log::Logger::LogBuf::sync()
    {
	switch(m_loglevel)
	{
	    case DBG:
		LOG->debug(str().c_str());
		break;
	    case INFO:
		LOG->info(str().c_str());
		break;
	    case WARN:
		LOG->warning(str().c_str());
		break;
	    case ERR:
		LOG->error(str().c_str());
		break;
	}
	str("");
	return 0;
    }

    Log::Logger::Logger(LOGLEVEL loglevel) : std::ostream(new LogBuf(loglevel))
    {
    }

    Log::Logger::~Logger()
    {
    }

} /* namespace DBGL */
