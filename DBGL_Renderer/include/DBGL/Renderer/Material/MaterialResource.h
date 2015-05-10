//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_MATERIAL_MATERIALRESOURCE_H_
#define INCLUDE_DBGL_RENDERER_MATERIAL_MATERIALRESOURCE_H_

#include "IMaterial.h"
#include "DBGL/Resources/Manager/AbstractResource.h"
#include "DBGL/Core/Debug/Log.h"
#include <string>

namespace dbgl
{
	/**
	 * @brief Material resource
	 */
	class MaterialResource: public AbstractResource
	{
	public:
		/**
		 * @brief Constructor
		 * @param h Handle assigned to this resource
		 * @param name Name of this material
		 * @param material Material held by this resource
		 */
		MaterialResource(ResourceHandle h, std::string const& name, IMaterial* material);
		virtual void load();
		virtual void unload();
		/**
		 * @brief Identify this resource by its name
		 * @param name Name to check
		 * @return True in case the name, this resource was constructed from, matches the passed one
		 */
		bool identify(std::string const& name) const;
		/**
		 * @brief Retrieves the actual material
		 * @return Pointer to the loaded material or nullptr, if not loaded yet
		 */
		IMaterial* getMaterial();
	private:
		std::string m_name;
		IMaterial* m_pMaterial = nullptr;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_MATERIAL_MATERIALRESOURCE_H_ */
