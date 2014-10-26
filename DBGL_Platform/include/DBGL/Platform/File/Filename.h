//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef FILENAME_H_
#define FILENAME_H_

#include <string>
#include <regex>
#include <cstring>
#include "Filesystem.h"

namespace dbgl
{
    class Filename
    {
	public:
	    Filename(std::string const& path);
	    bool isRelative() const;
	    std::string getExtension() const;
	    std::string getAbsolute() const;
//	    std::string getRelative() const;
	    std::string const& get() const;

	private:
	    void analyze(std::string const& path);
	    void analyzeRelative(std::string const& path);
	    void analyzeExtension(std::string const& path);

	    std::string m_completeFile = "";
	    std::string m_filename = "";
	    std::string m_extension = "";
	    bool m_isRelative;
    };
}

#endif /* FILENAME_H_ */
