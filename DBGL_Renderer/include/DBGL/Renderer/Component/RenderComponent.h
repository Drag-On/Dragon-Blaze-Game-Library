//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_COMPONENT_RENDERCOMPONENT_H_
#define INCLUDE_DBGL_RENDERER_COMPONENT_RENDERCOMPONENT_H_

#include "IGameComponent.h"
#include "DBGL/Platform/Mesh/IMesh.h"
#include "DBGL/Core/Shape/Shapes.h"
#include "DBGL/Renderer/Material/IMaterial.h"

namespace dbgl
{
	/**
	 * @brief Render component, which is needed if an entity is supposed to be visible
	 */
	class RenderComponent: public IGameComponent
	{
	public:
		/**
		 * @brief Constructor
		 * @param material Material to use for rendering
		 * @param mesh Mesh to use for rendering
		 * @note A bounding sphere for the mesh will automatically be computed
		 */
		RenderComponent(IMaterial* material, IMesh* mesh);
		/**
		 * @brief Constructor
		 * @param material Material to use for rendering
		 * @param mesh Mesh to use for rendering
		 * @param boundingSphere Bounding sphere that fits the mesh
		 */
		RenderComponent(IMaterial* material, IMesh* mesh, Sphere<float> const& boundingSphere);
		/**
		 * @copydoc IGameComponent::update()
		 */
		virtual void update();
		/**
		 * @brief Retrieves the mesh
		 * @return The mesh
		 */
		IMesh* getMesh() const;
		/**
		 * @brief Sets a new mesh
		 * @param mesh New mesh
		 * @note A bounding sphere for the mesh will automatically be computed
		 */
		void setMesh(IMesh* mesh);
		/**
		 * @brief Sets a new mesh
		 * @param mesh New mesh
		 * @param boundingSphere Bounding sphere to use for the new mesh
		 */
		void setMesh(IMesh* mesh, Sphere<float> boundingSphere);
		/**
		 * @brief Retrieves the material
		 * @return The material
		 */
		IMaterial* getMaterial() const;
		/**
		 * @brief Sets a new material
		 * @param material New material
		 */
		void setMaterial(IMaterial* material);
		/**
		 * @brief Returns a bounding sphere of the visible data
		 * @return The bounding sphere
		 */
		Sphere<float> const& getBoundingSphere() const;
	private:
		IMaterial* m_pMaterial;
		IMesh* m_pMesh;
		Sphere<float> m_boundingSphere;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_COMPONENT_RENDERCOMPONENT_H_ */
