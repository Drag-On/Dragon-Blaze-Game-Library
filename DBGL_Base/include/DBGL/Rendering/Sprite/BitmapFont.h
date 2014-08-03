//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef BITMAPFONT_H_
#define BITMAPFONT_H_

#include <string>
#include <fstream>
#include "Sprite.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    /**
     * @brief Contains functionality to load a bitmap font from file and use it to draw text to the screen
     * @details The file to load has to be in the bff2 format, written by the tool "CBFG" (http://www.codehead.co.uk/cbfg/)
     */
    class BitmapFont
    {
	public:
	    /**
	     * @brief Constructor
	     * @param filename Path of the font file to load
	     */
	    BitmapFont(std::string const& filename);
	    /**
	     * @brief Copy constructor
	     * @param other BitmapFont to copy
	     */
	    BitmapFont(BitmapFont const& other);
	    /**
	     * @brief Destructor
	     */
	    ~BitmapFont();
	    /**
	     * @brief Assignment operator
	     * @param other BitmapFont to assign
	     * @return Reference to this BitmapFont
	     */
	    BitmapFont& operator=(BitmapFont const& other);
	    /**
	     * @brief Calculates the width of the passed string when displayed
	     * @param text String to display
	     * @return Width in pixels of \p text when displayed
	     * @note Does not account for newlines.
	     */
	    unsigned int getWidth(std::string text) const;
	    /**
	     * @brief Provides the maximum height of a line of text using this font
	     * @return The height of the font in pixels
	     */
	    unsigned int getLineHeight() const;
	    /**
	     * @brief Provides a sprite that shows the character defined by \p c
	     * @param c Character to get sprite for
	     * @return Reference to sprite that is set up to show the passed character.
	     */
	    Sprite& getSprite(char c);
	private:
	    /**
	     * @brief loads the font file
	     * @param filename Path of the font
	     * @return True if everything went right, otherwise false
	     */
	    bool load(std::string const& filename);

	    static const unsigned int headerSize = 20;
	    Texture* m_pTexture;
	    Sprite* m_pSprite;
	    struct FileHeader
	    {
		public:
		    unsigned char id1 = 0, id2 = 0;
		    int imgWidth = 0, imgHeight = 0, cellWidth = 0, cellHeight = 0;
		    unsigned char bpp = 0, base = 0;
	    } m_header;
	    int m_rowPitch;
	    char m_widths[256];
    };
}

#endif /* BITMAPFONT_H_ */
