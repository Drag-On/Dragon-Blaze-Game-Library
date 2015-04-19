//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef DBGL_STRINGUTILITY_H
#define DBGL_STRINGUTILITY_H

#include <string>

namespace dbgl
{
    /**
     * @brief Contains useful string utility functions
     */
    class StringUtility
    {
    public:
        /**
         * @brief Trims whitespace on the left of a string
         * @param[in,out] s String to trim
         * @returns The input reference
         */
        static std::string& trimLeft(std::string& s);
        /**
         * @brief Trims whitespace on the right of a string
         * @param[in,out] s String to trim
         * @returns The input reference
         */
        static std::string& trimRight(std::string& s);
        /**
         * @brief Trims whitespace on both ends of a string
         * @param[in,out] s String to trim
         * @returns The input reference
         */
        static std::string& trim(std::string& s);
        /**
         * @brief Tries to parse a string as a number type
         * @param[in] s String to parse
         * @returns The parsed number
         */
        template<typename T>
        static T parseAs(std::string const& s);
    };

    /**
     * @brief Tries to parse a string as a signed char
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    signed char StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as an unsigned char
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    unsigned char StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a char
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    char StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a signed short
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    signed short StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as an unsigned short
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    unsigned short StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a signed int
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    signed int StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as an unsigned int
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    unsigned int StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a signed long
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    signed long StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as an unsigned long
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    unsigned long StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a signed long long
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    signed long long StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as an unsigned long long
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    unsigned long long StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a float
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    float StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a double
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    double StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a long double
     * @param[in] s String to parse
     * @returns The parsed number
     */
    template<>
    long double StringUtility::parseAs(std::string const& s);
    /**
     * @brief Tries to parse a string as a bool
     * @param[in] s String to parse
     * @returns The parsed bool
     */
    template<>
    bool StringUtility::parseAs(std::string const& s);
}

#include "StringUtility.imp"

#endif //DBGL_STRINGUTILITY_H
