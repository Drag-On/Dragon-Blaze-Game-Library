//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SHADERRESOURCE_H_
#define SHADERRESOURCE_H_

#include <string>
#include "Resource.h"
#include "DBGL/Rendering/ShaderProgram.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    /**
     * @brief A shader resource which can be used with a ResourceManager
     * @details It wraps a ShaderProgram inside and makes sure it gets loaded at an appropriate time
     * @note It's not possible to construct a ShaderResource from only a single file name (every ShaderProgram needs at least two shaders)
     */
    class ShaderResource: public Resource
    {
	public:
	    /**
	     * @brief Base structure, can be used to pass additional information to ResourceManager
	     */
	    template<class T> struct ShaderResourceInfo: public Resource::ResourceInfo
	    {
		    /**
		     * @brief Type of the loader to use
		     */
		    using LoaderType = T;

		    /**
		     * @brief File name of the fragment shader (m_filename is the vertex shader)
		     */
		    std::string m_fragmentShaderFileName;
	    };

	    /**
	     * @brief Constructor
	     * @param info Object holding all the data needed to properly initialize the resource
	     */
	    template<class T> ShaderResource(ShaderResourceInfo<T> const& info);
	    /**
	     * @brief Destructor
	     */
	    virtual ~ShaderResource();
	    /**
	     * @brief Loads the resource
	     */
	    virtual void load();
	    /**
	     * @brief Unloads the resource
	     */
	    virtual void unload();
	    /**
	     * @brief Retrieves the held shader
	     * @return A pointer to the shader or nullptr if not yet loaded
	     */
	    ShaderProgram* getShader() const;

	private:
	    ShaderProgram* m_pShader = nullptr;
	    std::string m_fragmentShaderFileName;
    };
}

#endif /* SHADERRESOURCE_H_ */
