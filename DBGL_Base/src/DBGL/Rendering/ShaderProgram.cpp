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
	LOG.info("Creating shader program...");
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
	GLuint vsId = 0, fsId = 0;
	const std::string vertFileName = isFiles ? vert : "";
	const std::string fragFileName = isFiles ? frag : "";
	vsId = compile(vertCode.c_str(), GL_VERTEX_SHADER, vertFileName);
	fsId = compile(fragCode.c_str(), GL_FRAGMENT_SHADER, fragFileName);

	// Link shaders
	GLint linkOk = GL_FALSE;
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vsId);
	glAttachShader(m_shaderProgram, fsId);
	glLinkProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linkOk);
	if (!linkOk)
	LOG.error("Error while linking shaders.");
	printLog(m_shaderProgram, linkOk);

	// Delete vertex- and fragment shader objects again
	glDeleteShader(vsId);
	glDeleteShader(fsId);

	// Check for common uniform names
	checkUniforms();
    }

    ShaderProgram::~ShaderProgram()
    {
	glDeleteProgram(m_shaderProgram);
    }

    void ShaderProgram::use() const
    {
	glUseProgram(m_shaderProgram);
    }

    GLint ShaderProgram::getAttributeHandle(const std::string name) const
    {
	return glGetAttribLocation(m_shaderProgram, name.c_str());
    }

    GLint ShaderProgram::getUniformHandle(const std::string name) const
    {
	return glGetUniformLocation(m_shaderProgram, name.c_str());
    }

    void ShaderProgram::bindTexture(int texLocation, int texType, GLuint texHandle) const
    {
	glActiveTexture(texLocation);
	glBindTexture(texType, texHandle);
    }

    void ShaderProgram::setUniformFloat(GLint handle, const float value) const
    {
	glUniform1f(handle, value);
    }

    void ShaderProgram::setUniformFloat2(GLint handle,
	    const float value[2]) const
    {
	glUniform2f(handle, value[0], value[1]);
    }

    void ShaderProgram::setUniformFloat3(GLint handle,
	    const float value[3]) const
    {
	glUniform3f(handle, value[0], value[1], value[2]);
    }

    void ShaderProgram::setUniformFloat4(GLint handle,
	    const float value[4]) const
    {
	glUniform4f(handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgram::setUniformInt(GLint handle, const int value) const
    {
	glUniform1i(handle, value);
    }

    void ShaderProgram::setUniformInt2(GLint handle, const int value[2]) const
    {
	glUniform2i(handle, value[0], value[1]);
    }

    void ShaderProgram::setUniformInt3(GLint handle, const int value[3]) const
    {
	glUniform3i(handle, value[0], value[1], value[2]);
    }

    void ShaderProgram::setUniformInt4(GLint handle, const int value[4]) const
    {
	glUniform4i(handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgram::setUniformBool(GLint handle, const bool value) const
    {
	glUniform1i(handle, value);
    }

    void ShaderProgram::setUniformBool2(GLint handle, const bool value[2]) const
    {
	glUniform2i(handle, value[0], value[1]);
    }

    void ShaderProgram::setUniformBool3(GLint handle, const bool value[3]) const
    {
	glUniform3i(handle, value[0], value[1], value[2]);
    }

    void ShaderProgram::setUniformBool4(GLint handle, const bool value[4]) const
    {
	glUniform4i(handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgram::setUniformFloatArray(GLint handle, unsigned int count,
	    const float* values) const
    {
	glUniform1fv(handle, count, values);
    }

    void ShaderProgram::setUniformFloat2Array(GLint handle, unsigned int count,
	    const float* values) const
    {
	glUniform2fv(handle, count, values);
    }

    void ShaderProgram::setUniformFloat3Array(GLint handle, unsigned int count,
	    const float* values) const
    {
	glUniform3fv(handle, count, values);
    }

    void ShaderProgram::setUniformFloat4Array(GLint handle, unsigned int count,
	    const float* values) const
    {
	glUniform4fv(handle, count, values);
    }

    void ShaderProgram::setUniformIntArray(GLint handle, unsigned int count,
	    const int* values) const
    {
	glUniform1iv(handle, count, values);
    }

    void ShaderProgram::setUniformInt2Array(GLint handle, unsigned int count,
	    const int* values) const
    {
	glUniform2iv(handle, count, values);
    }

    void ShaderProgram::setUniformInt3Array(GLint handle, unsigned int count,
	    const int* values) const
    {
	glUniform3iv(handle, count, values);
    }

    void ShaderProgram::setUniformInt4Array(GLint handle, unsigned int count,
	    const int* values) const
    {
	glUniform4iv(handle, count, values);
    }

    void ShaderProgram::setUniformFloatMatrix2Array(GLint handle,
	    unsigned int count, bool transpose, const float* values) const
    {
	glUniformMatrix2fv(handle, count, transpose, values);
    }

    void ShaderProgram::setUniformFloatMatrix3Array(GLint handle,
	    unsigned int count, bool transpose, const float* values) const
    {
	glUniformMatrix3fv(handle, count, transpose, values);
    }

    void ShaderProgram::setUniformFloatMatrix4Array(GLint handle,
	    unsigned int count, bool transpose, const float* values) const
    {
	glUniformMatrix4fv(handle, count, transpose, values);
    }

    void ShaderProgram::setUniformSampler(GLint handle, const int value) const
    {
	glUniform1i(handle, value);
    }

    GLuint ShaderProgram::getHandle() const
    {
	return m_shaderProgram;
    }

    GLint ShaderProgram::getDefaultUniformHandle(Uniform uniform) const
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
		"out vec3 color;\n"
		"uniform sampler2D tex_diffuse;\n"
		"void main(){\n"
		"float variance = max(0.0, dot(vec3(0, 0, 1), normal_cam));\n"
		"variance += max(0.0, dot(vec3(0, 0, 1), -normal_cam));\n"
		"color = texture(tex_diffuse, uv).rgb * variance;\n"
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
	    GLint handle = getUniformHandle(nameCstr);
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

    void ShaderProgram::printLog(GLuint object, GLint ok)
    {
	GLint logLength = 0;

	// Get length of the log depending on object type
	if (glIsShader(object))
	    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
	else if (glIsProgram(object))
	    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
	else
	{
	    LOG.warning(
		    "Tried to print compile log for an object that is not a shader or program.");
	    return;
	}
	if (logLength > 0)
	{
	    char* msg = new char[logLength] {};

	    // Get actual log
	    if (glIsShader(object))
		glGetShaderInfoLog(object, logLength, NULL, msg);
	    else if (glIsProgram(object))
		glGetProgramInfoLog(object, logLength, NULL, msg);

	    if (msg[logLength - 2] == '\n')
		msg[logLength - 2] = 0;

	    if (ok)
		LOG.info(msg);
	    else
		LOG.error(msg);

	    delete [] msg;
	}
    }

    GLuint ShaderProgram::compile(const std::string code, GLenum type,
	    const std::string fileName)
    {
	if (code.length() == 0)
	{
	    LOG.error("Error compiling NULL shader");
	    return -1;
	}

	// Create shader object
	GLuint id = glCreateShader(type);

	// Compile
	const char* codePtr = code.c_str();
	glShaderSource(id, 1, &codePtr, NULL);
	glCompileShader(id);

	// Check if everything went right
	GLint result = GL_FALSE;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)
	LOG.error("Error while compiling shader %", fileName);
	printLog(id, result);
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
        { ShaderProgram::BOGUS, "" },
    };
}
