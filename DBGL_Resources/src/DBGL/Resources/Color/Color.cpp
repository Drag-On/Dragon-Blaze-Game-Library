//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Color/Color.h"

namespace dbgl
{
	Color::Color() :
			m_components { 0, 0, 0, 255 }
	{
	}

	Color::Color(unsigned char components[4]) :
			m_components { components[0], components[1], components[2], components[3] }
	{
	}

	Color::Color(unsigned char components[3], unsigned char alpha) :
			m_components { components[0], components[1], components[2], alpha }
	{
	}

	Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) :
			m_components { red, green, blue, alpha }
	{
	}

	Color::Color(float red, float green, float blue, float alpha) :
			m_components { dbgl::clamp<float, unsigned char>(red * 255, 0, 255), dbgl::clamp<float, unsigned char>(
					green * 255, 0, 255), dbgl::clamp<float, unsigned char>(blue * 255, 0, 255), dbgl::clamp<float,
					unsigned char>(alpha * 255, 0, 255) }
	{
	}

	unsigned char const& Color::getRed() const
	{
		return m_components[0];
	}

	unsigned char const& Color::getGreen() const
	{
		return m_components[1];
	}

	unsigned char const& Color::getBlue() const
	{
		return m_components[2];
	}

	unsigned char const& Color::getAlpha() const
	{
		return m_components[3];
	}

	void Color::setRed(unsigned char red)
	{
		m_components[0] = red;
	}

	void Color::setRed(float red)
	{
		m_components[0] = red * 255;
	}

	void Color::setGreen(unsigned char green)
	{
		m_components[1] = green;
	}

	void Color::setGreen(float green)
	{
		m_components[1] = green * 255;
	}

	void Color::setBlue(unsigned char blue)
	{
		m_components[2] = blue;
	}

	void Color::setBlue(float blue)
	{
		m_components[2] = blue * 255;
	}

	void Color::setAlpha(unsigned char alpha)
	{
		m_components[3] = alpha;
	}

	void Color::setAlpha(float alpha)
	{
		m_components[3] = alpha * 255;
	}

}
