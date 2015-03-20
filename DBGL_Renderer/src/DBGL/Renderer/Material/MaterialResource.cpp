//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Material/MaterialResource.h"

namespace dbgl
{
	MaterialResource::MaterialResource(ResourceHandle h, std::string const& name, IMaterial* material)
			: AbstractResource(h), m_name(name), m_pMaterial(material)
	{
	}

	void MaterialResource::load()
	{
		m_pMaterial->load();
		AbstractResource::load();
	}

	void MaterialResource::unload()
	{
		m_pMaterial->unload();
		AbstractResource::unload();
	}

	bool MaterialResource::identify(std::string const& name) const
	{
		return m_name == name;
	}

	IMaterial* MaterialResource::getMaterial()
	{
		return m_pMaterial;
	}
}
