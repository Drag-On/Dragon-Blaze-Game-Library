//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Sprite/BitmapFont.h"

namespace dbgl
{
    BitmapFont::BitmapFont(std::string const& filename)
    {
	load(filename);
    }

    BitmapFont::BitmapFont(BitmapFont const& other)
    {
	m_pTexture = new Texture{*other.m_pTexture};
	m_pSprite = new Sprite{*other.m_pSprite};
    }

    BitmapFont::~BitmapFont()
    {
	delete m_pTexture;
	delete m_pSprite;
    }

    BitmapFont& BitmapFont::operator=(BitmapFont const& other)
    {
	if(this != &other)
	{
	    delete m_pTexture;
	    delete m_pSprite;
	    m_pTexture = new Texture{*other.m_pTexture};
	    m_pSprite = new Sprite{*other.m_pSprite};
	}
	return *this;
    }

    unsigned int BitmapFont::getWidth(std::string text) const
    {
	// Iterate over all characters and add up their widths
	unsigned int width = 0;
	for(char& c : text)
	{
	    width += m_widths[static_cast<int>(c)];
	}
	return width;
    }

    unsigned int BitmapFont::getLineHeight() const
    {
	return m_header.cellHeight;
    }

    Sprite& BitmapFont::getSprite(char c)
    {
	unsigned int row = (c - m_header.base) / m_rowPitch;
	unsigned int col = (c - m_header.base) - row * m_rowPitch;
	Rectangle<unsigned int> rect{};
	rect.pos() = Vector2<unsigned int>{col * m_header.cellWidth, row * m_header.cellHeight};
	rect.extent() = Vector2<unsigned int> { static_cast<unsigned int>(m_widths[static_cast<int>(c)]),
	    static_cast<unsigned int>(m_header.cellHeight) };
	m_pSprite->setRect(rect);
	return *m_pSprite;
    }

    void BitmapFont::drawText(RenderContext& rc, ShaderProgram const& shader, std::string text, unsigned int x, unsigned int y)
    {
	shader.use();
	unsigned int cursor = 0;
	for(char& c : text)
	{
	    // Check for uniforms
	    GLint transformId = shader.getDefaultUniformHandle(ShaderProgram::Uniform::TRANSFORM_2D);
	    GLint screenResId = shader.getDefaultUniformHandle(ShaderProgram::Uniform::SCREEN_RES);
	    if (screenResId <= 0 || transformId <= 0)
		return;
	    // Diffuse texture
	    GLint diffuseId = shader.getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
	    if (diffuseId >= 0)
	    {
		// Bind diffuse texture to unit 0
		shader.bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, m_pTexture->getHandle());
		shader.setUniformSampler(diffuseId, 0);
	    }

	    // Set blend mode
	    auto srcBlend = rc.getSrcAlphaBlend();
	    auto destBlend = rc.getDestAlphaBlend();
	    switch (m_header.bpp)
	    {
		case 8:
		    rc.setAlphaBlend(RenderContext::AlphaBlendValue::SrcAlpha, RenderContext::AlphaBlendValue::SrcAlpha);
		    break;
		case 24:
		    rc.setAlphaBlend(RenderContext::AlphaBlendValue::Zero, RenderContext::AlphaBlendValue::Zero);
		    break;
		case 32:
		    rc.setAlphaBlend(RenderContext::AlphaBlendValue::One, RenderContext::AlphaBlendValue::OneMinusSrcAlpha);
		    break;
	    }
	    rc.setAlphaBlend(srcBlend, destBlend);

	    // Sprite will be drawn in the top left corner
	    // Send to shader
	    Mat3f transform = Mat3f::make2DTranslation(x + cursor, y);
	    shader.setUniformFloat2(screenResId, Vec2f { static_cast<float>(rc.getWidth()),
		    static_cast<float>(rc.getHeight()) }.getDataPointer());
	    shader.setUniformFloatMatrix3Array(transformId, 1, GL_FALSE, transform.getDataPointer());
	    rc.draw(*getSprite(c).getMesh());
	    // Move cursor right
	    cursor += m_widths[static_cast<int>(c)];
	}
    }

    bool BitmapFont::load(std::string const& filename)
    {
	// Variables to store data in
	char headDat[headerSize]{};
	char* img = nullptr;
	// Stream to read from
	std::fstream in{};
	// Open file
	in.open(filename.c_str(), std::ios_base::binary | std::ios_base::in);
	// Everything alright?
	if(!in.is_open())
	    return false;
	// Read in header
	in.read(&(headDat[0]), headerSize);
	m_header.id1 = headDat[0];
	m_header.id2 = headDat[1];
	m_header.imgWidth = (headDat[2]<<0) | (headDat[3]<<8) | (headDat[4]<<16) | (headDat[5]<<24);
	m_header.imgHeight = (headDat[6]<<0) | (headDat[7]<<8) | (headDat[8]<<16) | (headDat[9]<<24);
	m_header.cellWidth = (headDat[10]<<0) | (headDat[11]<<8) | (headDat[12]<<16) | (headDat[13]<<24);
	m_header.cellHeight = (headDat[14]<<0) | (headDat[15]<<8) | (headDat[16]<<16) | (headDat[17]<<24);
	m_header.bpp = headDat[18];
	m_header.base = headDat[19];
	// Check if valid
	if(m_header.id1 != 0xBF || m_header.id2 != 0xF2)
	{
	    in.close();
	    LOG.error("Invalid BFF2 bitmap font file \"%\".", filename.c_str());
	    return false;
	}
	// Reject unsupported bpp values
	if(m_header.bpp != 8 && m_header.bpp != 24 && m_header.bpp != 32)
	{
	    in.close();
	    LOG.error("Bitmap font file \"%\" has unsupported amount of bits per pixel.", filename.c_str());
	    return false;
	}
	m_rowPitch = m_header.imgWidth / m_header.cellWidth;
	// Read in array with width of each character
	in.read(&(m_widths[0]), 256);
	// Read in texture
	long long int texDataSize = (m_header.imgWidth * m_header.imgHeight) * (m_header.bpp / 8);
	img = new char[texDataSize];
	if(!img)
	{
	    in.close();
	    LOG.error("Unable to allocate memory for bitmap font file \"%\".", filename.c_str());
	    return false;
	}
	in.read(img, texDataSize);
	in.close();

	// Create texture
	GLuint texId = GL_INVALID_VALUE;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Tex creation params are dependent on BPP
	switch (m_header.bpp)
	{
	    case 8:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_header.imgWidth, m_header.imgHeight, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, img);
		break;
	    case 24:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_header.imgWidth, m_header.imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		break;
	    case 32:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_header.imgWidth, m_header.imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		break;
	    default:
		// Should never get here
		LOG.error("Bitmap font file \"%\" corrupt.", filename.c_str());
		break;
	}
	m_pTexture = new Texture {texId};
	m_pSprite = new Sprite {m_pTexture};
	m_pSprite->setFlipY(true);

	delete [] img;
	return true;
    }
}
