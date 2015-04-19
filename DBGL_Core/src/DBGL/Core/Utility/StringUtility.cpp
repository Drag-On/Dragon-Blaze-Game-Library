//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Utility/StringUtility.h"

#include <algorithm>
#include <functional>
#include <sstream>

namespace dbgl
{
    std::string& StringUtility::trimLeft(std::string& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    std::string& StringUtility::trimRight(std::string& s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    std::string& StringUtility::trim(std::string& s)
    {
        return trimLeft(trimRight(s));
    }

    template<>
    signed char StringUtility::parseAs(std::string const& s)
    {
        return static_cast<signed char>(std::stoi(s));
    }

    template<>
    unsigned char StringUtility::parseAs(std::string const& s)
    {
        return static_cast<unsigned char>(std::stoi(s));
    }

    template<>
    char StringUtility::parseAs(std::string const& s)
    {
        return static_cast<char>(std::stoi(s));
    }

    template<>
    signed short StringUtility::parseAs(std::string const& s)
    {
        return static_cast<signed short>(std::stoi(s));
    }

    template<>
    unsigned short StringUtility::parseAs(std::string const& s)
    {
        return  static_cast<unsigned short>(std::stoul(s));
    }

    template<>
    signed int StringUtility::parseAs(std::string const& s)
    {
        return std::stoi(s);
    }

    template<>
    unsigned int StringUtility::parseAs(std::string const& s)
    {
        return static_cast<unsigned int>(std::stoul(s));
    }

    template<>
    signed long StringUtility::parseAs(std::string const& s)
    {
        return std::stol(s);
    }

    template<>
    unsigned long StringUtility::parseAs(std::string const& s)
    {
        return std::stoul(s);
    }

    template<>
    signed long long StringUtility::parseAs(std::string const& s)
    {
        return std::stoll(s);
    }

    template<>
    unsigned long long StringUtility::parseAs(std::string const& s)
    {
        return std::stoull(s);
    }

    template<>
    float StringUtility::parseAs(std::string const& s)
    {
        return std::stof(s);
    }

    template<>
    double StringUtility::parseAs(std::string const& s)
    {
        return std::stod(s);
    }

    template<>
    long double StringUtility::parseAs(std::string const& s)
    {
        return std::stold(s);
    }

    template<>
    bool StringUtility::parseAs(std::string const& s)
    {
        bool val;
        std::stringstream ss;
        ss << s;
        ss >> std::boolalpha >> val;
        return val;
    }
}