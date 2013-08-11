/*
 * Input.h
 *
 *  Created on: 08.08.2013
 *      Author: Drag-On
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include <tr1/functional>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "../Main/Log.h"

#define AMOUNTOFKEYS 107

namespace DBGL
{

/**
 * @brief Defines constants for all accessible keys
 */
enum KEY
{
	NONE,			//!< NONE
	MOUSE_LEFT,     //!< MOUSE_LEFT
	MOUSE_MIDDLE,   //!< MOUSE_MIDDLE
	MOUSE_RIGHT,    //!< MOUSE_RIGHT
	KEY_ENTER,      //!< KEY_ENTER
	KEY_SPACE,      //!< KEY_SPACE
	KEY_BACKSPACE,  //!< KEY_BACKSPACE
	KEY_ESCAPE,     //!< KEY_ESCAPE
	KEY_UP,         //!< KEY_UP
	KEY_LEFT,       //!< KEY_LEFT
	KEY_DOWN,       //!< KEY_DOWN
	KEY_RIGHT,      //!< KEY_RIGHT
	KEY_PAGEUP,     //!< KEY_PAGEUP
	KEY_PAGEDOWN,   //!< KEY_PAGEDOWN
	KEY_HOME,       //!< KEY_HOME
	KEY_END,        //!< KEY_END
	KEY_INSERT,     //!< KEY_INSERT
	KEY_DELETE,     //!< KEY_DELETE
	KEY_ADD,        //!< KEY_ADD
	KEY_MINUS,      //!< KEY_MINUS
	KEY_EQUALS,     //!< KEY_EQUALS
	KEY_TAB,        //!< KEY_TAB
	KEY_LBRACKET,   //!< KEY_LBRACKET
	KEY_RBRACKET,   //!< KEY_RBRACKET
	KEY_LCONTROL,   //!< KEY_LCONTROL
	KEY_RCONTROL,   //!< KEY_RCONTROL
	KEY_SEMICOLON,  //!< KEY_SEMICOLON
	KEY_APOSTROPHE, //!< KEY_APOSTROPHE
	KEY_GRAVE,      //!< KEY_GRAVE
	KEY_LSHIFT,     //!< KEY_LSHIFT
	KEY_RSHIFT,     //!< KEY_RSHIFT
	KEY_BACKSLASH,  //!< KEY_BACKSLASH
	KEY_COMMA,      //!< KEY_COMMA
	KEY_PERIOD,     //!< KEY_PERIOD
	KEY_SLASH,      //!< KEY_SLASH
	KEY_LALT,       //!< KEY_LALT
	KEY_RALT,       //!< KEY_RALT
	KEY_CAPITAL,    //!< KEY_CAPITAL
	KEY_SCROLLLOCK, //!< KEY_SCROLLLOCK
	KEY_SYSRQ,      //!< KEY_SYSRQ
	KEY_PAUSE,      //!< KEY_PAUSE
	KEY_LWIN,       //!< KEY_LWIN
	KEY_RWIN,       //!< KEY_RWIN
	KEY_NUM1,       //!< KEY_NUM1
	KEY_NUM2,       //!< KEY_NUM2
	KEY_NUM3,       //!< KEY_NUM3
	KEY_NUM4,       //!< KEY_NUM4
	KEY_NUM5,       //!< KEY_NUM5
	KEY_NUM6,       //!< KEY_NUM6
	KEY_NUM7,       //!< KEY_NUM7
	KEY_NUM8,       //!< KEY_NUM8
	KEY_NUM9,       //!< KEY_NUM9
	KEY_NUM0,       //!< KEY_NUM0
	KEY_NUMENTER,   //!< KEY_NUMENTER
	KEY_NUMCOMMA,   //!< KEY_NUMCOMMA
	KEY_NUMADD,     //!< KEY_NUMADD
	KEY_NUMSUBTRACT,     //!< KEY_NUMSUBTRACT
	KEY_NUMMULTIPLY,     //!< KEY_NUMMULTIPLY
	KEY_NUMDIVIDE,  //!< KEY_NUMDIVIDE
	KEY_NUMDECIMAL,	//!< KEY_NUMDECIMAL
	KEY_NUMLOCK,    //!< KEY_NUMLOCK
	KEY_F1,         //!< KEY_F1
	KEY_F2,         //!< KEY_F2
	KEY_F3,         //!< KEY_F3
	KEY_F4,         //!< KEY_F4
	KEY_F5,         //!< KEY_F5
	KEY_F6,         //!< KEY_F6
	KEY_F7,         //!< KEY_F7
	KEY_F8,         //!< KEY_F8
	KEY_F9,         //!< KEY_F9
	KEY_F10,        //!< KEY_F10
	KEY_F11,        //!< KEY_F11
	KEY_F12,        //!< KEY_F12
	KEY_A,          //!< KEY_A
	KEY_B,          //!< KEY_B
	KEY_C,          //!< KEY_C
	KEY_D,          //!< KEY_D
	KEY_E,          //!< KEY_E
	KEY_F,          //!< KEY_F
	KEY_G,          //!< KEY_G
	KEY_H,          //!< KEY_H
	KEY_I,          //!< KEY_I
	KEY_J,          //!< KEY_J
	KEY_K,          //!< KEY_K
	KEY_L,          //!< KEY_L
	KEY_M,          //!< KEY_M
	KEY_N,          //!< KEY_N
	KEY_O,          //!< KEY_O
	KEY_P,          //!< KEY_P
	KEY_Q,          //!< KEY_Q
	KEY_R,          //!< KEY_R
	KEY_S,          //!< KEY_S
	KEY_T,          //!< KEY_T
	KEY_U,          //!< KEY_U
	KEY_V,          //!< KEY_V
	KEY_W,          //!< KEY_W
	KEY_X,          //!< KEY_X
	KEY_Y,          //!< KEY_Y
	KEY_Z,          //!< KEY_Z
	KEY_1,          //!< KEY_1
	KEY_2,          //!< KEY_2
	KEY_3,          //!< KEY_3
	KEY_4,          //!< KEY_4
	KEY_5,          //!< KEY_5
	KEY_6,          //!< KEY_6
	KEY_7,          //!< KEY_7
	KEY_8,          //!< KEY_8
	KEY_9,          //!< KEY_9
	KEY_0,          //!< KEY_0
};

/**
 * @brief This class handles the input a window receives
 */
class Input
{
	// The window needs to pass input from glut to this class
	friend class BaseGameWindow;

	/**
	 * @brief State a key can have
	 */
	enum KEYSTATE
	{
		PRESSED,	// Key was previously up and is now down
		DOWN,		// Key is currently pressed down
		RELEASED,	// Key was previously down and is now up
		UP,			// Key is currently not pressed
	};

	// Typedef for input callbacks
	typedef std::tr1::function<void(KEY, char)> inputCallback;
	typedef std::tr1::function<void(int, int, int, int)> dragCallback;
	typedef std::tr1::function<void(int, int, int)> mouseWheelCallback;

public:
	/**
	 * Constructor
	 */
	Input();

	/**
	 * Destructor
	 */
	virtual ~Input();

	/**
	 * @brief Checks, if a key is currently held down
	 * @param key Key to check
	 * @return true in case the key is pressed, otherwise false
	 */
	bool isDown(KEY key);

	/**
	 * @brief Checks, if a key is currently not pressed
	 * @param key Key to check
	 * @return true in case the key is not pressed, otherwise false
	 */
	bool isUp(KEY key);

	/**
	 * @brief Checks if a key was just pressed down
	 * @param key Key to check
	 * @return true in case the key was toggled, otherwise false
	 */
	bool isPressed(KEY key);

	/**
	 * @brief Checks if a key was just released
	 * @param key Key to check
	 * @return true in case the key was toggled, otherwise false
	 */
	bool isReleased(KEY key);

	/**
	 * @brief Sets the callback function for key press events
	 * @param callback Function to call
	 */
	void setKeyPressedCallback(inputCallback callback);

	/**
	 * @brief Sets the callback function for key release events
	 * @param callback Function to call
	 */
	void setKeyReleasedCallback(inputCallback callback);

	/**
	 * @brief Sets the callback function for mouse drag events
	 * @param callback Function to call
	 */
	void setMouseDragCallback(dragCallback callback);

	/**
	 * @brief Sets the callback function for mouse wheel events
	 * @param callback Function to set
	 */
	void setMouseWheelCallback(mouseWheelCallback callback);

private:
	std::map<KEY, KEYSTATE>* _pKeys; // Map of all keys and their states
	int _mouseX; // Current mouse x coordinate
	int _mouseY; // Current mouse y coordinate
	int _lastMouseX; // Last mouse x coordinate
	int _lastMouseY; // Last mouse y coordinate

	// Callback functions
	inputCallback _keyPressedCallback;
	inputCallback _keyReleasedCallback;
	dragCallback _dragCallback;
	mouseWheelCallback _mouseWheelCallback;

	/**
	 * @brief Called on every keyboard input
	 * @param key Key that got pressed
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	void onKeyInput(unsigned char key, int x, int y);

	/**
	 * @brief Called once a special key on the keyboard got pressed
	 * @param key Special key that got pressed
	 * @param x X mouse coordinate
	 * @param y Y mouse coordinate
	 */
	void onSpecialKeyInput(int key, int x, int y);

	/**
	 * @brief Called once a key was released
	 * @param key Key that has been released
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	void onKeyInputUp(unsigned char key, int x, int y);

	/**
	 * @brief Called once a special key was released
	 * @param key Key that has been released
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	void onSpecialKeyUp(int key, int x, int y);

	/**
	 * @brief Called on every mouse input
	 * @param button Mouse button that changed state
	 * @param state New state of the button
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	void onMouseInput(int button, int state, int x, int y);

	/**
	 * @brief Called when the mouse got moved with a mouse button pressed down
	 * @param x X mouse coordinate
	 * @param y Y mouse coordinate
	 */
	void onMouseDrag(int x, int y);

	/**
	 * @brief Called when the mouse got moved
	 * @param x X mouse coordinate
	 * @param y Y mouse coordinate
	 */
	void onMouseMove(int x, int y);

	/**
	 * @brief Called once the mouse wheel changed
	 * @param button Mouse button
	 * @param dir Direction of scroll wheel
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	void onMouseWheel(int button, int dir, int x, int y);

	/**
	 * Update the input handler
	 */
	void update();

	/**
	 * @brief Translates a character into the right KEY constant
	 * @param key Character to translate
	 * @return The KEY constant corresponding to the character
	 */
	KEY translateCharToKey(unsigned char key);

	/**
	 * @brief Translates a key code into the right KEY constant
	 * @param key Integer to translate
	 * @return The KEY constant corresponding to the code
	 */
	KEY translateKeyCodeToKey(int key);
};

} /* namespace DBGL */
#endif /* INPUT_H_ */
