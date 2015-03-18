//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_SHADER_SHADERPROGRAMRESOURCE_H_
#define INCLUDE_DBGL_RESOURCES_SHADER_SHADERPROGRAMRESOURCE_H_

#include "DBGL/Resources/Manager/AbstractResource.h"
#include "DBGL/Resources/Manager/ResourceManager.h"
#include "DBGL/Resources/Shader/ShaderResource.h"
#include "DBGL/Core/Debug/Log.h"
#include "DBGL/Platform/Platform.h"
#include <string>
#include <vector>

namespace dbgl
{
	/**
	 * @brief Shader program resource
	 */
	class ShaderProgramResource: public AbstractResource
	{
	public:
		/**
		 * @brief Constructor
		 * @param h Handle assigned to this resource
		 * @param name Name of this shader program
		 * @param filenames Array of filenames of ShaderResources
		 * @param shaderManager Manager instance that holds the shaders required by this program
		 */
		ShaderProgramResource(ResourceHandle h, std::string const& name, std::vector<std::string> const& filenames,
				ResourceManager<ShaderResource>* shaderManager);
		virtual void load();
		virtual void unload();
		/**
		 * @brief Identify this resource by its name
		 * @param name Name to check
		 * @return True in case the name, this resource was constructed from, matches the passed one
		 */
		bool identify(std::string const& name) const;
		/**
		 * @brief Retrieves the actual texture
		 * @return Pointer to the loaded texture or nullptr, if not loaded yet
		 */
		IShaderProgram* getShaderProgram();
	private:
		IShaderProgram* m_pShaderProgram = nullptr;
		std::string m_name;
		std::vector<std::string> m_shaderFiles;
		ResourceManager<ShaderResource>* m_pShaderManager;
	};
}

#endif /* INCLUDE_DBGL_RESOURCES_SHADER_SHADERPROGRAMRESOURCE_H_ */
