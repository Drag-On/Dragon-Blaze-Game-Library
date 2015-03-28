//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Parsers/CSV.h"
#include "DBGL/Core/Debug/Log.h"

namespace dbgl
{
	CSV::CSV()
	{
	}

	CSV::CSV(std::string const& path)
			: m_filename { path }
	{
		if (!read(path))
			throw std::runtime_error { "Unable to load file \"" + path + "\"." };
	}

	bool CSV::read(std::string const& path)
	{
		m_filename = path;
		// Open file
		std::ifstream file { };
		file.open(path.c_str(), std::ios::in);
		if (file.is_open())
		{
			// Seek to beginning
			file.seekg(0, std::ios::beg);
			int lineNo { -1 };
			// Scan whole file
			while (file.good())
			{
				// Increase line number
				lineNo++;
				// Read line
				std::string line { };
				std::getline(file, line);
				// Skip empty lines
				if (line.length() == 0)
					continue;
				// Split on delimiter
				auto start = 0U;
				auto end = line.find(m_delimiter);
				std::vector<std::string> tokens { };
				while (end != std::string::npos)
				{
					tokens.push_back(line.substr(start, end - start));
					start = end + m_delimiter.length();
					end = line.find(m_delimiter, start);
				}
				tokens.push_back(line.substr(start, end));
				// Add element
				m_table.push_back(tokens);
			}
			file.close();
			return true;
		}
		Log::getDefault().warning("CSV file \"%\" could not be opened!", path.c_str());
		return false;
	}

	bool CSV::write()
	{
		return write(m_filename);
	}

	bool CSV::write(std::string const& path)
	{
		// Write to some other file
		std::ofstream outFile { };
		outFile.open(path, std::ios::out);
		if (outFile.is_open())
		{
			// Write table contents
			for (unsigned int y = 0; y < m_table.size(); y++)
				for (unsigned int x = 0; x < m_table[y].size(); x++)
					outFile << m_table[y][x] << m_delimiter << "\n";
			outFile.close();
			return true;
		}
		Log::getDefault().warning("CSV file \"%\" could not be opened!", path);
		return false;
	}

	void CSV::setValue(unsigned int x, unsigned int y, std::string const& value)
	{
		if (m_table.size() <= y || m_table[y].size() <= x)
			throw std::out_of_range { "(" + std::to_string(x) + "," + std::to_string(y)
					+ ") out of range in CSV table read from \"" + m_filename + "\"." };
		m_table[y][x] = value;
	}

	std::string CSV::getStringValue(unsigned int x, unsigned int y) const
	{
		if (m_table.size() <= y || m_table[y].size() <= x)
			throw std::out_of_range { "(" + std::to_string(x) + "," + std::to_string(y)
					+ ") out of range in CSV table read from \"" + m_filename + "\"." };
		return m_table[y][x];
	}

	int CSV::getIntValue(unsigned int x, unsigned int y) const
	{
		if (m_table.size() <= y || m_table[y].size() <= x)
			throw std::out_of_range { "(" + std::to_string(x) + "," + std::to_string(y)
					+ ") out of range in CSV table read from \"" + m_filename + "\"." };
		return atoi(m_table[y][x].c_str());
	}

	float CSV::getFloatValue(unsigned int x, unsigned int y) const
	{
		if (m_table.size() <= y || m_table[y].size() <= x)
			throw std::out_of_range { "(" + std::to_string(x) + "," + std::to_string(y)
					+ ") out of range in CSV table read from \"" + m_filename + "\"." };
		return atof(m_table[y][x].c_str());
	}

	bool CSV::getBoolValue(unsigned int x, unsigned int y) const
	{
		if (m_table.size() <= y || m_table[y].size() <= x)
			throw std::out_of_range { "(" + std::to_string(x) + "," + std::to_string(y)
					+ ") out of range in CSV table read from \"" + m_filename + "\"." };
		std::string val = m_table[y][x];
		bool b { };
		std::istringstream(val) >> std::boolalpha >> b;
		return b;
	}

	void CSV::setDelimiter(std::string const& delimiter)
	{
		m_delimiter = delimiter;
	}

	unsigned int CSV::getWidth(unsigned int y) const
	{
		if (m_table.size() <= y)
			return 0;
		else
			return m_table[y].size();
	}

	unsigned int CSV::getHeight(unsigned int x) const
	{
		if (getWidth(0) < x)
			return 0;
		else
			return m_table.size();
	}
}

