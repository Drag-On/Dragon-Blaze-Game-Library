//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef LIGHTCOMPONENT_H_
#define LIGHTCOMPONENT_H_

#include "Entity.h"
#include "DBGL/Math/Vector3.h"
#include "DBGL/Math/Utility.h"

namespace dbgl
{
    /**
     * @brief Adds a light to an entity
     */
    class LightComponent : public Entity::Component
    {
	public:
	    /**
	     * @brief Type of light
	     */
	    enum class LightType : char
	    {
		POINT,      //!< POINT A point light, illuminating everything around it
		SPOT,       //!< SPOT A spot light, illuminating everything along a certain direction within a cone of light
		DIRECTIONAL,//!< DIRECTIONAL A directional light, illuminating everything along a certain direction
		AMBIENT,    //!< AMBIENT An ambient light which illuminates everything
	    };

	    /**
	     * @brief Constructor
	     * @param type Type of light
	     * @param color The light's color
	     * @param power The light's power
	     */
	    LightComponent(LightType type, Vec3f const& color = {1.0f, 1.0f, 1.0f}, float power = 1.0f);
	    /**
	     * @brief Provides access the the light's type
	     * @return The light's type
	     */
	    LightType& type();
	    /**
	     * @brief Provides read access the the light's type
	     * @return The light's type
	     */
	    LightType const& type() const;
	    /**
	     * @brief Provides access the the light's color
	     * @return The light's color
	     */
	    Vec3f& color();
	    /**
	     * @brief Provides read access the the light's color
	     * @return The light's color
	     */
	    Vec3f const& color() const;
	    /**
	     * @brief Provides access the the light's power
	     * @return The light's power
	     */
	    float& power();
	    /**
	     * @brief Provides read access the the light's power
	     * @return The light's power
	     */
	    float const& power() const;
	    /**
	     * @brief Provides access the the light's cutoff
	     * @return The light's cutoff
	     */
	    float& cutoff();
	    /**
	     * @brief Provides read access the the light's cutoff
	     * @return The light's cutoff
	     */
	    float const& cutoff() const;
	    /**
	     * @brief Provides access the the light's direction
	     * @return The light's direction
	     */
	    Vec3f& direction();
	    /**
	     * @brief Provides read access the the light's direction
	     * @return The light's direction
	     */
	    Vec3f const& direction() const;

	private:
	    /**
	     * @brief Type of the attached light
	     */
	    LightType m_type;
	    /**
	     * @brief The light's color
	     */
	    Vec3f m_color;
	    /**
	     * @brief Power of the light. Influences range.
	     */
	    float m_power;
	    /**
	     * @brief Maximum spread angle (for spotlights)
	     */
	    float m_cutoff = pi();
	    /**
	     * @brief Direction of light (for spot- and directional lights)
	     */
	    Vec3f m_direction{1.0f, 0.0f, 0.0f};
    };
}

#endif /* LIGHTCOMPONENT_H_ */
