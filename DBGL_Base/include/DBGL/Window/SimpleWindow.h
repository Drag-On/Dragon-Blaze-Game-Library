//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SIMPLEWINDOW_H_
#define SIMPLEWINDOW_H_

#include <memory>
#include "Window.h"
#include "DBGL/Rendering/Sprite/BitmapFont.h"
#include "DBGL/Rendering/ShaderProgram.h"

namespace dbgl
{
    /**
     * @brief Simple default window with often used properties
     */
    class SimpleWindow: public Window
    {
	public:
	    /**
	     * @brief Frees all memory allocated to this window
	     */
	    ~SimpleWindow();
	    /**
	     * @brief Checks if fps are currently being shown
	     * @return True in case fps are currently shown, otherwise false
	     */
	    bool getShowFps() const;
	    /**
	     * @brief Determines is fps should be shown
	     * @param showFps True if fps should be shown, otherwise false
	     */
	    void setShowFps(bool showFps);

	protected:
	    /**
	     * @brief Creates a simple window
	     * @param share Other window to share resources with
	     * @param title Window title
	     * @param width Window width
	     * @param height Window height
	     * @param multisampling Multisampling level (0 to disable)
	     * @param fullscreen Indicates if the window should be initialized as fullscreen
	     */
	    SimpleWindow(GLFWwindow* share, const char* title = "Dragon Blaze Game Library",
		    int width = 800, int height = 600, bool fullscreen = false, unsigned int multisampling = 2);
	    /**
	     * @brief Called on key events.
	     * @param args Key event arguments
	     */
	    void keyCallback(KeyEventArgs args);
	    /**
	     * @brief Gets called once a frame and should render everything
	     */
	    virtual void render();
	    /**
	     * @brief Gets called once a frame after @see update
	     */
	    virtual void postRender();

	private:
	    bool m_takeScreenshot = false;
	    bool m_showFps = true;
	    BitmapFont m_defaultFont{"../common/DefaultFont.bff"};
	    float m_fps = 0.0f;

	    static std::shared_ptr<ShaderProgram> spriteShader;

	    friend class WindowManager;
    };
}

#endif /* SIMPLEWINDOW_H_ */
