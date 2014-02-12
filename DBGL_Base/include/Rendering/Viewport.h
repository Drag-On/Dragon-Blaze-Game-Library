//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <stdlib.h>
#include "Camera.h"

namespace dbgl
{
    /**
     * @brief Defines a rectangular frame inside of a window which can be drawn to
     */
    class Viewport
    {
	public:
	    /**
	     * @brief Constructor
	     * @param x X coordinate in window
	     * @param y Y coordinate in window
	     * @param width Viewport width
	     * @param height Viewport height
	     */
	    Viewport(unsigned int x, unsigned int y, unsigned int width,
		    unsigned int height);
	    ~Viewport();
	    /**
	     * @return X coordinate of frame
	     */
	    unsigned int getX() const;
	    /**
	     * @return Y coordinate of frame
	     */
	    unsigned int getY() const;
	    /**
	     * @return Frame width
	     */
	    unsigned int getWidth() const;
	    /**
	     * @return Frame height
	     */
	    unsigned int getHeight() const;
	    /**
	     * @param x New frame x coordinate
	     * @param y New frame y coordinate
	     */
	    void setPos(unsigned int x, unsigned int y);
	    /**
	     * @param width New frame width
	     * @param height New frame height
	     */
	    void setSize(unsigned int width, unsigned int height);
	    /**
	     * @return Pointer to the camera currently associated with this viewport
	     */
	    Camera* getCamera() const;
	    /**
	     * @param camera Pointer to the new camera that shall be associated
	     * 		     with this viewport
	     */
	    void setCamera(Camera* camera);
	private:
	    unsigned int _x, _y;
	    unsigned int _width, _height;
	    Camera* _camera;
    };
}

#endif /* VIEWPORT_H_ */
