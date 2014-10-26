//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <string>
#include <algorithm>
#include "DBGL/Resources/Texture/IIMageFormatModule.h"

namespace dbgl
{
    class BMPModule : public IImageFormatModule
    {
	public:
	    virtual ~BMPModule() = default;

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
		return lowercaseExt == ".bmp" || lowercaseExt == "bmp";
	    }

	    virtual ITexture* load(std::string const& path) const
	    {
		return nullptr;
	    }

	    virtual ITexture* load(Filename const& path) const
	    {
		return nullptr;
	    }

	    virtual bool write(ITexture* tex, std::string const& path) const
	    {
		return false;
	    }

	    virtual bool write(ITexture* tex, Filename const& path) const
	    {
		return false;
	    }
    };
}

extern "C" dbgl::IImageFormatModule* create()
{
    return new dbgl::BMPModule{};
}

extern "C" void destroy(dbgl::IImageFormatModule* mod)
{
    delete mod;
}
