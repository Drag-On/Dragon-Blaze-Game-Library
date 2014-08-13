//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTURERESOURCE_H_
#define TEXTURERESOURCE_H_

#include <string>
#include "Resource.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Texture/TextureLoader.h"
#include "DBGL/Rendering/Texture/TGATextureLoader.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    /**
     * @brief A texture resource which can be used with a ResourceManager
     * @details It wraps a texture inside and makes sure it gets loaded at an appropriate time
     */
    class TextureResource : public Resource
    {
	public:
	    /**
	     * @brief Base structure, can be used to pass additional information to ResourceManager
	     */
	    template <class T> struct TextureResourceInfo : public Resource::ResourceInfo
	    {
		/**
		 * @brief Type of the loader to use
		 */
		using LoaderType = T;

		/**
		 * @brief Constructor
		 * @param filename Name of the texture file
		 * @param flags Flags to pass to loader
		 * @param filtering Filtering to use
		 */
		TextureResourceInfo(std::string filename, Bitmask<> flags = 0,
			    TextureLoader::Filtering filtering = TextureLoader::Filtering::LINEAR) :
				    ResourceInfo(filename), m_flags(flags), m_filtering(filtering)
		{
		}

		/**
		 * Flags to pass to the loader, defined in Texture class
		 */
		Bitmask<> m_flags = 0;
		/**
		 * @brief Texture filtering to use
		 */
		TextureLoader::Filtering m_filtering = TextureLoader::Filtering::LINEAR;
	    };

	    /**
	     * @brief Constructor
	     * @param filename Filename of the resource
	     */
	    TextureResource(std::string const& filename);
	    /**
	     * @brief Constructor
	     * @param info Object holding all the data needed to properly initialize the resource
	     */
	    template<class T> TextureResource(TextureResourceInfo<T> const& info) :
		    Resource(info), m_pTextureLoader(new T {}), m_flags(info.m_flags), m_filtering(
			    info.m_filtering)
	    {
	    }
	    /**
	     * @brief Destructor
	     */
	    virtual ~TextureResource();
	    /**
	     * @brief Loads the resource
	     */
	    virtual void load();
	    /**
	     * @brief Unloads the resource
	     */
	    virtual void unload();
	    /**
	     * @brief Retrieves the held texture
	     * @return A pointer to the texture or nullptr if not yet loaded
	     */
	    Texture* getTexture() const;

	private:
	    Texture* m_pTexture = nullptr;
	    TextureLoader* m_pTextureLoader = nullptr;
	    Bitmask<> m_flags = 0;
	    TextureLoader::Filtering m_filtering = TextureLoader::Filtering::LINEAR;

	    friend class ResourceManager<TextureResource>;
    };
}



#endif /* TEXTURERESOURCE_H_ */
