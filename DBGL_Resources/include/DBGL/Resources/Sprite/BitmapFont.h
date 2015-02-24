//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_SPRITE_BITMAPFONT_H_
#define INCLUDE_DBGL_RESOURCES_SPRITE_BITMAPFONT_H_

#include <string>
#include <fstream>
#include <string>
#include "Sprite.h"
#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Platform/RenderContext/IRenderContext.h"
#include "DBGL/Platform/Shader/IShaderProgram.h"
#include "DBGL/Core/Math/Matrix3x3.h"
#include "DBGL/Core/Debug/Log.h"

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
		 * @brief Constructs a default font
		 * @details This font may only include the most common english symbols. No fancy stuff.
		 */
		BitmapFont();
		/**
		 * @brief Constructor
		 * @param filename Path of the font file to load
		 */
		BitmapFont(std::string const& filename);
		/**
		 * @brief Constructs a font from a series of bytes
		 * @param size Size to pass
		 * @param data Data in a contiguous array
		 * @note The data passed to \p data must be freed after using this method. It will be left untouched.
		 */
		BitmapFont(unsigned int size, char const* data);
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
		/**
		 * @brief Draws a text to the passed render context
		 * @param rc Render context to use
		 * @param shader Shader to use
		 * @param text Message to display
		 * @param x X display coordinate to start text at
		 * @param y Y display coordinate to start text at
		 * @note This assumes that the render context has been properly set up beforehand
		 */
		void drawText(IRenderContext* rc, IShaderProgram* shader, std::string const& text, unsigned int x, unsigned int y);
	private:
		/**
		 * @brief Loads the font file
		 * @param filename Path of the font
		 * @return True if everything went right, otherwise false
		 */
		bool load(std::string const& filename);
		/**
		 * @brief Loads a font file from raw data
		 * @param filesize Size of the file
		 * @param data Data array
		 * @note The data passed to \p data must be freed after using this method. It will be left untouched.
		 * @return True if everything went right, otherwise false
		 */
		bool load(unsigned int filesize, char const* data);

		static const unsigned int headerSize = 20;
		ITexture* m_pTexture;
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

#endif /* INCLUDE_DBGL_RESOURCES_SPRITE_BITMAPFONT_H_ */
