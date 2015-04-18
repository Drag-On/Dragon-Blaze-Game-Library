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
         */
        static std::string& trimLeft(std::string& s);

        /**
         * @brief Trims whitespace on the right of a string
         */
        static std::string& trimRight(std::string& s);

        /**
         * @brief Trims whitespace on both ends of a string
         */
        static std::string& trim(std::string& s);
    };
}

#endif //DBGL_STRINGUTILITY_H
