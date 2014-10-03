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
    BitmapFont::BitmapFont()
    {
#include"DefaultFont.imp"
	load(size, reinterpret_cast<const char*>(data));
    }

    BitmapFont::BitmapFont(std::string const& filename)
    {
	load(filename);
    }

    BitmapFont::BitmapFont(unsigned int size, char const* data)
    {
	load(size, data);
    }

    BitmapFont::BitmapFont(BitmapFont const& other)
    {
	m_pTexture = new Texture{*other.m_pTexture};
	m_pSprite = new Sprite{*other.m_pSprite};
	m_header = other.m_header;
	m_rowPitch = other.m_rowPitch;
	std::copy(std::begin(other.m_widths), std::end(other.m_widths), std::begin(m_widths));
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
	// Try to open the file
	std::ifstream input{filename, std::ifstream::in | std::ifstream::binary | std::ios::ate};
	if(!input.good())
	{
	    LOG.warning("Unable to open file % for reading!", filename);
	    input.close();
	    return 1;
	}
	// Else read in data
	unsigned int filesize = input.tellg();
	input.seekg(0, std::ifstream::beg);
	char* data = new char[filesize];
	if(!data)
	{
	    LOG.error("Unable to allocate sufficient memory!");
	    input.close();
	    return 1;
	}
	input.read(data, filesize);
	input.close();

	load(filesize, data);
	delete [] data;

	return true;
    }

    bool BitmapFont::load(unsigned int filesize, char const* data)
    {
	// Variables to store data in
	m_header.id1 = data[0];
	m_header.id2 = data[1];
	// Note: Sometimes the files are misformatted and contain negative values for width or height instead of positive ones
	m_header.imgWidth = std::abs((data[2]<<0) | (data[3]<<8) | (data[4]<<16) | (data[5]<<24));
	m_header.imgHeight = std::abs((data[6]<<0) | (data[7]<<8) | (data[8]<<16) | (data[9]<<24));
	m_header.cellWidth = (data[10]<<0) | (data[11]<<8) | (data[12]<<16) | (data[13]<<24);
	m_header.cellHeight = (data[14]<<0) | (data[15]<<8) | (data[16]<<16) | (data[17]<<24);
	m_header.bpp = data[18];
	m_header.base = data[19];
	// Check if valid
	if(m_header.id1 != 0xBF || m_header.id2 != 0xF2)
	{
	    LOG.error("BFF2 bitmap font header invalid.");
	    return false;
	}
	// Reject unsupported bpp values
	if(m_header.bpp != 8 && m_header.bpp != 24 && m_header.bpp != 32)
	{
	    LOG.error("Bitmap font file has unsupported amount of bits per pixel.");
	    return false;
	}
	m_rowPitch = m_header.imgWidth / m_header.cellWidth;
	// Read in array with width of each character
	std::memcpy(&m_widths, &data[20], 256);
	// Read in texture
	long long int texDataSize { (std::abs(m_header.imgWidth) * std::abs(m_header.imgHeight)) * (m_header.bpp / 8) };
	const char* img = data + 276;
	if(276 + texDataSize != filesize)
	{
	    LOG.error("BFF2 bitmap font corrupt.");
	    return false;
	}

	// Create texture
	GLuint texId = GL_INVALID_VALUE;
	auto handle = GLProvider::get()->texGenerate(IGL::TextureType::TEX2D);
//	glGenTextures(1, &texId);
	texId = handle->m_handle; // TODO: DEBUG
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
		LOG.error("BFF2 Bitmap font corrupt.");
		break;
	}
	m_pTexture = new Texture {handle};
	m_pSprite = new Sprite {m_pTexture};
	m_pSprite->setFlipY(true);

	return true;
    }
}
