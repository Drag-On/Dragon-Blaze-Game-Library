//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IGL_H_
#define IGL_H_

#include <string>
#include <iostream>
#include <functional>
#include <GL/glew.h> // TODO: DEBUG!
#include "HandleGenerator.h"
#include "Input.h"

namespace dbgl
{

    class IGL
    {
	public:
	    /**
	     * @brief Type of handles used for windows
	     */
	    using WindowHandle = HandleGenerator::Handle;
	    /**
	     * @brief Constant for invalid window handles
	     */
	    static constexpr WindowHandle InvalidWindowHandle = HandleGenerator::InvalidHandle;

	    /**
	     * @brief Function type for error callback
	     */
	    using WndErrorCallback = std::function<void(int,const char*)>;
	    /**
	     * @brief Function type for close callback
	     */
	    using WndCloseCallback = std::function<void(WindowHandle)>;
	    /**
	     * @brief Function type for focus callback
	     */
	    using WndFocusCallback = std::function<void(WindowHandle,int)>;
	    /**
	     * @brief Function type for iconified callback
	     */
	    using WndIconifiedCallback = std::function<void(WindowHandle,int)>;
	    /**
	     * @brief Function type for resize callback
	     */
	    using WndResizeCallback = std::function<void(WindowHandle,int,int)>;
	    /**
	     * @brief Function type for framebuffer resize callback
	     */
	    using WndFramebufferResizeCallback = std::function<void(WindowHandle,int,int)>;
	    /**
	     * @brief Function type for window position callback
	     */
	    using WndPositionCallback = std::function<void(WindowHandle,int,int)>;
	    /**
	     * @brief Function type for cursor enter callback
	     */
	    using WndCursorEnterCallback = std::function<void(WindowHandle,int)>;
	    /**
	     * @brief Function type for cursor movement callback
	     */
	    using WndCursorPositionCallback = std::function<void(WindowHandle,double,double)>;
	    /**
	     * @brief Function type for scroll callback
	     */
	    using WndScrollCallback = std::function<void(WindowHandle,double,double)>;
	    /**
	     * @brief Function type for general input callback
	     */
	    using WndInputCallback = std::function<void(WindowHandle,Input::Key,Input const&)>;

	protected:
	    /**
	     * @brief Base struct for texture handles
	     */
	    struct TextureHandleInternal
	    {
		public:
		    virtual ~TextureHandleInternal() = default;
		    GLuint m_handle; // TODO: DEBUG!
	    };
	public:
	    /**
	     * @brief Type of handles used for textures
	     */
	    using TextureHandle = TextureHandleInternal*;
	    /**
	     * @brief Constant for invalid window handles
	     */
	    static constexpr TextureHandle InvalidTextureHandle = nullptr;
	    /**
	     * @brief Lists all supported texture types
	     */
	    enum class TextureType : char
	    {
		TEX2D,//!< TEX2D
	    };
	    /**
	     * @brief Lists all supported uncompressed pixel formats
	     */
	    enum class PixelFormat : char
	    {
		RGB, 	  //!< RGB
		BGR, 	  //!< BGR
		RGBA,	  //!< RGBA
		BGRA,	  //!< BGRA
	    };
	    /**
	     * @brief Lists all supported compressed pixel formats
	     */
	    enum class PixelFormatCompressed : char
	    {
		COMP_DXT1,//!< COMP_DXT1
		COMP_DXT3,//!< COMP_DXT3
		COMP_DXT5,//!< COMP_DXT5
	    };
	    /**
	     * @brief Lists all supported pixel types
	     */
	    enum class PixelType : char
	    {
		UBYTE, //!< UBYTE
		BYTE,  //!< BYTE
		USHORT,//!< USHORT
		SHORT, //!< SHORT
		UINT,  //!< UINT
		INT,   //!< INT
		FLOAT, //!< FLOAT
	    };
	    /**
	     * @brief Lists all supported row alignment types
	     */
	    enum class RowAlignment : char
	    {
		PACK,  //!< PACK
		UNPACK,//!< UNPACK
	    };
	    /**
	     * @brief Lists all supported minifying filters
	     */
	    enum class MinFilter : char
	    {
		NEAREST,               //!< NEAREST
		LINEAR,                //!< LINEAR
		NEAREST_MIPMAP_NEAREST,//!< NEAREST_MIPMAP_NEAREST
		NEAREST_MIPMAP_LINEAR, //!< NEAREST_MIPMAP_LINEAR
		LINEAR_MIPMAP_NEAREST, //!< LINEAR_MIPMAP_NEAREST
		LINEAR_MIPMAP_LINEAR,  //!< LINEAR_MIPMAP_LINEAR
	    };
	    /**
	     * @brief Lists all supported magnifying filters
	     */
	    enum class MagFilter : char
	    {
		NEAREST,//!< NEAREST
		LINEAR, //!< LINEAR
	    };

	    /**
	     * @brief Virtual destructor
	     */
	    virtual ~IGL() = default;
	    /**
	     * @brief Retrieves the resolution of the main screen
	     * @param[out] width Screen width
	     * @param[out] height Screen height
	     */
	    virtual void getScreenResolution(int& width, int& height) = 0;
	    /**
	     * @brief Initializes a window
	     * @param title Window title
	     * @param width Window width
	     * @param height Window height
	     * @param fullscreen Specifies if fullscreen
	     * @return Handle to the newly created window
	     */
	    virtual WindowHandle wndInit(std::string title = "Dragon-Blaze-Game-Library", unsigned int width =
		    800, unsigned int height = 600, bool fullscreen = false,
		    unsigned int multisampling = 0) = 0;
	    /**
	     * @brief Terminates the window system and closes all open windows
	     */
	    virtual void wndTerminate() = 0;
	    /**
	     * @brief Show a window
	     * @param wnd Window to show
	     */
	    virtual void wndShow(WindowHandle wnd) = 0;
	    /**
	     * @brief Hide a window
	     * @param wnd Window to hide
	     */
	    virtual void wndHide(WindowHandle wnd) = 0;
	    /**
	     * @brief Closes a window
	     * @param wnd Window to close
	     */
	    virtual void wndClose(WindowHandle wnd) = 0;
	    /**
	     * @brief Destroys a window without calling any events
	     * @param wnd Window to destroy
	     */
	    virtual void wndDestroy(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is in focus
	     * @param wnd Window to check
	     * @return True in case the window is in focus, otherwise false
	     */
	    virtual bool wndCheckFocus(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is iconified
	     * @param wnd Window to check
	     * @return True in case the window is iconified, otherwise false
	     */
	    virtual bool wndCheckIconified(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is visible
	     * @param wnd Window to check
	     * @return True in case the window is visible, otherwise false
	     */
	    virtual bool wndCheckVisible(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is resizable
	     * @param wnd Window to check
	     * @return True in case the window is resizable, otherwise false
	     */
	    virtual bool wndCheckResizable(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window has decorations
	     * @param wnd Window to check
	     * @return True in case the window has decorations, otherwise false
	     */
	    virtual bool wndCheckDecorations(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is about to be closed
	     * @param wnd Window to check
	     * @return True in case the window is about to be closed, otherwise false
	     */
	    virtual bool wndCheckClose(WindowHandle wnd) = 0;
	    /**
	     * @brief Modifies the title of a window
	     * @param wnd Window to set title for
	     * @param title New title
	     */
	    virtual void wndSetTitle(WindowHandle wnd, std::string const& title) = 0;
	    /**
	     * @brief Retrieves the size of a window
	     * @param wnd Window to get width from
	     * @param[out] width The window's width
	     * @param[out] height The window's height
	     */
	    virtual void wndGetSize(WindowHandle wnd, int& width, int& height) = 0;
	    /**
	     * @brief Modifies the size of a window
	     * @param wnd Window to modify
	     * @param width New width
	     * @param height New height
	     */
	    virtual void wndSetSize(WindowHandle wnd, int width, int height) = 0;
	    /**
	     * @brief Retrieves the frame size of a window
	     * @param wnd Window to get frame size from
	     * @param[out] width Frame width
	     * @param[out] height Frame height
	     */
	    virtual void wndGetFrameSize(WindowHandle wnd, int& width, int& height) = 0;
	    /**
	     * @brief Retrieves the coordinates of a window
	     * @param wnd Window to get coordinates from
	     * @param[out] x X coordinate
	     * @param[out] y Y coordinate
	     */
	    virtual void wndGetPos(WindowHandle wnd, int& x, int& y) = 0;
	    /**
	     * @brief Modifies the coordinates of a window
	     * @param wnd Window to modify
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    virtual void wndSetPos(WindowHandle wnd, int x, int y) = 0;
	    /**
	     * @brief Makes a window current
	     * @param wnd Window to make current
	     */
	    virtual void wndMakeCurrent(WindowHandle wnd) = 0;
	    /**
	     * @brief Retrieves the current cursor coordinates within a window
	     * @param wnd Window to check
	     * @param x[out] X coordinate
	     * @param y[out] Y coordinate
	     */
	    virtual void wndGetCursorPos(WindowHandle wnd, double& x, double& y) = 0;
	    /**
	     * @brief Modifies the cursor coordinates within a window
	     * @param wnd Window to modify
	     * @param x[in] New x coordinate
	     * @param y[in] New y coordinate
	     */
	    virtual void wndSetCursorPos(WindowHandle wnd, double x, double y) = 0;
	    /**
	     * @brief Retrieves input from a window
	     * @param wnd Wnd to check input from
	     * @return Reference to input object
	     */
	    virtual Input& wndGetInput(WindowHandle wnd) = 0;
	    /**
	     * @brief Swaps the render buffers of a window
	     * @param wnd Window to modify
	     */
	    virtual void wndSwapBuffers(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks for new events in all windows and returns
	     */
	    virtual void wndPollEvents() = 0;
	    /**
	     * @brief Provides the time since initialization of the window system in seconds (but in a much better resolution)
	     * @return Time since startup
	     */
	    virtual double wndGetTime() = 0;
	    /**
	     * @brief Set a callback to call on errors regarding windows
	     * @param callback Callback function
	     */
	    virtual void wndSetErrorCallback(WndErrorCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window is closed
	     * @param wnd Wnd to set the callback for
	     * @param callback Callback function to call on close events
	     */
	    virtual void wndSetCloseCallback(WindowHandle wnd, WndCloseCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window is focused or unfocused
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetFocusCallback(WindowHandle wnd, WndFocusCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window is iconified or deconified
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetIconifiedCallback(WindowHandle wnd, WndIconifiedCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window is resized
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetResizeCallback(WindowHandle wnd, WndResizeCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window's framebuffer is resized
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetFramebufferResizeCallback(WindowHandle wnd, WndFramebufferResizeCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window is moved
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetPositionCallback(WindowHandle wnd, WndPositionCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a cursor enters a window
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetCursorEnterCallback(WindowHandle wnd, WndCursorEnterCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a cursor within a window has been moved
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetCursorPositionCallback(WindowHandle wnd, WndCursorPositionCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a scroll wheel within a window has been used
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetScrollCallback(WindowHandle wnd, WndScrollCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window receives some kind of input
	     * @param wnd Window to set callback for
	     * @param callback Callback function
	     */
	    virtual void wndSetInputCallback(WindowHandle wnd, WndInputCallback callback) = 0;
	    /**
	     * @brief Generates a new texture
	     * @param type Type of texture to generate
	     * @return Handle of the generated texture
	     */
	    virtual TextureHandle texGenerate(TextureType type) = 0;
	    /**
	     * @brief Deletes a texture
	     * @param handle Handle of the texture
	     */
	    virtual void texDelete(TextureHandle handle) = 0;
	    /**
	     * @brief Bind a texture
	     * @param handle Texture to bind
	     */
	    virtual void texBind(TextureHandle handle) = 0;
	    /**
	     * @brief Fills the currently bound, previously generated texture buffer
	     * @param level MipMap level to write
	     * @param width Image width
	     * @param height Image height
	     * @param format Pixel format
	     * @param type Pixel type
	     * @param data Pointer to image data
	     */
	    virtual void texWrite(unsigned int level, unsigned int width,
		    unsigned int height, PixelFormat format, PixelType type, void* data) = 0;
	    /**
	     * @brief Fills the currently bound, previously generated texture buffer with compressed data
	     * @param level Mip map level to write
	     * @param width Image width
	     * @param height Image height
	     * @param format Compressed pixel format
	     * @param size Size of the passed image data
	     * @param data Pointer to image data
	     */
	    virtual void texWriteCompressed(unsigned int level, unsigned int width, unsigned int height,
		    PixelFormatCompressed format, unsigned int size, void* data) = 0;
	    /**
	     * @brief Modifies the row alignment used when transfering image data
	     * @param type Alignment type
	     * @param align Alignment to set
	     */
	    virtual void texSetRowAlignment(RowAlignment type, unsigned int align) = 0;
	    /**
	     * @brief Sets the filter used to minify the currently bound texture
	     * @param filter New filter
	     */
	    virtual void texSetMinFilter(MinFilter filter) = 0;
	    /**
	     * @brief Sets the filter used to magnify the currently bound texture
	     * @param filter New filter
	     */
	    virtual void texSetMagFilter(MagFilter filter) = 0;
	    /**
	     * @brief Generates mip maps for the currently bound texture.
	     * @details Overwrites any previously set mip maps
	     */
	    virtual void texGenerateMipMaps() = 0;
	    /**
	     * @brief Retrieves the size of the currently bound texture (or a mip map of this texture)
	     * @param[out] width Texture width will be copied here
	     * @param[out] height Texture height will be copied here
	     * @param level Mip level, defaults to 0
	     */
	    virtual void texGetSize(unsigned int& width, unsigned int& height, unsigned int level = 0) = 0;

	protected:
	    /**
	     * @brief Constructor
	     */
	    IGL();
	    /**
	     * @brief Checks if a pixel format supports alpha values
	     * @param format Format to check
	     * @return True in case alpha is supported, otherwise false
	     */
	    bool hasAlpha(PixelFormat format);
	private:
	    IGL(IGL const&); // Disallow copying
	    IGL& operator=(IGL const& other);
    };
}

#endif /* IGL_H_ */
