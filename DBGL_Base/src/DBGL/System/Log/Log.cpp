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

// These headers are not included in Log.h by purpose. They pollute the whole namespace.
#ifdef _WIN32
    /**
     * @brief OS dependent namespace for win32
     */
    namespace OS_Win32
    {
#undef _MSC_EXTENSIONS
	#include <windows.h>
    }
#endif

#ifdef __linux__
    /**
     * @brief OS dependent namespace for linux
     */
    namespace OS_Linux
    {
	#include <sys/utsname.h>
    }
#endif

namespace dbgl
{
    // Init static variables
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

	writeLog("#######################################\n");
	writeLog("## Logfile\n");
	writeLog("#######################################\n");
	writeLog("# Date: " + time + "\n");
	writeLog("# OS: " + getOSDescription() + "\n");
	writeLog("#######################################\n");

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

    Log& Log::getDefault()
    {
	// This ensures lazy loading
	static Log instance("Logfile.txt", true, true);
	return instance;
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

    std::string Log::getOSDescription()
    {
	std::stringstream osDesc;
#ifdef _WIN32
	osDesc << "Windows ";
	OS_Win32::OSVERSIONINFO version;
	version.dwOSVersionInfoSize = sizeof(OS_Win32::OSVERSIONINFO);
	OS_Win32::GetVersionEx(&version);
	switch (version.dwPlatformId)
	{
	    case VER_PLATFORM_WIN32s:
		osDesc << version.dwMajorVersion << "." << version.dwMinorVersion;
		break;
	    case VER_PLATFORM_WIN32_WINDOWS:
		if (version.dwMinorVersion == 0)
		    osDesc << "95";
		else if (version.dwMinorVersion == 10)
		    osDesc << "98";
		else if (version.dwMinorVersion == 90)
		    osDesc << "ME";
		break;
	    case VER_PLATFORM_WIN32_NT:
		if (version.dwMajorVersion == 5 && version.dwMinorVersion == 0)
		    osDesc << "2000 with " << version.szCSDVersion;
		else if (version.dwMajorVersion == 5 && version.dwMinorVersion == 1)
		    osDesc << "XP " << std::string(version.szCSDVersion);
		else if (version.dwMajorVersion <= 4)
		    osDesc << "NT " << version.dwMajorVersion << std::string(".") << version.dwMinorVersion << " with "
			    << std::string(version.szCSDVersion);
		else
		    osDesc << version.dwMajorVersion << "." << version.dwMinorVersion;
		break;
	}
#endif
#ifdef __linux__
	osDesc << "Linux";
	// TODO: More detailed description
	// int uname(struct utsname *buf);
#endif
#ifdef __APPLE__
	osDesc << "OSX";
#endif
	return osDesc.str();
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
		LOG.debug(str().c_str());
		break;
	    case Level::INFO:
		LOG.info(str().c_str());
		break;
	    case Level::WARN:
		LOG.warning(str().c_str());
		break;
	    case Level::ERR:
		LOG.error(str().c_str());
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
