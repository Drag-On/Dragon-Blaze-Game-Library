//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTRENDERER_H_
#define ABSTRACTRENDERER_H_

#include <vector>
#include <limits>
#include <string>

namespace dbgl
{
    class Renderer
    {
	private:
	    /**
	     * @brief Instance of the renderer implementation to use
	     */
	    static Renderer* pInstance;
	public:
	    /**
	     * @brief Identifier of a certain index buffer
	     */
	    using IndexBufferId = unsigned int;
	    /**
	     * @brief Identifier of a certain vertex buffer
	     */
	    using VertexBufferId = unsigned int;
	    /**
	     * @brief Value for specifying an invalid index buffer
	     */
	    static constexpr IndexBufferId INVALID_INDEX_BUFFER = std::numeric_limits<IndexBufferId>::max();
	    /**
	     * @brief Value for specifying an invalid vertex buffer
	     */
	    static constexpr VertexBufferId INVALID_VERTEX_BUFFER = std::numeric_limits<VertexBufferId>::max();
	    /**
	     * @brief Identifier of a certain vertex format
	     */
	    using VertexFormatId = unsigned int;

	    /**
	     * @brief Identifier for textures
	     */
	    using TextureBuffer2dId = unsigned int;
	    /**
	     * @brief Value for specifying an invalid vertex buffer
	     */
	    static constexpr TextureBuffer2dId INVALID_TEXTURE_BUFFER_2D = std::numeric_limits<TextureBuffer2dId>::max();
	    /**
	     * @brief Format used by a texture
	     */
	    enum class TextureFormat : char
	    {
		RGB,//!< RGB
		BGR,//!< BGR
	    };

	    /**
	     * @brief Type of buffer
	     */
	    enum class BufferType : char
	    {
		STATIC, //!< STATIC
		DYNAMIC,//!< DYNAMIC
	    };
	    /**
	     * @brief Specifies what kind of polygon is used
	     */
	    enum class PolygonMode : char
	    {
		TRIANGLE,//!< TRIANGLE
	    };
	    /**
	     * @brief Attribute format
	     */
	    enum class AttribFormat : char
	    {
		FLOAT,	//!< FLOAT
		SHORT,	//!< SHORT
		BYTE,	//!< BYTE
	    };
	    /**
	     * @brief Type of a vertex attribute
	     */
	    using AttribId = unsigned int;
	    /**
	     * @brief Supported blend modes
	     */
	    enum class BlendMode : char
	    {
		ZERO,               //!< ZERO
		ONE,                //!< ONE
		SRC_COLOR,          //!< SRC_COLOR
		ONE_MINUS_SRC_COLOR,//!< ONE_MINUS_SRC_COLOR
		DST_COLOR,          //!< DST_COLOR
		ONE_MINUS_DST_COLOR,//!< ONE_MINUS_DST_COLOR
		SRC_ALPHA,          //!< SRC_ALPHA
		ONE_MINUS_SRC_ALPHA,//!< ONE_MINUS_SRC_ALPHA
		DST_ALPHA,          //!< DST_ALPHA
		ONE_MINUS_DST_ALPHA,//!< ONE_MINUS_DST_ALPHA
//		CONSTANT_COLOR,
//		ONE_MINUS_CONSTANT_COLOR,
//		CONSTANT_ALPHA,
//		ONE_MINUS_CONSTANT_ALPHA,
	    };
	    /**
	     * @brief Supported depth testing modes
	     */
	    enum class DepthTestMode : char
	    {
		NEVER,   //!< NEVER
		LESS,    //!< LESS
		EQUAL,   //!< EQUAL
		LEQUAL,  //!< LEQUAL
		GREATER, //!< GREATER
		NOTEQUAL,//!< NOTEQUAL
		GEQUAL,  //!< GEQUAL
		ALWAYS,  //!< ALWAYS
	    };
	    /**
	     * @brief Supported stencil testing modes
	     */
	    enum class StencilTestMode : char
	    {
		KEEP,    //!< KEEP
		SET_ZERO,//!< SET_ZERO
		REPLACE, //!< REPLACE
		INVERT,  //!< INVERT
		INCR,    //!< INCR
		DECR,    //!< DECR
		INCR_SAT,//!< INCR_SAT
		DECR_SAT,//!< DECR_SAT
	    };
	    /**
	     * @brief Supported culling modes
	     */
	    enum class CullingMode : char
	    {
		NONE, //!< NONE
		BACK, //!< BACK
		FRONT,//!< FRONT
	    };
	protected:
	    struct VertexFormat
	    {
		AttribId id;
		unsigned int size;
		AttribFormat format;
	    };
	public:
	    /**
	     * @brief Provides access to the renderer
	     * @return The current renderer
	     */
	    static Renderer* get();
	    /**
	     * @brief Sets the renderer to use
	     * @note Should be used only once
	     * @warning The passed instance needs to be freed manually!
	     * @param renderer Renderer to set
	     */
	    static void set(Renderer* renderer);
	    /**
	     * @brief Destructor
	     */
	    virtual ~Renderer() = default;
	    /**
	     * @brief Generates a vertex buffer
	     * @param size Size of the buffer to create
	     * @param type Buffer type
	     * @param data Data to initialize the buffer with
	     * @return Identifier of the newly created buffer or INVALID_VERTEX_BUFFER if something went wrong
	     */
	    virtual VertexBufferId genVertexBuffer(BufferType type, unsigned int size, const void* data) = 0;
	    /**
	     * @brief Deletes a vertex buffer
	     * @param id ID of the buffer to delete
	     */
	    virtual void delVertexBuffer(VertexBufferId id) = 0;
	    /**
	     * @brief Sends data to a buffer
	     * @param id Identifier of the buffer
	     * @param type Buffer type
	     * @param size Size of the buffer
	     * @param data Data to send to the buffer
	     */
	    virtual void fillVertexBuffer(VertexBufferId id, BufferType type, unsigned int size, const void* data) = 0;
	    /**
	     * @brief Generates a vertex buffer
	     * @param size Size of the buffer to create
	     * @param type Buffer type
	     * @param data Data to initialize the buffer with
	     * @return Identifier of the newly created buffer or INVALID_INDEX_BUFFER if something went wrong
	     */
	    virtual IndexBufferId genIndexBuffer(BufferType type, unsigned int size, const void* data) = 0;
	    /**
	     * @brief Deletes an index buffer
	     * @param id ID of the buffer to delete
	     */
	    virtual void delIndexBuffer(IndexBufferId id) = 0;
	    /**
	     * @brief Sends data to a buffer
	     * @param id Identifier of the buffer
	     * @param type Buffer type
	     * @param size Size of the buffer
	     * @param data Data to send to the buffer
	     */
	    virtual void fillIndexBuffer(IndexBufferId id, BufferType type, unsigned int size, const void* data) = 0;
	    /**
	     * @brief Registers a new vertex format
	     * @param id Attribute ID
	     * @param size Amount of attributes to pass
	     * @param format Attribute format
	     * @param offset Offset
	     * @return Identifier of the newly registered vertex format
	     */
	    virtual VertexFormatId regVertexFormat(AttribId id, unsigned int size, AttribFormat format) = 0;
	    /**
	     * @brief Initializes a vertex buffer to be used on the next draw call
	     * @param vertBuffer Identifier of the vertex buffer to use
	     * @param vertFormat Vertex format to use
	     */
	    virtual void useVertexBuffer(VertexBufferId vertBuffer, VertexFormatId vertFormat) = 0;
	    /**
	     * @brief Ends the usage of a certain vertex buffer
	     * @param vertBuffer Identifier of the vertex buffer to end usage
	     */
	    virtual void endUseVertexBuffer(VertexBufferId vertBuffer, VertexFormatId vertFormat) = 0;
	    /**
	     * @brief Initializes a index buffer to be used on the next draw call
	     * @param vertBuffer Identifier of the index buffer to use
	     */
	    virtual void useIndexBuffer(IndexBufferId indexBuffer) = 0;
	    /**
	     * @brief Ends the usage of a certain index buffer
	     * @param vertBuffer Identifier of the index buffer to end usage
	     */
	    virtual void endUseIndexBuffer(IndexBufferId indexBuffer) = 0;
	    /**
	     * @brief Draws elements using the currently used index- and vertex buffers
	     * @param mode Primitive format used
	     */
	    virtual void drawElements(PolygonMode mode, unsigned int size, AttribFormat format) = 0;
	    /**
	     * @brief Changes the viewport to a new resolution
	     * @param width New viewport width
	     * @param height New viewport height
	     */
	    virtual void changeViewport(unsigned int width, unsigned int height) = 0;
	    /**
	     * @brief Generates a texture and binds it to the graphics memory
	     * @param width Texture width
	     * @param height Texture height
	     * @param data Actual data in a contiguous block of memory
	     * @param level Amount of mip levels
	     * @param texFormat Texture format
	     * @param format Format of each pixel
	     * @return ID of the generated texture
	     */
	    virtual TextureBuffer2dId genTextureBuffer2d(unsigned int width, unsigned int height, const void* data,
		    unsigned int level, TextureFormat texFormat, AttribFormat format) = 0;
	    /**
	     * @brief Removes the texture with ID \p id from the graphics memory
	     * @param id ID of the texture to remove
	     */
	    virtual void delTextureBuffer2d(TextureBuffer2dId id) = 0;
	    /**
	     * @brief Binds a new texture to an already created buffer
	     * @param id Texture buffer ID
	     * @param width Texture width
	     * @param height Texture height
	     * @param data Actual data in a contiguous block of memory
	     * @param level Amount of mip levels
	     * @param texFormat Texture format
	     * @param format Format of each pixel
	     */
	    virtual void fillTextureBuffer2d(TextureBuffer2dId id, unsigned int width, unsigned int height,
		    const void* data, unsigned int level, TextureFormat texFormat, AttribFormat format) = 0;
    };
}

#endif /* ABSTRACTRENDERER_H_ */
