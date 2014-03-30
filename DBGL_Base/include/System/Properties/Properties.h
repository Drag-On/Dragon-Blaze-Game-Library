//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "System/Log/Log.h"

namespace dbgl
{
    /**
     * @brief Loads simple key = value text files and interprets -arguments
     */
    class Properties
    {
	public:
	    /**
	     * @brief Loads the specified properties file into RAM
	     * @param path Path of the file to use
	     * @return True in case the file could be loaded, otherwise false
	     */
	    bool load(const std::string path);
	    /**
	     * @brief Interprets a line
	     * @detail Reads in -key value pairs
	     * @param line String to parse
	     */
	    void interpret(const std::string line);
	    /**
	     * @param key Key to get the value for
	     * @return Raw string value associated with the passed key
	     */
	    std::string getStringValue(std::string key);
	    /**
	     * @brief Interprets the string associated with the passed key as an integer
	     * @param key Key to get the value for
	     * @return Integer value associated with the passed key
	     */
	    int getIntValue(std::string key);
	    /**
	     * @brief Interprets the string associated with the passed key as a float
	     * @param key Key to get the value for
	     * @return Float value associated with the passed key
	     */
	    float getFloatValue(std::string key);
	    /**
	     * @brief Interprets the string associated with the passed key as a boolean
	     * @param key Key to get the value for
	     * @return Boolean value associated with the passed key
	     */
	    bool getBoolValue(std::string key);
	    /**
	     * @param key Key to get the value for
	     * @return Value associated with the passed key or "" if not found
	     */
	    std::string operator[](std::string key);
	private:
	    std::string m_cmntSymbol = "#";
	    std::string m_keyValueSep = "=";
	    std::string m_keyPrefix = "-";
	    std::unordered_map<std::string, std::string> m_properties;
    };
}

#endif /* PROPERTIES_H_ */
