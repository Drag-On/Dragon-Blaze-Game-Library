//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_FILEFORMATIO_H_
#define INCLUDE_DBGL_RESOURCES_FILEFORMATIO_H_

#include <iostream>

#include "DBGL/Platform/Library/SimpleLibrary.h"
#include "DBGL/Platform/File/Filename.h"

namespace dbgl
{
    /**
     * @brief Loads resource files from hard disk and stores them
     * @details This class doesn't contain any code to load or write resource files of
     * 		type T, instead it loads dynamic libraries that contain such code. The
     * 		libraries must be compatible with the AdvancedModule class from DBGL_Platform,
     * 		and provide instances of subclasses of M.
     */
    template <class T, class M> class FileFormatIO
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    FileFormatIO();
	    /**
	     * @brief Destructor
	     */
	    ~FileFormatIO();
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
	     * @brief Loads a resource from a certain file
	     * @details The correct loader will be chosen based on file extension
	     * @param filename File to load
	     * @return Pointer to the loaded file or nullptr if not loaded
	     */
	    T* load(std::string const& filename) const;
	    /**
	     * @brief Loads a resource from a certain file
	     * @details The correct loader will be chosen based on file extension
	     * @param filename File to load
	     * @return Pointer to the loaded file or nullptr if not loaded
	     */
	    T* load(Filename const& filename) const;
	    /**
	     * @brief Writes a resource to hard disk
	     * @details Image format is automatically determined based on file extension
	     * @param res Resource to write
	     * @param filename File to write to
	     * @return True in case the file could be written, otherwise false
	     */
	    bool write(T* res, std::string const& filename) const;
	    /**
	     * @brief Writes a resource to hard disk
	     * @details Image format is automatically determined based on file extension
	     * @param res Resource to write
	     * @param filename File to write to
	     * @return True in case the file could be written, otherwise false
	     */
	    bool write(T* res, Filename const& filename) const;

	protected:
	    std::vector<SimpleLibrary<M>*> m_modules {};
    };
}

#include "FileFormatIO.imp"

#endif /* INCLUDE_DBGL_RESOURCES_FILEFORMATIO_H_ */
