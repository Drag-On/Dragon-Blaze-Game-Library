//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef OS_H_
#define OS_H_

#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>

namespace dbgl
{
    /**
     * @brief This class can be used to get information about the underlying operating system
     */
    class OS
    {
	public:
	    /**
	     * @brief Holds available data about an operating system
	     */
	    struct Type
	    {
		/**
		 * @brief Operating system name (e.g. "Linux", "Windows")
		 */
		std::string name = "Unknown";
		/**
		 * @brief Name of the derivative (e.g. "Ubuntu", "Vista")
		 */
		std::string derivative = "";
		/**
		 * @brief Major version number
		 */
		unsigned short major = 0;
		/**
		 * @brief Minor version number
		 */
		unsigned short minor = 0;
		/**
		 * @brief Additional description, if there is some
		 */
		std::string descr = "";
	    };

	    /**
	     * @brief Provides data about the operating system running the program
	     * @return All available data about the operating system currently running the program
	     */
	    static OS::Type getType();
	    /**
	     * @brief Creates a descriptive string of the passed OS type
	     * @param os OS type to create a description for
	     * @return The descriptive string
	     */
	    static std::string getDescripion(OS::Type const& os);
	    /**
	     * @brief Creates a descriptive string of the OS currently running the program
	     * @return The descriptive string
	     */
	    static std::string getDescripion();
    };
}

#endif /* OS_H_ */
