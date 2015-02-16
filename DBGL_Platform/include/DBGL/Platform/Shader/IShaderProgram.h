//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ISHADERPROGRAM_H_
#define ISHADERPROGRAM_H_

#include "IShader.h"

namespace dbgl
{
	/**
	 * @brief Interface class for shader programs.
	 * @details Shader programs consist of multiple shaders, mostly vertex- and fragment shaders,
	 * 		who work together to create some image on screen.
	 */
	class IShaderProgram
	{
	public:
		/**
		 * @brief Handles that distinctly describe an attribute within a program
		 */
		using AttribHandle = int;
		/**
		 * @brief Handles that distinctly describe a uniform within a program
		 */
		using UniformHandle = int;
		/**
		 * @brief Value of invalid attribute handles
		 */
		static constexpr AttribHandle InvalidAttribHandle = -1;
		/**
		 * @brief Value of invalid uniform handles
		 */
		static constexpr UniformHandle InvalidUniformHandle = -1;

		/**
		 * @brief Destructor
		 */
		virtual ~IShaderProgram() = default;
		/**
		 * @brief Attach a shader to this program
		 * @note The passed shader needs to be compiled
		 * @param shader Shader to attach
		 */
		virtual void attach(IShader* shader) = 0;
		/**
		 * @brief Link the attached shaders
		 */
		virtual void link() = 0;
		/**
		 * @brief Start using this shader program
		 */
		virtual void use() = 0;
		/**
		 * @brief Provides a handle for a attribute by its name
		 * @param name Attribute name
		 * @return Handle to the attribute or InvalidAttribHandle if no attribute with name \p name could be found
		 */
		virtual AttribHandle getAttributeHandle(std::string name) const = 0;
		/**
		 * @brief Provides a handle for a uniform by its name
		 * @param name Uniform name
		 * @return Handle to the uniform or InvalidUniformHandle if no uniform with name \p name could be found
		 */
		virtual UniformHandle getUniformHandle(std::string name) const = 0;
	};
}

#endif /* ISHADERPROGRAM_H_ */
