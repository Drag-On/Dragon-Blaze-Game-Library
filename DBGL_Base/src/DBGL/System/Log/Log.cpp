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

    Log::Log(std::string filename, bool bashOutput, bool redirectStd)
    {
	m_logLevel = Level::WARN;
	m_filename = filename;
	m_bashOutput = bashOutput;
	m_redirectStd = redirectStd;

	// Get current time
	auto time = getCurTime(true);

	writeLog("-----------------\n");
	writeLog("-----Logfile-----\n");
	writeLog("-----------------\n");
	writeLog(time + "\n");
	writeLog("-----------------\n");

	// Redirect std streams
	if (m_redirectStd)
	{
	    m_pOldCout = std::cout.rdbuf(inf.rdbuf());
	    m_pOldCerr = std::cerr.rdbuf(err.rdbuf());
	}
    }

    Log::~Log()
    {
	// Restore original std streams
	if (m_redirectStd)
	{
	    std::cout.rdbuf(m_pOldCout);
	    std::cerr.rdbuf(m_pOldCerr);
	}
    }

    Log* Log::getDefault()
    {
	if (!Log::s_pInstance)
	    Log::s_pInstance = new Log("Logfile.txt", true, true);
	return Log::s_pInstance;
    }

    void Log::freeDefault()
    {
	if (Log::s_pInstance)
	{
	    delete (Log::s_pInstance);
	    Log::s_pInstance = nullptr;
	}
    }

    void Log::setLogLevel(Level lvl)
    {
	m_logLevel = lvl;
    }

    void Log::writeLog(std::string msg)
    {
	std::ofstream out(m_filename, std::ios::app);
	out.write(msg.c_str(), msg.length());
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

    void Log::format(std::string& msg, const char* format)
    {
	while (*format)
	{
	    if (*format == '%')
	    {
		if (*(format + 1) == '%')
		    ++format;
		else
		    throw std::runtime_error("Format string invalid. Missing arguments.");
	    }
	    msg += *format++;
	}
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
