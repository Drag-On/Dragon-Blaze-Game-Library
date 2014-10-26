//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <string>
#include <cstring>

namespace dbgl
{
    /**
     * @brief Provides info about the underlying filesystem
     */
    class Filesystem
    {
	public:
	    /**
	     * @brief Retrieves the current working directory from the operating system
	     * @return Current working directory
	     */
	    static std::string getCurWorkingDir();
	    /**
	     * @brief Modifies the current working directory of the operating system
	     * @param path New working directory
	     * @return True in case the new working directory was set, otherwise false
	     */
	    static bool setCurWorkingDir(std::string const& path);
    };
}



#endif /* FILESYSTEM_H_ */
