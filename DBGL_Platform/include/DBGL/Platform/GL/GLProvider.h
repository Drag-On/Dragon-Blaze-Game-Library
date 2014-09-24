//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef GLPROVIDER_H_
#define GLPROVIDER_H_

#include "IGL.h"
#include "GLOpenGL33.h"

namespace dbgl
{
    class GLProvider
    {
	public:
	    /**
	     * @brief Enumerates all supported rendering APIs
	     */
	    enum class API : char
	    {
		OpenGL33,//!< OpenGL33 OpenGL Version 3.3
	    };

	    /**
	     * @brief Initialize a graphics layer using the specified API
	     * @details Doesn't do anything if another API has already been initialized
	     * @param api API to use
	     */
	    static void init(API api);
	    /**
	     * @brief Provides access to the currently active graphics layer implementation
	     * @return Pointer to the previously initialized graphics layer implementation or
	     * 	       nullptr if @see init wasn't called before
	     */
	    static IGL* get();
	    /**
	     * @brief Frees the previously initialized graphics layer implementation
	     */
	    static void free();

	private:
	    GLProvider(); // Prevent construction

	    static IGL* s_pGL;
    };
}

#endif /* GLPROVIDER_H_ */
