//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Viewport.h"

namespace dbgl
{
    Viewport::Viewport(float xRatio, float yRatio, float widthRatio,
	    float heightRatio) :
	    m_xRatio(xRatio), m_yRatio(yRatio), m_widthRatio(widthRatio), m_heightRatio(
		    heightRatio), m_camera(NULL)
    {
    }

    Viewport::~Viewport()
    {
    }

    float Viewport::getXRatio() const
    {
	return m_xRatio;
    }

    float Viewport::getYRatio() const
    {
	return m_yRatio;
    }

    float Viewport::getWidthRatio() const
    {
	return m_widthRatio;
    }

    float Viewport::getHeightRatio() const
    {
	return m_heightRatio;
    }

    void Viewport::setPosRatio(float xRatio, float yRatio)
    {
	m_xRatio = xRatio;
	m_yRatio = yRatio;
    }

    void Viewport::setSizeRatio(float widthRatio, float heightRatio)
    {
	m_widthRatio = widthRatio;
	m_heightRatio = heightRatio;
    }

    Camera* Viewport::getCamera() const
    {
	return m_camera;
    }

    void Viewport::setCamera(Camera* camera)
    {
	m_camera = camera;
    }

    void Viewport::update(float frameWidth, float frameHeight)
    {
	if (m_camera != NULL)
	{
	    Vec3f direction, up;
	    m_camera->getOrientation(&direction, &up, NULL);
	    m_viewMat.view(m_camera->position(), direction, up);
	    m_projectionMat.projection(m_camera->getFieldOfView(),
		    (frameWidth * (m_widthRatio - m_xRatio))
			    / (frameHeight * (m_heightRatio - m_yRatio)),
		    m_camera->getNear(), m_camera->getFar());
	    m_viewProjectionMat = m_projectionMat * m_viewMat;
	    m_itView = m_viewMat;
	    m_itView.invert().transpose();
	}
    }

    Mat4f const& Viewport::getViewMat() const
    {
	return m_viewMat;
    }

    Mat4f const& Viewport::getProjectionMat() const
    {
	return m_projectionMat;
    }

    Mat4f const& Viewport::getViewProjectionMat() const
    {
	return m_viewProjectionMat;
    }

    Mat4f const& Viewport::getITViewMat() const
    {
	return m_itView;
    }
}

