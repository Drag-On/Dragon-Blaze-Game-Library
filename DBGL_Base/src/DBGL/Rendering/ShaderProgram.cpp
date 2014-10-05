//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/ShaderProgram.h"

namespace dbgl
{
    ShaderProgram::ShaderProgram(const std::string vert, const std::string frag, bool isFiles)
    {
	std::string vertCode = "", fragCode = "";
	if (isFiles)
	{
	    // Read vertex shader code from file
	    vertCode = readFile(vert);

	    // Read fragment shader code from file
	    fragCode = readFile(frag);
	}
	else
	{
	    vertCode = vert;
	    fragCode = frag;
	}

	// Compile shaders
	IGL::ShaderHandle vsId = IGL::InvalidShaderHandle, fsId = IGL::InvalidShaderHandle;
	const std::string vertFileName = isFiles ? vert : "";
	const std::string fragFileName = isFiles ? frag : "";
	vsId = compile(vertCode, IGL::ShaderType::VERTEX, vertFileName);
	fsId = compile(fragCode, IGL::ShaderType::FRAGMENT, fragFileName);

	// Link shaders
	try
	{
	    m_shaderProgram = GLProvider::get()->shaCreateProgram();
	    GLProvider::get()->shaAttachShader(m_shaderProgram, vsId);
	    GLProvider::get()->shaAttachShader(m_shaderProgram, fsId);
	    GLProvider::get()->shaLinkProgram(m_shaderProgram);
	}
	catch (LinkException& e)
	{
	    LOG.error("Unable to link shader. %.", e.what());
	}

	// Delete vertex- and fragment shader objects again
	GLProvider::get()->shaDelete(vsId);
	GLProvider::get()->shaDelete(fsId);

	// Check for common uniform names
	checkUniforms();
    }

    ShaderProgram::~ShaderProgram()
    {
	GLProvider::get()->shaDeleteProgram(m_shaderProgram);
    }

    void ShaderProgram::use() const
    {
	GLProvider::get()->shaUseProgram(m_shaderProgram);
    }

    IGL::AttributeHandle ShaderProgram::getAttributeHandle(const std::string name) const
    {
	return GLProvider::get()->shaGetAttributeHandle(m_shaderProgram, name);
    }

    IGL::UniformHandle ShaderProgram::getUniformHandle(const std::string name) const
    {
	return GLProvider::get()->shaGetUniformHandle(m_shaderProgram, name);
    }

    void ShaderProgram::bindTexture(int texLocation, int texType, GLuint texHandle) const
    {
	glActiveTexture(texLocation);
	glBindTexture(texType, texHandle);
    }

    void ShaderProgram::setUniformFloat(IGL::UniformHandle const& handle, const float value) const
    {
	glUniform1f(handle->m_handle, value);
    }

    void ShaderProgram::setUniformFloat2(IGL::UniformHandle const& handle,
	    const float value[2]) const
    {
	glUniform2f(handle->m_handle, value[0], value[1]);
    }

    void ShaderProgram::setUniformFloat3(IGL::UniformHandle const& handle,
	    const float value[3]) const
    {
	glUniform3f(handle->m_handle, value[0], value[1], value[2]);
    }

    void ShaderProgram::setUniformFloat4(IGL::UniformHandle const& handle,
	    const float value[4]) const
    {
	glUniform4f(handle->m_handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgram::setUniformInt(IGL::UniformHandle const& handle, const int value) const
    {
	glUniform1i(handle->m_handle, value);
    }

    void ShaderProgram::setUniformInt2(IGL::UniformHandle const& handle, const int value[2]) const
    {
	glUniform2i(handle->m_handle, value[0], value[1]);
    }

    void ShaderProgram::setUniformInt3(IGL::UniformHandle const& handle, const int value[3]) const
    {
	glUniform3i(handle->m_handle, value[0], value[1], value[2]);
    }

    void ShaderProgram::setUniformInt4(IGL::UniformHandle const& handle, const int value[4]) const
    {
	glUniform4i(handle->m_handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgram::setUniformBool(IGL::UniformHandle const& handle, const bool value) const
    {
	glUniform1i(handle->m_handle, value);
    }

    void ShaderProgram::setUniformBool2(IGL::UniformHandle const& handle, const bool value[2]) const
    {
	glUniform2i(handle->m_handle, value[0], value[1]);
    }

    void ShaderProgram::setUniformBool3(IGL::UniformHandle const& handle, const bool value[3]) const
    {
	glUniform3i(handle->m_handle, value[0], value[1], value[2]);
    }

    void ShaderProgram::setUniformBool4(IGL::UniformHandle const& handle, const bool value[4]) const
    {
	glUniform4i(handle->m_handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgram::setUniformFloatArray(IGL::UniformHandle const& handle, unsigned int count,
	    const float* values) const
    {
	glUniform1fv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformFloat2Array(IGL::UniformHandle const& handle, unsigned int count,
	    const float* values) const
    {
	glUniform2fv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformFloat3Array(IGL::UniformHandle const& handle, unsigned int count,
	    const float* values) const
    {
	glUniform3fv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformFloat4Array(IGL::UniformHandle const& handle, unsigned int count,
	    const float* values) const
    {
	glUniform4fv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformIntArray(IGL::UniformHandle const& handle, unsigned int count,
	    const int* values) const
    {
	glUniform1iv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformInt2Array(IGL::UniformHandle const& handle, unsigned int count,
	    const int* values) const
    {
	glUniform2iv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformInt3Array(IGL::UniformHandle const& handle, unsigned int count,
	    const int* values) const
    {
	glUniform3iv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformInt4Array(IGL::UniformHandle const& handle, unsigned int count,
	    const int* values) const
    {
	glUniform4iv(handle->m_handle, count, values);
    }

    void ShaderProgram::setUniformFloatMatrix2Array(IGL::UniformHandle const& handle,
	    unsigned int count, bool transpose, const float* values) const
    {
	glUniformMatrix2fv(handle->m_handle, count, transpose, values);
    }

    void ShaderProgram::setUniformFloatMatrix3Array(IGL::UniformHandle const& handle,
	    unsigned int count, bool transpose, const float* values) const
    {
	glUniformMatrix3fv(handle->m_handle, count, transpose, values);
    }

    void ShaderProgram::setUniformFloatMatrix4Array(IGL::UniformHandle const& handle,
	    unsigned int count, bool transpose, const float* values) const
    {
	glUniformMatrix4fv(handle->m_handle, count, transpose, values);
    }

    void ShaderProgram::setUniformSampler(IGL::UniformHandle const& handle, const int value) const
    {
	glUniform1i(handle->m_handle, value);
    }

    GLuint ShaderProgram::getHandle() const
    {
	return m_shaderProgram->m_handle;
    }

    IGL::UniformHandle const& ShaderProgram::getDefaultUniformHandle(Uniform uniform) const
    {
	return m_uniformHandles.find(uniform)->second;
    }

    std::string ShaderProgram::getDefaultUniformName(Uniform uniform)
    {
	return uniformNames.at(uniform);
    }

    ShaderProgram* ShaderProgram::createSimpleShader()
    {
	const std::string vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec3 vertexPos;\n"
		"layout(location = 1) in vec2 vertexUV;\n"
		"layout(location = 2) in vec3 normal;\n"
		"out vec3 normal_cam;\n"
		"out vec2 uv;\n"
		"uniform mat4 MVP;\n"
		"uniform mat4 ITMV;\n"
		"void main(){\n"
		"gl_Position = MVP * vec4(vertexPos, 1);\n"
		"uv = vertexUV;\n"
		"normal_cam = normalize((ITMV * vec4(normal, 0)).xyz);\n"
		"}";
	const std::string fragmentShader = "#version 330 core\n"
		"in vec3 normal_cam;\n"
		"in vec2 uv;\n"
		"out vec4 color;\n"
		"uniform sampler2D tex_diffuse;\n"
		"void main(){\n"
		"float variance = max(0.0, dot(vec3(0, 0, 1), normal_cam));\n"
		"variance += max(0.0, dot(vec3(0, 0, 1), -normal_cam));\n"
		"color = texture(tex_diffuse, uv).rgba * variance;\n"
		"}";
	return new ShaderProgram { vertexShader, fragmentShader, false };
    }

    ShaderProgram* ShaderProgram::createSimpleColorShader()
        {
    	const std::string vertexShader = "#version 330 core\n"
    		"layout(location = 0) in vec3 vertexPos;\n"
    		"layout(location = 2) in vec3 normal;\n"
    		"out vec3 normal_cam;\n"
    		"uniform mat4 MVP;\n"
    		"uniform mat4 ITMV;\n"
    		"void main(){\n"
    		"gl_Position = MVP * vec4(vertexPos, 1);\n"
    		"normal_cam = normalize((ITMV * vec4(normal, 0)).xyz);\n"
    		"}";
    	const std::string fragmentShader = "#version 330 core\n"
    		"in vec3 normal_cam;\n"
    		"out vec3 color;\n"
    		"uniform vec3 v3_color;\n"
    		"void main(){\n"
    		"float variance = max(0.0, dot(vec3(0, 0, 1), normal_cam));\n"
    		"variance += max(0.0, dot(vec3(0, 0, 1), -normal_cam));\n"
    		"color = v3_color * variance;\n"
    		"}";
	return new ShaderProgram { vertexShader, fragmentShader, false };
        }

    ShaderProgram* ShaderProgram::createSpriteShader()
    {
	const std::string vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec3 vertexPos;\n"
		"layout(location = 1) in vec2 vertexUV;\n"
		"out vec2 uv;\n"
		"uniform vec2 v2_screenRes;\n"
		"uniform mat3 TRANSFORM_2D;\n"
		"void main(){\n"
		"vec2 halfRes = v2_screenRes / 2;\n"
		"vec2 clipPos = vec2(TRANSFORM_2D * vec3(vertexPos.xy, 1)) - halfRes;\n"
		"clipPos /= halfRes;\n"
		"gl_Position = vec4(clipPos, 0, 1);\n"
		"uv = vertexUV;\n"
		"}";
	const std::string fragmentShader = "#version 330 core\n"
		"in vec2 uv;\n"
		"out vec4 color;\n"
		"uniform sampler2D tex_diffuse;\n"
		"void main(){\n"
		"color = texture(tex_diffuse, uv).rgba;\n"
		"}";
	return new ShaderProgram { vertexShader, fragmentShader, false };
    }

    void ShaderProgram::checkUniforms()
    {
	use();
	// Iterate over uniform enum... not nice, but handy!
	for (int val = MODEL; val != BOGUS; val++)
	{
	    Uniform uniform = static_cast<Uniform>(val);
	    auto foo = uniformNames.find(uniform);
	    std::string name = foo->second;
	    const std::string nameCstr = name.c_str();
	    IGL::UniformHandle handle = getUniformHandle(nameCstr);
	    m_uniformHandles[uniform] = handle;
	}
    }

    std::string ShaderProgram::readFile(const std::string path)
    {
	std::string code = "";
	std::ifstream inStream(path, std::ios::in);
	if (inStream.is_open())
	{
	    std::string line = "";
	    while (getline(inStream, line))
		code += "\n" + line;
	    inStream.close();
	}
	else
	    LOG.error("Unable to open %.", path);
	return code;
    }

    IGL::ShaderHandle ShaderProgram::compile(const std::string code, IGL::ShaderType type, const std::string fileName)
    {
	// Create shader object
	IGL::ShaderHandle id = IGL::InvalidShaderHandle;

	if (code.length() == 0)
	{
	    LOG.error("Error compiling NULL shader");
	    return id;
	}

	try
	{
	    id = GLProvider::get()->shaCreate(type, code);
	}
	catch (CompileException& e)
	{
	    LOG.error("Error while compiling shader %. %", fileName, e.what());
	}

	return id;
    }

    // Initialize static variable
    std::map<ShaderProgram::Uniform, std::string> ShaderProgram::uniformNames =
    {
        { ShaderProgram::MODEL, "M" },
        { ShaderProgram::VIEW, "V" },
        { ShaderProgram::PROJECTION, "P" },
        { ShaderProgram::MV, "MV" },
        { ShaderProgram::MVP, "MVP" },
        { ShaderProgram::ITM, "ITM" },
        { ShaderProgram::ITV, "ITV" },
        { ShaderProgram::ITMV, "ITMV" },
        { ShaderProgram::TEX_DIFFUSE, "tex_diffuse" },
        { ShaderProgram::TEX_NORMAL, "tex_normal" },
        { ShaderProgram::TEX_SPECULAR, "tex_specular" },
        { ShaderProgram::SPEC_COLOR, "mat.v3_specColor" },
        { ShaderProgram::SPEC_WIDTH, "mat.f_specWidth" },
        { ShaderProgram::COLOR, "v3_color" },
        { ShaderProgram::LIGHTS, "lights" },
        { ShaderProgram::AMOUNTLIGHTS, "i_numLights" },
        { ShaderProgram::LIGHT_POS, "v3_position_w" },
        { ShaderProgram::LIGHT_COLOR, "v3_color" },
        { ShaderProgram::AMBIENT, "v3_ambientLight" },
        { ShaderProgram::SCREEN_RES, "v2_screenRes" },
        { ShaderProgram::TRANSFORM_2D, "TRANSFORM_2D" },
        { ShaderProgram::BOGUS, "" },
    };
}
