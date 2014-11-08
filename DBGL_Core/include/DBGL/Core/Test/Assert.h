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
    /**
     * @brief Exception thrown by assert commands
     */
    class AssertException : public std::runtime_error
    {
	public:
	    /**
	     * @brief Constructor
	     * @param file File where the assertion failed
	     * @param line Line within that file, where assertion failed
	     * @param msg Attached message
	     */
	    AssertException(std::string const& file, unsigned int line, std::string const& msg);
	    /**
	     * @brief Retrieves the file name where the exception was thrown
	     * @return File name
	     */
	    std::string const& getFile() const;
	    /**
	     * @brief Retrieves the line where the exception was thrown
	     * @return
	     */
	    unsigned int getLine() const;
	private:
	    std::string m_file;
	    unsigned int m_line;
    };
}

#define ASSERT(chk) if((chk)){}else{throw AssertException{__FILE__, __LINE__, "\""#chk "\" failed."};}

#define ASSERT_EQ(first, last) ASSERT((first) == (last))

#define ASSERT_THROWS(chk,ex) {bool thrown = false; try {(chk);}catch(ex& e){thrown = true;}catch(...){throw AssertException{__FILE__, __LINE__, "\""#chk "\" failed."};}if(!thrown)throw AssertException{__FILE__, __LINE__, "\""#chk "\" failed."};}

#define ASSERT_NOTHROW(chk) try{(chk);}catch(...){throw AssertException{__FILE__, __LINE__, "\""#chk "\" failed."};}

#define FAIL() {throw AssertException{__FILE__, __LINE__, "Failed unconditionally."};}

#endif /* ASSERT_H_ */
