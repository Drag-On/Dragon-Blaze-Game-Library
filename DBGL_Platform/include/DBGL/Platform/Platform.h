//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <string>
#include "DBGL/Platform/Window/IWindow.h"
#include "DBGL/Platform/Monitor/IMonitor.h"
#include "DBGL/Platform/Time/ITimer.h"
#include "DBGL/Platform/Shader/IShader.h"
#include "DBGL/Platform/Shader/IShaderProgram.h"
#include "DBGL/Platform/Shader/IShaderProgramCommands.h"
#include "DBGL/Platform/Texture/ITexture.h"

namespace dbgl
{
	/**
	 * @brief Static main platform class
	 * @details Initilizes a platform implementation and provides access to it
	 */
	class Platform
	{
	public:
		/**
		 * @brief Interface class for platform implementations. Serves as factory for platform components.
		 */
		class IImplementation
		{
		public:
			/**
			 * @brief Destructor
			 */
			virtual ~IImplementation() = default;
			/**
			 * @brief Creates a new window
			 * @param title Window title
			 * @param width Initial window width
			 * @param height Initial window height
			 * @param fullscreen Flag determining if the window will be created fullscreen
			 * @param multisampling Amount of multisampling
			 * @return Pointer to the created window
			 * @note The created object needs to be deleted manually
			 */
			virtual IWindow* createWindow(std::string title = "Dragon Blaze Game Library", int width = 800, int height =
					600, bool fullscreen = false, unsigned int multisampling = 2) = 0;
			/**
			 * @brief Creates a monitor object
			 * @return Pointer to the created monitor object
			 * @note The created object needs to be deleted manually
			 */
			virtual IMonitor* createMonitor() = 0;
			/**
			 * @brief Creates a timer object
			 * @return Pointer to the created timer object
			 * @note The created object needs to be deleted manually
			 */
			virtual ITimer* createTimer() = 0;
			/**
			 * @brief Creates a shader object
			 * @param type Shader type
			 * @param code code of the shader
			 * @return Pointer to the created shader object
			 * @note The created object needs to be deleted manually
			 */
			virtual IShader* createShader(IShader::Type type, std::string code) = 0;
			/**
			 * @brief Creates a shader program
			 * @return Pointer to the created shader program
			 * @note The created object needs to be deleted manually
			 */
			virtual IShaderProgram* createShaderProgram() = 0;
			/**
			 * @brief Creates an empty texture
			 * @param type Texture type
			 * @return Pointer to the created texture object
			 * @note The created object needs to be deleted manually
			 */
			virtual ITexture* createTexture(ITexture::Type type) = 0;
			/**
			 * @brief Creates an empty mesh
			 * @return Pointer to the created mesh object
			 * @note The created object needs to be deleted manually
			 */
			virtual IMesh* createMesh() = 0;
			/**
			 * @brief Creates a render context that can be used to draw onto textures
			 * @param tex Texture to draw onto
			 * @param createDepthBuf Flag indicating if a depth buffer is needed
			 * @return Pointer to the created render context
			 * @note The created object needs to be deleted manually
			 */
			virtual IRenderContext* createRenderContext(ITexture* tex, bool createDepthBuf = false) = 0;
			/**
			 * @brief Provides functionality to operate on the currently in-use shader program
			 * @return A pointer to the currently in-use shader program
			 */
			virtual IShaderProgramCommands* curShaderProgram() = 0;
		};

		/**
		 * @brief Initializes the specified platform implementation
		 */
		template<class Type> static void init();
		/**
		 * @brief Destroy the currently active platform implementation
		 */
		static void destroy();
		/**
		 * @brief Provides a pointer to the currently initialized platform implementation
		 * @return Pointer to platform implementation or nullptr if init() hasn't been called yet
		 */
		static IImplementation* get();

	private:
		static IImplementation* s_pType;
	};
}

#include "Platform.imp"

#endif /* PLATFORM_H_ */
