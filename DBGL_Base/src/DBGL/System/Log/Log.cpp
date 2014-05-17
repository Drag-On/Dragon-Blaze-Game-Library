//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    // Init static variables
    Log* Log::s_pInstance = nullptr;
    Log::Logger Log::dbg(Level::DBG);
    Log::Logger Log::inf(Level::INFO);
    Log::Logger Log::wrn(Level::WARN);
    Log::Logger Log::err(Level::ERR);

    Log::Log()
    {
	m_logLevel = Level::WARN;

	// Get current time
	auto time = getCurTime(true);

	writeLog("-----------------\n");
	writeLog("-----Logfile-----\n");
	writeLog("-----------------\n");
	writeLog("%s\n", time.c_str());
	writeLog("-----------------\n");

	// Redirect std streams
	m_pOldCout = std::cout.rdbuf(inf.rdbuf());
	m_pOldCerr = std::cerr.rdbuf(err.rdbuf());
    }

    Log::~Log()
    {
	// Restore original std streams
	std::cout.rdbuf(m_pOldCout);
	std::cerr.rdbuf(m_pOldCerr);
    }

    Log* Log::get()
    {
	if (!Log::s_pInstance)
	{
	    Log::s_pInstance = new Log();
	}
	return Log::s_pInstance;
    }

    void Log::del()
    {
	if (Log::s_pInstance)
	{
	    delete (Log::s_pInstance);
	    Log::s_pInstance = NULL;
	}
    }

    void Log::setLogLevel(Level lvl)
    {
	m_logLevel = lvl;
    }

    void Log::debug(const char* msg, ...)
    {
	if (m_logLevel <= Level::DBG)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    auto time = getCurTime();
	    fprintf(stdout, "%s: DEBUG: %s\n", time.c_str(), buffer);
	    fflush (stdout);

	    writeLog("%s: DEBUG: %s\n", time.c_str(), buffer);
	}
    }

    void Log::info(const char* msg, ...)
    {
	if (m_logLevel <= Level::INFO)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    auto time = getCurTime();
	    fprintf(stdout, "%s: INFO: %s\n", time.c_str(), buffer);
	    fflush (stdout);

	    writeLog("%s: INFO: %s\n", time.c_str(), buffer);
	}
    }

    void Log::warning(const char* msg, ...)
    {
	if (m_logLevel <= Level::WARN)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    auto time = getCurTime();
	    fprintf(stderr, "%s: WARNING: %s\n", time.c_str(), buffer);
	    fflush (stderr);

	    writeLog("%s: WARNING: %s\n", time.c_str(), buffer);
	}
    }

    void Log::error(const char* msg, ...)
    {
	if (m_logLevel <= Level::ERR)
	{
	    char buffer[m_maxBuffer]; // Buffer for arguments
	    va_list pArgList; // List of arguments

	    // Make string from arguments
	    va_start(pArgList, msg);
	    vsprintf(buffer, msg, pArgList);
	    va_end(pArgList);

	    auto time = getCurTime();
	    fprintf(stderr, "%s: ERROR: %s\n", time.c_str(), buffer);
	    fflush (stderr);

	    writeLog("%s: ERROR: %s\n", time.c_str(), buffer);
	}
    }

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

    std::string Log::getCurTime(bool date)
    {
	auto now = std::chrono::system_clock::now();
	auto now_c = std::chrono::system_clock::to_time_t(now);

	char buf[m_maxBuffer];
	std::strftime(buf, sizeof(buf), date?"%c":"%X", std::localtime(&now_c));

	return std::string(buf);
    }

    Log::Logger::LogBuf::LogBuf(Level loglevel) : m_loglevel(loglevel)
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
	    case Level::DBG:
		LOG->debug(str().c_str());
		break;
	    case Level::INFO:
		LOG->info(str().c_str());
		break;
	    case Level::WARN:
		LOG->warning(str().c_str());
		break;
	    case Level::ERR:
		LOG->error(str().c_str());
		break;
	}
	str("");
	return 0;
    }

    Log::Logger::Logger(Level loglevel) : std::ostream(new LogBuf(loglevel))
    {
    }

    Log::Logger::~Logger()
    {
    }

} /* namespace DBGL */
