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
	    struct ShaderResourceInfo: public Resource::ResourceInfo
	    {
		    /**
		     * @brief Constructor
		     * @param vertShaderFile File name of the vertex shader
		     * @param fragShaderFile File name of the fragment shader
		     */
		    ShaderResourceInfo(std::string const& vertShaderFile, std::string const& fragShaderFile) :
			    Resource::ResourceInfo(vertShaderFile), m_fragmentShaderFileName(fragShaderFile)
		    {
		    }

		    /**
		     * @brief File name of the fragment shader (m_filename is the vertex shader)
		     */
		    std::string m_fragmentShaderFileName;
	    };

	    /**
	     * @brief Constructor
	     * @param info Object holding all the data needed to properly initialize the resource
	     */
	    ShaderResource(ShaderResourceInfo const& info);
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

	    friend class ResourceManager<ShaderResource>;
    };
}

#endif /* SHADERRESOURCE_H_ */
