//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Texture/TextureGL33.h"
#include "DBGL/Platform/Texture/TextureCommandsGL33.h"

namespace dbgl
{
	TextureGL33::TextureGL33(Type type) :
			m_type { type }
	{
		glGenTextures(1, &m_id);
	}

	TextureGL33::~TextureGL33()
	{
		glDeleteTextures(1, &m_id);
	}

	void TextureGL33::bind()
	{
		glBindTexture(TextureCommandsGL33::texType2GL(m_type), m_id);
		TextureCommandsGL33::s_pCurTexture = this;
	}

	auto TextureGL33::getType() -> Type
	{
		return m_type;
	}

	GLuint TextureGL33::getHandle() const
	{
		return m_id;
	}

}

