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
#include <cstdio>
#include <unordered_map>
#include "DBGL/Core/Debug/Log.h"

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
	    bool read(std::string const& path);
	    /**
	     * @brief Interprets a line
	     * @details Reads in "-key value" pairs
	     * @param line String to parse
	     */
	    void interpret(std::string const& line);
	    /**
	     * @brief Interprets an array
	     * @details Reads in "-key value" pairs
	     * @param argc Amount of arguments
	     * @param argv Actual arguments
	     */
	    void interpret(int argc, char** argv);
	    /**
	     * @brief Writes the properties back to file
	     * @return True in case the file was written, otherwise false
	     */
	    bool write();
	    /**
	     * @brief Writes the properties back to file
	     * @param path Path to write to
	     * @return True in case the file was written, otherwise false
	     */
	    bool write(std::string const& path);
	    /**
	     * @brief Manually sets a property, overwriting any previous values
	     * @param key Key of the property
	     * @param value Value of the property
	     */
	    void setValue(std::string const&key, std::string const& value);
	    /**
	     * @param key Key to get the value for
	     * @return Raw string value associated with the passed key
	     */
	    std::string getStringValue(std::string const& key);
	    /**
	     * @brief Interprets the string associated with the passed key as an integer
	     * @param key Key to get the value for
	     * @return Integer value associated with the passed key
	     */
	    int getIntValue(std::string const& key);
	    /**
	     * @brief Interprets the string associated with the passed key as a float
	     * @param key Key to get the value for
	     * @return Float value associated with the passed key
	     */
	    float getFloatValue(std::string const& key);
	    /**
	     * @brief Interprets the string associated with the passed key as a boolean
	     * @param key Key to get the value for
	     * @return Boolean value associated with the passed key
	     */
	    bool getBoolValue(std::string const& key);
	    /**
	     * @param key Key to get the value for
	     * @return Reference to value associated with the passed key. Creates key if not found.
	     */
	    std::string& operator[](std::string const& key);
	    /**
	     * @param cmntQualifier String that qualifies lines as comments
	     */
	    void setCommentQualifier(std::string const& cmntQualifier);
	    /**
	     * @param delimiter String to delimit key and value in property files
	     */
	    void setKeyValueDelimiter(std::string const& delimiter);
	    /**
	     * @param prefix Prefix for keys in interpreted lines
	     */
	    void setKeyPrefix(std::string const& prefix);
	private:
	    std::string m_filename;
	    std::string m_cmntSymbol = "#";
	    std::string m_keyValueSep = "=";
	    std::string m_keyPrefix = "-";
	    std::unordered_map<std::string, std::string> m_properties;
    };
}

#endif /* PROPERTIES_H_ */
