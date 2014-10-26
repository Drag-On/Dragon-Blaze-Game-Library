//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include <string>
#include <vector>
#include "ITextureFormat.h"
#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Platform/File/Filename.h"
#include "DBGL/Platform/Module/AdvancedModule.h"

namespace dbgl
{
    /**
     * @brief Loads textures from hard disk and stores them
     * @details This class doesn't contain any code to load or write image files, instead
     * 		it loads dynamic libraries that contain such code. The libraries must
     * 		be compatible with the AdvancedModule class from DBGL_Platform, and
     * 		provide instances of subclasses of ITextureFormat.
     */
    class TextureIO
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    TextureIO();
	    /**
	     * @brief Destructor
	     */
	    ~TextureIO();
	    /**
	     * @brief Adds a loader for a specific file format
	     * @param filename Name and path of the module file to load
	     * @return True in case the loader can be utilized, otherwise false
	     */
	    bool addFormat(std::string const& filename);
	    /**
	     * @brief Adds a loader for a specific file format
	     * @param filename Name and path of the module file to load
	     * @return True in case the loader can be utilized, otherwise false
	     */
	    bool addFormat(Filename const& filename);
	    /**
	     * @brief Loads a texture from a certain file
	     * @details The correct loader will be chosen based on file extension
	     * @param filename File to load
	     * @return Pointer to the loaded texture or nullptr if not loaded
	     */
	    ITexture* load(std::string const& filename) const;
	    /**
	     * @brief Loads a texture from a certain file
	     * @details The correct loader will be chosen based on file extension
	     * @param filename File to load
	     * @return Pointer to the loaded texture or nullptr if not loaded
	     */
	    ITexture* load(Filename const& filename) const;
	    /**
	     * @brief Writes a texture to hard disk
	     * @details Image format is automatically determined based on file extension
	     * @param tex Texture to write
	     * @param filename File to write to
	     * @return True in case the file could be written, otherwise false
	     */
	    bool write(ITexture* tex, std::string const& filename) const;
	    /**
	     * @brief Writes a texture to hard disk
	     * @details Image format is automatically determined based on file extension
	     * @param tex Texture to write
	     * @param filename File to write to
	     * @return True in case the file could be written, otherwise false
	     */
	    bool write(ITexture* tex, Filename const& filename) const;

	private:
	    AdvancedModule<ITextureFormat>* pickModule() const;

	    std::vector<AdvancedModule<ITextureFormat>*> m_modules;
    };
}

#endif /* TEXTURELOADER_H_ */
