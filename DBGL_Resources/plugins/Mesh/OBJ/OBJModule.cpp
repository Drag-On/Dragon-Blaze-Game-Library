//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include "DBGL/Resources/Mesh/IMeshFormatModule.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    class OBJModule : public IMeshFormatModule
    {
	public:
	    virtual ~OBJModule() = default;

	    virtual bool canLoad() const
	    {
		return false;
	    }

	    virtual bool canWrite() const
	    {
		return false;
	    }

	    virtual bool matchExtension(std::string const& extension) const
	    {
		std::string lowercaseExt{};
		std::transform(extension.begin(), extension.end(), std::back_inserter(lowercaseExt), ::tolower);
		return lowercaseExt == ".obj" || lowercaseExt == "obj";
	    }

	    virtual IMesh* load(std::string const& path) const
	    {
		return load(Filename{path});
	    }

	    virtual IMesh* load(Filename const& path) const
	    {
		return nullptr;
	    }

	    virtual bool write(IMesh* mesh, std::string const& path) const
	    {
		return write(mesh, Filename{path});
	    }

	    virtual bool write(IMesh* mesh, Filename const& path) const
	    {
		return false;
	    }
    };
}

extern "C" dbgl::IMeshFormatModule* create()
{
    return new dbgl::OBJModule{};
}

extern "C" void destroy(dbgl::IMeshFormatModule* mod)
{
    delete mod;
}
