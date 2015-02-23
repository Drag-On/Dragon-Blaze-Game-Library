//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Texture/TextureGL33.h"
#include "DBGL/Platform/Texture/TextureCommandsGL33.h"

namespace dbgl
{
	TextureGL33::TextureGL33(Type type) :
			m_type { type }
	{
		glGenTextures(1, &m_id);
	}

	TextureGL33::TextureGL33(TextureGL33 const& copy)
			: m_type { copy.m_type }
	{
		glGenTextures(1, &m_id);
		copy.bind();
		auto width = Platform::get()->curTexture()->getWidth();
		auto height = Platform::get()->curTexture()->getHeight();
		char* buffer = new char[width * height * 4];
		Platform::get()->curTexture()->getPixelData(ITextureCommands::PixelFormat::RGBA, ITextureCommands::PixelType::UBYTE, buffer, 0);
		bind();
		Platform::get()->curTexture()->write(0, width, height, ITextureCommands::PixelFormat::RGBA, ITextureCommands::PixelType::UBYTE, buffer);
		Platform::get()->curTexture()->generateMipMaps();
	}

    TextureGL33& TextureGL33::operator=(TextureGL33 const& copy)
    {
    	if(this != &copy)
    	{
    		this->~TextureGL33();
    		m_type = copy.m_type;
    		glGenTextures(1, &m_id);
    	}
    	return *this;
    }

	TextureGL33::~TextureGL33()
	{
		glDeleteTextures(1, &m_id);
	}

	void TextureGL33::bind() const
	{
		glBindTexture(TextureCommandsGL33::texType2GL(m_type), m_id);
		TextureCommandsGL33::s_pCurTexture = const_cast<TextureGL33*>(this); // TODO: This is bad!
	}

	auto TextureGL33::getType() const -> Type
	{
		return m_type;
	}

	ITexture* TextureGL33::clone() const
	{
		TextureGL33* clone = new TextureGL33(*this);
		return clone;
	}

	GLuint TextureGL33::getHandle() const
	{
		return m_id;
	}

}

