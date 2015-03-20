//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_MATERIAL_ABSTRACTMATERIAL_H_
#define INCLUDE_DBGL_RENDERER_MATERIAL_ABSTRACTMATERIAL_H_

#include "IMaterial.h"
#include "DBGL/Resources/Manager/AbstractResource.h"
#include "DBGL/Resources/Manager/ResourceManager.h"
#include "DBGL/Resources/Texture/TextureResource.h"
#include "DBGL/Resources/Shader/ShaderProgramResource.h"
#include <vector>

namespace dbgl
{
	/**
	 * @brief Abstract material; implements a way to have the material link to textures and shader programs
	 */
	class AbstractMaterial: public IMaterial
	{
	public:
		/**
		 * @brief Constructor
		 * @param texManager Pointer to the texture manager
		 * @param shaManager Pointer to the shader manager
		 */
		AbstractMaterial(ResourceManager<TextureResource>* texManager,
				ResourceManager<ShaderProgramResource>* shaManager);
		/**
		 * @brief Destructor
		 */
		virtual ~AbstractMaterial();
		virtual void load();
		virtual void unload();
	protected:
		TextureResource* getTexture(unsigned int i) const;
		ShaderProgramResource* getShaderProgram(unsigned int i) const;

		std::vector<std::string> m_texPaths;
		std::vector<std::string> m_shaNames;
		std::vector<TextureResource::ResourceHandle> m_loadedTextures;
		std::vector<ShaderProgramResource::ResourceHandle> m_loadedShaders;
		ResourceManager<TextureResource>* m_pTexManager;
		ResourceManager<ShaderProgramResource>* m_pShaManager;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_MATERIAL_ABSTRACTMATERIAL_H_ */
