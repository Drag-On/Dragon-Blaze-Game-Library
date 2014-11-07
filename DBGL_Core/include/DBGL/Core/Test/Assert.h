//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ASSERT_H_
#define ASSERT_H_

#include <string>
#include <stdexcept>

namespace dbgl
{
    class AssertException : public std::runtime_error
    {
	public:
	    AssertException(std::string const& file, unsigned int line, std::string const& msg);
	    std::string const& getFile() const;
	    unsigned int getLine() const;
	private:
	    std::string m_file;
	    unsigned int m_line;
    };
}

#define ASSERT(chk) if(chk){}else{throw AssertException{__FILE__, __LINE__, "\""#chk "\" failed."};}

#define ASSERT_EQ(first, last) ASSERT((first) == (last))

#endif /* ASSERT_H_ */
