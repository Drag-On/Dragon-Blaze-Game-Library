//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_SPRITE_SPRITE_H_
#define INCLUDE_DBGL_RESOURCES_SPRITE_SPRITE_H_

#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Platform/Mesh/IMesh.h"
#include "DBGL/Core/Math/Hyperrectangle.h"

namespace dbgl
{
	/**
	 * @brief Represents a section of a two-dimensional texture, that is supposed to be drawn onto a plane, e.g. the screen.
	 * @details Automatically creates a mesh which tightly fits to the selected part of the texture and has the right UVs to show it.
	 */
	class Sprite
	{
	public:
		/**
		 * @brief Constructor
		 * @param tex Texture to get the sprite from
		 */
		Sprite(ITexture* tex);
		/**
		 * @brief Destructor
		 */
		~Sprite();
		/**
		 * @brief Copy constructor
		 * @param other Sprite to copy
		 */
		Sprite(Sprite const& other);
		/**
		 * @brief Assignment operator
		 * @param other Sprite to assign
		 * @return Reference to this
		 */
		Sprite& operator=(Sprite const& other);
		/**
		 * @brief Returns the texture used for this sprite
		 * @return The texture used for this sprite
		 */
		ITexture* getTexture() const;
		/**
		 * @brief Replaces the texture used for this sprite
		 * @param tex New texture
		 * @note Crops Rect to the new texture size if necessary
		 */
		void setTexture(ITexture* tex);
		/**
		 * @brief Returns the rectangle on the used texture used for this sprite
		 * @return Rectangle on the used texture used for this sprite
		 */
		Rectangle<unsigned int> const& getRect() const;
		/**
		 * @brief Replaces the rectangle on the used texture
		 * @param rect New rectangle
		 */
		void setRect(Rectangle<unsigned int> rect);
		/**
		 * @brief Returns the mesh fitting to the currently chosen rectangle
		 * @return Mesh fitting to the currently chosen rectangle
		 */
		IMesh* getMesh() const;
		/**
		 * @brief Returns the width of the currently selected part of the texture
		 * @return Width of the currently selected part of the texture
		 */
		unsigned int getWidth() const;
		/**
		 * @brief Returns the height of the currently selected part of the texture
		 * @return Height of the currently selected part of the texture
		 */
		unsigned int getHeight() const;
		/**
		 * @brief Checks if this sprite is flipped horizontally
		 * @return True in case the sprite is flipped horizontally
		 */
		bool getFlipX() const;
		/**
		 * @brief Allows to flip this sprite horizontally
		 * @param flip True to flip, otherwise false
		 */
		void setFlipX(bool flip);
		/**
		 * @brief Checks if this sprite is flipped vertically
		 * @return True in case the sprite is flipped vertically
		 */
		bool getFlipY() const;
		/**
		 * @brief Allows to flip this sprite vertically
		 * @param flip True to flip, otherwise false
		 */
		void setFlipY(bool flip);
	private:
		/**
		 * @brief Recomputes mesh proportions and UVs
		 */
		void recomputeMesh();
		/**
		 * @brief Validates the rectangle and crops it to the texture size if needed
		 */
		void validateRect();

		/**
		 * @brief Texture to get sprite from
		 */
		ITexture* m_pTexture = nullptr;
		/**
		 * @brief Rectangle to display
		 */
		Rectangle<unsigned int> m_rect;
		/**
		 * @brief Mesh to display the sprite on
		 */
		IMesh* m_pMesh = nullptr;
		/**
		 * @brief Indices of the corner vertices
		 */
		unsigned int tl = 5, tr = 5, ll = 5, lr = 5;
		/**
		 * @brief Inverts x or y uvs
		 */
		bool m_flipX = false, m_flipY = false;
	};
}

#endif /* INCLUDE_DBGL_RESOURCES_SPRITE_SPRITE_H_ */
