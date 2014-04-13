//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef OBJMESHLOADER_H_
#define OBJMESHLOADER_H_

#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Mesh.h"
#include "MeshLoader.h"

namespace dbgl
{
    /**
     * @brief Capable of loading meshes in OBJ file format
     */
    class OBJMeshLoader: public MeshLoader
    {
	public:
	    Mesh* load(std::string path, Bitmask flags = 0);
	private:
    };
}

#endif /* OBJMESHLOADER_H_ */
