//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ISHADER_H_
#define ISHADER_H_

#include <string>

namespace dbgl
{
    class IShader
    {
	public:
	    /**
	     * @brief Lists all supported shader types
	     */
	    enum class Type
	    {
		VERTEX,  //!< VERTEX
		FRAGMENT,//!< FRAGMENT
		GEOMETRY,//!< GEOMETRY
		COMPUTE, //!< COMPUTE
	    };

	    virtual ~IShader() = default;
	    virtual void compile() = 0;
    };
}

#endif /* ISHADER_H_ */
