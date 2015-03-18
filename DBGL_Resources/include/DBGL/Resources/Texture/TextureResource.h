//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_TEXTURE_TEXTURERESOURCE_H_
#define INCLUDE_DBGL_RESOURCES_TEXTURE_TEXTURERESOURCE_H_

#include "DBGL/Resources/Manager/AbstractResource.h"
#include "DBGL/Resources/Texture/TextureIO.h"
#include "DBGL/Core/Debug/Log.h"

namespace dbgl
{
	/**
	 * @brief Texture resource
	 */
	class TextureResource: public AbstractResource
	{
	public:
		/**
		 * @brief Constructor
		 * @param h Handle assigned to this resource
		 * @param filename Filename of the resource
		 * @param createMip Specifies if mip-maps should be generated
		 */
		TextureResource(ResourceHandle h, std::string const& filename, bool createMip = true);
		virtual void load();
		virtual void unload();
		/**
		 * @brief Retrieves the actual texture
		 * @return Pointer to the loaded texture or nullptr, if not loaded yet
		 */
		ITexture* getTexture();
		/**
		 * @brief Reference to the texture loader instance used by all texture resources
		 * @return Reference to texture loader
		 * @note This texture loader needs to be pointed to the right plugins in order to work!
		 */
		static TextureIO& loader();
	private:
		static TextureIO s_textureIO;
		ITexture* m_pTexture = nullptr;
		std::string m_filename;
		bool m_createMip;
	};
}

#endif /* INCLUDE_DBGL_RESOURCES_TEXTURE_TEXTURERESOURCE_H_ */
