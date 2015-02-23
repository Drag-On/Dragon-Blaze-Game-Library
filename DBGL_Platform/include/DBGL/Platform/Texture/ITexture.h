//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ITEXTURE_H_
#define ITEXTURE_H_

namespace dbgl
{
	/**
	 * @brief Interface class for textures
	 */
	class ITexture
	{
	public:
		/**
		 * @brief Lists all supported texture types
		 */
		enum class Type
		{
			TEX2D, //!< TEX2D
		};

		/**
		 * @brief Destructor
		 */
		virtual ~ITexture() = default;
		/**
		 * @brief Binds the texture to a texture unit
		 */
		virtual void bind() const = 0;
		/**
		 * @brief Retrieves the type of this texture
		 * @return Texture type
		 */
		virtual Type getType() const = 0;
		/**
		 * @brief Produces a deep copy of this texture
		 * @return The copy
		 */
		virtual ITexture* clone() const = 0;
	};
}

#endif /* ITEXTURE_H_ */
