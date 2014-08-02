//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SPRITE_H_
#define SPRITE_H_

#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Math/Hyperrectangle.h"

namespace dbgl
{
    class Sprite
    {
	public:
	    /**
	     * @brief Constructor
	     * @param tex Texture to get the sprite from
	     */
	    Sprite(Texture* tex);
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
	    Texture* getTexture() const;
	    /**
	     * @brief Replaces the texture used for this sprite
	     * @param tex New texture
	     * @note Crops Rect to the new texture size if necessary
	     */
	    void setTexture(Texture* tex);
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
	    Mesh* getMesh() const;
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
	    Texture* m_pTexture = nullptr;
	    /**
	     * @brief Rectangle to display
	     */
	    Rectangle<unsigned int> m_rect;
	    /**
	     * @brief Mesh to display the sprite on
	     */
	    Mesh* m_pMesh = nullptr;
	    /**
	     * @brief Indices of the corner vertices
	     */
	    unsigned int tl = 5, tr = 5, ll = 5, lr = 5;
    };
}



#endif /* SPRITE_H_ */
