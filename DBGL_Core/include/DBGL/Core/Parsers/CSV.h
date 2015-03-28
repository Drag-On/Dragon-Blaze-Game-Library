//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef CSV_H_
#define CSV_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <stdexcept>

namespace dbgl
{
	/**
	 * @brief Parser for csv tables
	 */
	class CSV
	{
	public:
		/**
		 * @brief Loads a csv file from hard disk
		 * @param path Path of the file to load
		 */
		CSV(std::string const& path);
		/**
		 * @brief Writes the csv contents back to file
		 * @return True in case the file was written, otherwise false
		 */
		bool write();
		/**
		 * @brief Writes the csv contents back to file
		 * @param path Path to write to
		 * @return True in case the file was written, otherwise false
		 */
		bool write(std::string const& path);
		/**
		 * @brief Manually sets a property, overwriting any previous values
		 * @param x X coordinate of the value to set
		 * @param y Y coordinate of the value to set
		 * @param value Value of the property
		 */
		void setValue(unsigned int x, unsigned int y, std::string const& value);
		/**
		 * @param x X coordinate of the value to get
		 * @param y Y coordinate of the value to get
		 * @return Raw string value associated with the passed key
		 */
		std::string getStringValue(unsigned int x, unsigned int y) const;
		/**
		 * @brief Interprets the string associated with the passed coordinates as an integer
		 * @param x X coordinate of the value to get
		 * @param y Y coordinate of the value to get
		 * @return Integer value associated with the passed key
		 */
		int getIntValue(unsigned int x, unsigned int y) const;
		/**
		 * @brief Interprets the string associated with the passed coordinates as a float
		 * @param x X coordinate of the value to get
		 * @param y Y coordinate of the value to get
		 * @return Float value associated with the passed key
		 */
		float getFloatValue(unsigned int x, unsigned int y) const;
		/**
		 * @brief Interprets the string associated with the passed coordinates as a boolean
		 * @param x X coordinate of the value to get
		 * @param y Y coordinate of the value to get
		 * @return Boolean value associated with the passed key
		 */
		bool getBoolValue(unsigned int x, unsigned int y) const;
		/**
		 * @param delimiter String to delimit key and value in property files
		 */
		void setDelimiter(std::string const& delimiter);
		/**
		 * @brief Gets the width of a line
		 * @param y Line to get width for
		 * @return Amount of elements in line \p y
		 */
		unsigned int getWidth(unsigned int y) const;
		/**
		 * @brief Gets the height of a column
		 * @param x Column to get height for
		 * @return Amount of elements in column \p x
		 */
		unsigned int getHeight(unsigned int x) const;
	private:
		/**
		 * @brief Loads the specified csv file into RAM
		 * @param path Path of the file to use
		 * @return True in case the file could be loaded, otherwise false
		 */
		bool read(std::string const& path);

		std::string m_filename;
		std::string m_delimiter = ";";
		std::vector<std::vector<std::string>> m_table { };
	};
}

#endif /* CSV_H_ */
