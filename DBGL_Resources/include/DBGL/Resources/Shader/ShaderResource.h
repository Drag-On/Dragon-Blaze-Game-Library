//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_SHADER_SHADERRESOURCE_H_
#define INCLUDE_DBGL_RESOURCES_SHADER_SHADERRESOURCE_H_

#include "DBGL/Resources/Manager/AbstractResource.h"
#include "DBGL/Core/Debug/Log.h"
#include "DBGL/Platform/Platform.h"
#include <string>
#include <vector>

namespace dbgl
{
	/**
	 * @brief Shader resource
	 */
	class ShaderResource: public AbstractResource
	{
	public:
		/**
		 * @brief Constructor
		 * @param h Handle assigned to this resource
		 * @param filename Filename of the shader
		 * @param type Shader type
		 */
		ShaderResource(ResourceHandle h, std::string const& filename, IShader::Type type);
		virtual void load();
		virtual void unload();
		/**
		 * @brief Identify this resource by its filename
		 * @param filename Filename to check
		 * @return True in case the filename this resource was constructed from matches the passed one
		 */
		bool identify(std::string const& filename) const;
		/**
		 * @brief Retrieves the actual shader
		 * @return Pointer to the loaded shader or nullptr, if not loaded yet
		 */
		IShader* getShader();
	private:
		IShader* m_pShader = nullptr;
		std::string m_filename;
		IShader::Type m_type;
	};
}

#endif /* INCLUDE_DBGL_RESOURCES_SHADER_SHADERRESOURCE_H_ */
