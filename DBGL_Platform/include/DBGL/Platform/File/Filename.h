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
    /**
     * @brief Represents a path and filename on hard disk
     */
    class Filename
    {
	public:
	    /**
	     * @brief Initialize filename from string
	     * @param path Initial value
	     */
	    Filename(std::string const& path);
	    /**
	     * @brief Checks if this filename is relative to the current working directory
	     * @return True in case it's relative, otherwise false
	     */
	    bool isRelative() const;
	    /**
	     * @brief Provides the file extension (if any) of the file pointed to by this path
	     * @return The file extension
	     */
	    std::string getExtension() const;
	    /**
	     * @brief Returns an absolute path to the file
	     * @return Absolute path to the file
	     */
	    std::string getAbsolute() const;
//	    std::string getRelative() const;
	    /**
	     * @brief Retrieves the path and filename as stored within this object, i.e. it can
	     * 	      either be a relative path or an absolute one.
	     * @return The underlying path and filename
	     */
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
