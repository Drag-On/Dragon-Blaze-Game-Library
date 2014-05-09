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

namespace dbgl
{
    class AbstractRenderer
    {
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
	    IndexBufferId INVALID_INDEX_BUFFER = std::numeric_limits<IndexBufferId>::max();
	    /**
	     * @brief Value for specifying an invalid vertex buffer
	     */
	    VertexBufferId INVALID_VERTEX_BUFFER = std::numeric_limits<VertexBufferId>::max();

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
		FLOAT,//!< FLOAT
		HALF, //!< HALF
		UBYTE,//!< UBYTE
	    };
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
	private:
	    struct VertexFormat
	    {
		unsigned int id;
		unsigned int amount;
		AttribFormat format;
	    };
	    struct IndexBuffer
	    {
		unsigned int id;
		unsigned int size;
	    };
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~AbstractRenderer() = 0;
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
	     * @brief Initializes a vertex buffer to be used on the next draw call
	     * @param vertBuffer Identifier of the vertex buffer to use
	     */
	    virtual void useVertexBuffer(VertexBufferId vertBuffer) = 0;
	    /**
	     * @brief Ends the usage of a certain vertex buffer
	     * @param vertBuffer Identifier of the vertex buffer to end usage
	     */
	    virtual void endUseVertexBuffer(VertexBufferId vertBuffer) = 0;
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
	    virtual void drawElements(PolygonMode mode) = 0;
    };
}

#endif /* ABSTRACTRENDERER_H_ */
