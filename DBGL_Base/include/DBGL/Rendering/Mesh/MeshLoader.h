//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MESHLOADER_H_
#define MESHLOADER_H_

#include <string>
#include "DBGL/System/Bitmask/Bitmask.h"

namespace dbgl
{
    class Mesh;

    /**
     * @brief Interface for all texture loaders
     */
    class MeshLoader
    {
	public:
	    virtual ~MeshLoader() {};
	    /**
	     * @brief Loads the mesh from hard disk
	     * @param path Path of the mesh file
	     * @param flags Special behavior that may be requested from the loader
	     * @return The loaded mesh if everything went right, otherwise NULL
	     */
	    virtual Mesh* load(std::string path, Bitmask<> flags = 0) = 0;
	private:
    };
}

#endif /* MESHLOADER_H_ */
