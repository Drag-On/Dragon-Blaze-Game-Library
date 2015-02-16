//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SHADERPROGRAMGL33_H_
#define SHADERPROGRAMGL33_H_

#include "IShaderProgram.h"
#include "ShaderGL33.h"

namespace dbgl
{
	/**
	 * @brief OpenGL 3.3 implementation of the shader program class
	 */
	class ShaderProgramGL33: public IShaderProgram
	{
	public:
		/**
		 * @brief Constructor
		 */
		ShaderProgramGL33();
		virtual ~ShaderProgramGL33();
		virtual void attach(IShader* shader);
		virtual void link();
		virtual void use();
		virtual AttribHandle getAttributeHandle(std::string name) const;
		virtual UniformHandle getUniformHandle(std::string name) const;

		/**
		 * @return Internal shader program handle
		 */
		GLuint getHandle() const;

	private:
		GLuint m_id;

		void useInternal() const;
	};
}

#endif /* SHADERPROGRAMGL33_H_ */
