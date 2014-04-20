//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Properties/Properties.h"

namespace dbgl
{
    bool Properties::load(const std::string path)
    {
	// Open file
	std::ifstream file;
	file.open(path.c_str(), std::ios::in);
	if (file.is_open())
	{
	    // Seek to beginning
	    file.seekg(0, std::ios::beg);
	    int lineNo = -1;
	    // Scan whole file
	    while (file.good())
	    {
		// Increase line number
		lineNo++;
		// Read line
		std::string line;
		std::getline(file, line);
		// Skip empty lines
		if (line.length() == 0)
		    continue;
		// Skip comments
		if (line.substr(0, m_cmntSymbol.size()) == m_cmntSymbol)
		    continue;
		// Split on key-value-separator
		auto start = 0U;
		auto end = line.find(m_keyValueSep);
		std::vector<std::string> tokens;
		while (end != std::string::npos)
		{
		    tokens.push_back(line.substr(start, end - start));
		    start = end + m_keyValueSep.length();
		    end = line.find(m_keyValueSep, start);
		}
		tokens.push_back(line.substr(start, end));
		if (tokens.size() != 2)
		{
		    LOG->warning("Properties file \"%s\" misformatted at line %d!", path.c_str(), lineNo);
		    continue;
		}
		// Erase trailing spaces for key and leading spaces for value
		tokens[0].erase(tokens[0].find_last_not_of(' ') + 1);
		tokens[1].erase(0, tokens[1].find_first_not_of(' '));
		// Check if property already exists
		if (m_properties.find(tokens[0]) != m_properties.end())
		    LOG->warning("Properties file \"%s\" contains multiple definitions for key \"%s\" at line %d!", path.c_str(), tokens[0].c_str(), lineNo);
		    // Add property
		m_properties[tokens[0]] = tokens[1];
	    }
	    return true;
	}
	LOG->warning("Properties file \"%s\" not found!", path.c_str());
	return false;
    }

    void Properties::interpret(const std::string line)
    {
	std::string token;
	std::istringstream lineStream(line);
	while (lineStream.good())
	{
	    lineStream >> token;
	    if (token.substr(0, m_cmntSymbol.size()) != m_keyPrefix)
	    {
		LOG->warning("Misformatted argument in \"%s\"!", line.c_str());
		return;
	    }
	    std::string key = token.substr(m_cmntSymbol.size(), token.size());
	    std::string value;
	    lineStream >> value;
	    // Check if property already exists
	    if (m_properties.find(key) != m_properties.end())
		LOG->warning("Multiple definitions for key  \"%s\"!", key.c_str());
		// Add property
	    m_properties[key] = value;
	}
    }

    void Properties::interpret(int argc, char** argv)
    {
	for(int i = 0; i < argc; i+=2)
	{
	    std::string token(argv[i]);
	    if (token.substr(0, m_cmntSymbol.size()) != m_keyPrefix || argc <= i+1)
	    {
		LOG->warning("Misformatted argument in \"%s\"!", token.c_str());
		return;
	    }
	    std::string key = token.substr(m_cmntSymbol.size(), token.size());
	    std::string value(argv[i+1]);
	    // Check if property already exists
	    if (m_properties.find(key) != m_properties.end())
		LOG->warning("Multiple definitions for key  \"%s\"!", key.c_str());
		// Add property
	    m_properties[key] = value;
	}
    }

    void Properties::setValue(std::string key, std::string value)
    {
	// Check if property already exists
	if (m_properties.find(key) != m_properties.end())
	    LOG->warning("Multiple definitions for key  \"%s\"!", key.c_str());
	// Add property
	m_properties[key] = value;
    }

    std::string Properties::getStringValue(std::string key)
    {
	auto it = m_properties.find(key);
	if (it != m_properties.end())
	    return it->second;
	else
	    return "";
    }

    int Properties::getIntValue(std::string key)
    {
	std::string val = getStringValue(key);
	return atoi(val.c_str());
    }

    float Properties::getFloatValue(std::string key)
    {
	std::string val = getStringValue(key);
	return atof(val.c_str());
    }

    bool Properties::getBoolValue(std::string key)
    {
	std::string val = getStringValue(key);
	bool b;
	std::istringstream(val) >> std::boolalpha >> b;
	return b;
    }

    std::string Properties::operator[](std::string key)
    {
	return getStringValue(key);
    }

    void Properties::setCommentQualifier(std::string cmntQualifier)
    {
	m_cmntSymbol = cmntQualifier;
    }

    void Properties::setKeyValueDelimiter(std::string delimiter)
    {
	m_keyValueSep = delimiter;
    }

    void Properties::setKeyPrefix(std::string prefix)
    {
	m_keyPrefix = prefix;
    }
}
