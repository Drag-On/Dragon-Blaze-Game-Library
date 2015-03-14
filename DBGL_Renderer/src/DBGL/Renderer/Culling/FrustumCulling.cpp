//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Culling/FrustumCulling.h"
#include <exception>

namespace dbgl
{
	FrustumCulling::FrustumCulling()
	{
	}

	void FrustumCulling::update()
	{
		// Calculate some helping vectors
		float tan = std::tan(m_pCam->getFieldOfView() / 2);
		float nearHeight = 2 * tan * m_pCam->getNear();
		float nearWidth = nearHeight * m_pCam->getRatio();
		float farHeight = 2 * tan * m_pCam->getFar();
		float farWidth = farHeight * m_pCam->getRatio();
		Vec3f farCenter = m_pCam->getPosition() + m_pCam->getDirection() * m_pCam->getFar();
		Vec3f nearCenter = m_pCam->getPosition() + m_pCam->getDirection() * m_pCam->getNear();
		Vec3f right = m_pCam->getDirection().cross(m_pCam->getUp());
		Vec3f camLeft = (nearCenter - right * (nearWidth / 2.0f) - m_pCam->getPosition()).normalize();
		Vec3f camRight = (nearCenter + right * (nearWidth / 2.0f) - m_pCam->getPosition()).normalize();
		Vec3f camTop = (nearCenter + m_pCam->getUp() * (nearHeight / 2.0f) - m_pCam->getPosition()).normalize();
		Vec3f camBot = (nearCenter - m_pCam->getUp() * (nearHeight / 2.0f) - m_pCam->getPosition()).normalize();

		// Calculate planes in order near, far, left, right, top, bottom;
		m_planes[0] = Plane<float>(nearCenter, m_pCam->getDirection());
		m_planes[1] = Plane<float>(farCenter, -m_pCam->getDirection());
		m_planes[2] = Plane<float>(m_pCam->getPosition(), camLeft.cross(m_pCam->getUp()));
		m_planes[3] = Plane<float>(m_pCam->getPosition(), m_pCam->getUp().cross(camRight));
		m_planes[4] = Plane<float>(m_pCam->getPosition(), camTop.cross(right));
		m_planes[5] = Plane<float>(m_pCam->getPosition(), right.cross(camBot));

		// Compute bounding sphere
		Vec3f farRight = farCenter + right * (farWidth / 2.0f);
		Vec3f farTopRight = farRight + m_pCam->getUp() * (farHeight / 2.0f);
		Vec3f nearRight = nearCenter + right * (nearWidth / 2.0f);
		Vec3f rightMiddle = nearRight + ((farRight - nearRight) / 2.0f);
		Vec3f const& rightDir = m_planes[3].normal();
		float lambda = (right * (nearCenter - rightMiddle)) / (right * rightDir);
		m_boundingSphere.center() = rightMiddle + rightDir * lambda;
		m_boundingSphere.radius() = (m_boundingSphere.center() - farTopRight).getLength();
	}

	bool FrustumCulling::checkPoint(Vec3f const& point)
	{
		// Transform point into clip space
		Mat4f vp = m_pCam->getProjectionMatrix() * m_pCam->getViewMatrix();
		Vec4f pClip = vp * Vec4f { point[0], point[1], point[2], 1 };
		float w = pClip.w();
		pClip /= w;
		// Check for planes
		return -1 < pClip.x() && pClip.x() < 1 && -1 < pClip.y() && pClip.y() < 1 && -1 < pClip.z() && pClip.z() < 1;
	}

	bool FrustumCulling::checkSphere(Vec3f const& center, float radius)
	{
		// Check against all planes
		for (unsigned int i = 0; i < 6; i++)
		{
			float distance = m_planes[i].getSignedDistance(center);
			if (distance < -radius)
				return false;
		}
		return true;
	}

	Sphere<float> const& FrustumCulling::getBoundingSphere() const
	{
		return m_boundingSphere;
	}

	void FrustumCulling::setCamera(ICameraEntity* pCam)
	{
		if (pCam)
			m_pCam = pCam;
		else
			throw std::invalid_argument("Can't use a null camera for culling.");
	}

	ICameraEntity* FrustumCulling::getCamera() const
	{
		return m_pCam;
	}
}
