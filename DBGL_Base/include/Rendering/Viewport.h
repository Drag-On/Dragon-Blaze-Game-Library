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
	     * @param xRatio Percentage of the frame buffer where this viewport
	     * 		     should start in x direction
	     * @param yRatio Percentage of the frame buffer where this viewport
	     * 		     should start in y direction
	     * @param widthRatio Percentage of the remaining part of the frame
	     * 			 buffer to claim for this viewport
	     * @param heightRatio Percentage of the remaining part of the frame
	     * 			  buffer to claim for this viewport
	     * @details A viewport with xRatio and yRatio both set to 0.5 and
	     * 		both widthRatio and heightRatio set to 1 will range from
	     * 		the center of the window to the bottom right corner
	     */
	    Viewport(float xRatio, float yRatio, float widthRatio,
		    float heightRatio);
	    ~Viewport();
	    /**
	     * @return X coordinate of frame
	     */
	    float getXRatio() const;
	    /**
	     * @return Y coordinate of frame
	     */
	    float getYRatio() const;
	    /**
	     * @return Frame width percentage
	     * @details This describes the amount of the framebuffer right and
	     * 		below of the viewport's coordinates should be used, i.e.
	     * 		if the viewport has the coordinates
	     */
	    float getWidthRatio() const;
	    /**
	     * @return Frame height percentage
	     */
	    float getHeightRatio() const;
	    /**
	     * @param xRatio Percentage of the frame buffer where this viewport
	     * 		     should start in x direction
	     * @param yRatio Percentage of the frame buffer where this viewport
	     * 		     should start in y direction
	     * @details A viewport with xRatio and yRatio both set to 0.5 will
	     * 		range from the center of the screen to the coordinate
	     * 		defined by the size ratio
	     */
	    void setPosRatio(float xRatio, float yRatio);
	    /**
	     * @param widthRatio Percentage of the remaining part of the frame
	     * 			 buffer to claim for this viewport
	     * @param heightRatio Percentage of the remaining part of the frame
	     * 			  buffer to claim for this viewport
	     * @details A viewport with both widthRatio and heightRatio set to 1
	     * 		will range from the position defined by the position ratio
	     * 		to the bottom right corner
	     */
	    void setSizeRatio(float widthRatio, float heightRatio);
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
	    /**
	     * @brief Updates the matrices, must be called once a frame
	     * @param frameWidth Width of the full window
	     * @param frameHeight Height of the full window
	     */
	    void update(float frameWidth, float frameHeight);
	    /**
	     * @return The (cached) view matrix
	     * @warning Needs to be updated using update() first!
	     */
	    Mat4f const& getViewMat() const;
	    /**
	     * @return The (cached) projection matrix
	     * @warning Needs to be updated using update() first!
	     */
	    Mat4f const& getProjectionMat() const;
	    /**
	     * @return The (cached) view-projection matrix
	     * @warning Needs to be updated using update() first!
	     */
	    Mat4f const& getViewProjectionMat() const;
	    /**
	     * @return The (cached) inverted transposed view matrix
	     * @warning Needs to be updated using update() first!
	     */
	    Mat4f const& getITViewMat() const;

	    float m_xRatio, m_yRatio;
	    float m_widthRatio, m_heightRatio;
	    Camera* m_camera;
	    Mat4f m_viewMat, m_projectionMat, m_viewProjectionMat, m_itView; // Cached matrizes

	    friend class RenderContext;
    };
}

#endif /* VIEWPORT_H_ */
