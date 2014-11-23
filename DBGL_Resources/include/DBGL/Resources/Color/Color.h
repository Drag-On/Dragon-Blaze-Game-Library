//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_UTILITY_COLOR_H_
#define INCLUDE_DBGL_CORE_UTILITY_COLOR_H_

#include "DBGL/Core/Math/Utility.h"

namespace dbgl
{
    /**
     * @brief Represents an RGBA color
     */
    class Color
    {
	public:
	    /**
	     * @brief Default constructor, color defaults to black
	     */
	    Color();
	    /**
	     * @brief Construct color from char array
	     * @param components Color components in RGBA order, in the range of 0 to 255
	     */
	    explicit Color(unsigned char components[4]);
	    /**
	     * @brief Construct color from char array
	     * @param components Color components in RGB order, in the range of 0 to 255
	     * @param alpha Alpha component in range 0 to 255
	     */
	    explicit Color(unsigned char components[3], unsigned char alpha = 255);
	    /**
	     * @brief Construct color from four components
	     * @param red Red component in the range 0 to 255
	     * @param green Green component in he range 0 to 255
	     * @param blue Blue component in he range 0 to 255
	     * @param alpha Alpha component in he range 0 to 255
	     */
	    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
	    /**
	     * @brief Construct color from four components
	     * @param red Red component in the range 0 to 1
	     * @param green Green component in he range 0 to 1
	     * @param blue Blue component in he range 0 to 1
	     * @param alpha Alpha component in he range 0 to 1
	     */
	    Color(float red, float green, float blue, float alpha = 1.0f);
	    /**
	     * @brief Retrieve the red component
	     * @return Red component in the range 0 to 255
	     */
	    unsigned char const& getRed() const;
	    /**
	     * @brief Retrieve the green component
	     * @return Green component in the range 0 to 255
	     */
	    unsigned char const& getGreen() const;
	    /**
	     * @brief Retrieve the blue component
	     * @return Blue component in the range 0 to 255
	     */
	    unsigned char const& getBlue() const;
	    /**
	     * @brief Retrieve the alpha component
	     * @return Alpha component in the range 0 to 255
	     */
	    unsigned char const& getAlpha() const;
	    /**
	     * @brief Modify red component
	     * @param red New red component in range 0 to 255
	     */
	    void setRed(unsigned char red);
	    /**
	     * @brief Modify red component
	     * @param red New red component in range 0 to 1
	     */
	    void setRed(float red);
	    /**
	     * @brief Modify green component
	     * @param red New green component in range 0 to 255
	     */
	    void setGreen(unsigned char green);
	    /**
	     * @brief Modify green component
	     * @param red New green component in range 0 to 1
	     */
	    void setGreen(float green);
	    /**
	     * @brief Modify blue component
	     * @param red New blue component in range 0 to 255
	     */
	    void setBlue(unsigned char blue);
	    /**
	     * @brief Modify blue component
	     * @param red New blue component in range 0 to 1
	     */
	    void setBlue(float blue);
	    /**
	     * @brief Modify alpha component
	     * @param red New alpha component in range 0 to 255
	     */
	    void setAlpha(unsigned char alpha);
	    /**
	     * @brief Modify alpha component
	     * @param red New alpha component in range 0 to 1
	     */
	    void setAlpha(float alpha);
	private:
	    unsigned char m_components[4];
    };
}

#endif /* INCLUDE_DBGL_CORE_UTILITY_COLOR_H_ */
