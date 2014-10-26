//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IIMAGEFORMATMODULE_H_
#define IIMAGEFORMATMODULE_H_

#include <string>
#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Platform/File/Filename.h"

namespace dbgl
{
    /**
     * @brief Interface class for all image loader and writer modules
     */
    class IImageFormatModule
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~IImageFormatModule() = default;
	    /**
	     * @brief Checks if the module is capable of loading images
	     * @return True in case the module's load() methods work
	     */
	    virtual bool canLoad() const = 0;
	    /**
	     * @brief Checks if the module is capable of writing images
	     * @return True in case the module's write() methods work
	     */
	    virtual bool canWrite() const = 0;
	    /**
	     * @brief Checks if \p extension matches with the usual file extension
	     * 	      of the image format this module can handle
	     * @param extension File extension
	     * @return True in case the file extension matches the most common file
	     * 	       extensions for the image format this module can handle
	     */
	    virtual bool matchExtension(std::string const& extension) const = 0;
	    /**
	     * @brief Tries to load the image at \p path
	     * @param path Path to the image file
	     * @return Pointer to the loaded image or nullptr
	     */
	    virtual ITexture* load(std::string const& path) const = 0;
	    /**
	     * @brief Tries to load the image at \p path
	     * @param path Path to the image file
	     * @return Pointer to the loaded image or nullptr
	     */
	    virtual ITexture* load(Filename const& path) const = 0;
	    /**
	     * @brief Tries to write the image to \p path
	     * @param tex Texture to write
	     * @param path Path to write to
	     * @return True in case the image was written, otherwise false
	     */
	    virtual bool write(ITexture* tex, std::string const& path) const = 0;
	    /**
	     * @brief Tries to write the image to \p path
	     * @param tex Texture to write
	     * @param path Path to write to
	     * @return True in case the image was written, otherwise false
	     */
	    virtual bool write(ITexture* tex, Filename const& path) const = 0;
    };
}

#endif /* IIMAGEFORMATMODULE_H_ */
