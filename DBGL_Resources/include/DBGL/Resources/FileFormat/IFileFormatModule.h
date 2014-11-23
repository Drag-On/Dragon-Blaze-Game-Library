//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IFILEFORMATMODULE_H_
#define IFILEFORMATMODULE_H_

#include <string>
#include "DBGL/Platform/File/Filename.h"

namespace dbgl
{
    /**
     * @brief Interface class for all file loader and writer modules
     */
    template <class T> class IFileFormatModule
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~IFileFormatModule() = default;
	    /**
	     * @brief Checks if the module is capable of loading files
	     * @return True in case the module's load() methods work
	     */
	    virtual bool canLoad() const = 0;
	    /**
	     * @brief Checks if the module is capable of writing files
	     * @return True in case the module's write() methods work
	     */
	    virtual bool canWrite() const = 0;
	    /**
	     * @brief Checks if \p extension matches with the usual file extension
	     * 	      of the file format this module can handle
	     * @param extension File extension
	     * @return True in case the file extension matches the most common file
	     * 	       extensions for the file format this module can handle
	     */
	    virtual bool matchExtension(std::string const& extension) const = 0;
	    /**
	     * @brief Tries to load the file at \p path
	     * @param path Path to the file
	     * @return Pointer to the loaded file or nullptr
	     */
	    virtual T* load(std::string const& path) const = 0;
	    /**
	     * @brief Tries to load the file at \p path
	     * @param path Path to the file
	     * @return Pointer to the loaded file or nullptr
	     */
	    virtual T* load(Filename const& path) const = 0;
	    /**
	     * @brief Tries to write the file to \p path
	     * @param data Data to write
	     * @param path Path to write to
	     * @return True in case the file was written, otherwise false
	     */
	    virtual bool write(T* data, std::string const& path) const = 0;
	    /**
	     * @brief Tries to write the image to \p path
	     * @param data Data to write
	     * @param path Path to write to
	     * @return True in case the image was written, otherwise false
	     */
	    virtual bool write(T* data, Filename const& path) const = 0;
    };
}

#endif /* IFILEFORMATMODULE_H_ */
