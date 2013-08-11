/*
 * Input.cpp
 *
 *  Created on: 08.08.2013
 *      Author: Drag-On
 */

#include "Input.h"

namespace DBGL
{

/**
 * Constructor
 */
Input::Input()
{
	_pKeys = new std::map<KEY, KEYSTATE>();

	_mouseX = _mouseY = _lastMouseX = _lastMouseY = 0;

	// Initialize all keys as UP
	for (int i = 0; i < AMOUNTOFKEYS; i++)
	{
		std::pair<KEY, KEYSTATE> pair = std::make_pair(KEY(i), UP);
		_pKeys->insert(pair);
	}
}

/**
 * Destructor
 */
Input::~Input()
{
	delete _pKeys;
	_pKeys = NULL;
}

/**
 * @brief Checks, if a key is currently held down
 * @param key Key to check
 * @return true in case the key is pressed, otherwise false
 */
bool Input::isDown(KEY key)
{
	std::map<KEY, KEYSTATE>::iterator iter;
	iter = _pKeys->find(key);
	return iter != _pKeys->end()
			&& (iter->second == DOWN || iter->second == PRESSED);
}

/**
 * @brief Checks, if a key is currently not pressed
 * @param key Key to check
 * @return true in case the key is not pressed, otherwise false
 */
bool Input::isUp(KEY key)
{
	std::map<KEY, KEYSTATE>::iterator iter;
	iter = _pKeys->find(key);
	return iter == _pKeys->end() || iter->second == UP
			|| iter->second == RELEASED;
}

/**
 * brief Checks if a key was just pressed down and is now up again
 * @param key Key to check
 * @return true in case the key was toggled, otherwise false
 */
bool Input::isPressed(KEY key)
{
	std::map<KEY, KEYSTATE>::iterator iter;
	iter = _pKeys->find(key);
	return iter != _pKeys->end() && iter->second == PRESSED;
}

/**
 * @brief Checks if a key was just released
 * @param key Key to check
 * @return true in case the key was toggled, otherwise false
 */
bool Input::isReleased(KEY key)
{
	std::map<KEY, KEYSTATE>::iterator iter;
	iter = _pKeys->find(key);
	return iter != _pKeys->end() && iter->second == RELEASED;
}

/**
 * @brief Sets the callback function for key press events
 * @param callback Function to call
 */
void Input::setKeyPressedCallback(inputCallback callback)
{
	_keyPressedCallback = callback;
}

/**
 * @brief Sets the callback function for key release events
 * @param callback Function to call
 */
void Input::setKeyReleasedCallback(inputCallback callback)
{
	_keyReleasedCallback = callback;
}

/**
 * @brief Sets the callback function for mouse drag events
 * @param callback Function to call
 */
void Input::setMouseDragCallback(dragCallback callback)
{
	_dragCallback = callback;
}

/**
 * @brief Sets the callback function for mouse wheel events
 * @param callback Function to set
 */
void Input::setMouseWheelCallback(mouseWheelCallback callback)
{
	_mouseWheelCallback = callback;
}

/**
 * @brief Translates a character into the right KEY constant
 * @param key Character to translate
 * @return The KEY constant corresponding to the character
 */
KEY Input::translateCharToKey(unsigned char key)
{
	switch (key)
	{
	case 'a':
	case 'A':
		return (KEY_A);
	case 'b':
	case 'B':
		return (KEY_B);
	case 'c':
	case 'C':
		return (KEY_C);
	case 'd':
	case 'D':
		return (KEY_D);
	case 'e':
	case 'E':
		return (KEY_E);
	case 'f':
	case 'F':
		return (KEY_F);
	case 'g':
	case 'G':
		return (KEY_G);
	case 'h':
	case 'H':
		return (KEY_H);
	case 'i':
	case 'I':
		return (KEY_I);
	case 'j':
	case 'J':
		return (KEY_J);
	case 'k':
	case 'K':
		return (KEY_K);
	case 'l':
	case 'L':
		return (KEY_L);
	case 'm':
	case 'M':
		return (KEY_M);
	case 'n':
	case 'N':
		return (KEY_N);
	case 'o':
	case 'O':
		return (KEY_O);
	case 'p':
	case 'P':
		return (KEY_P);
	case 'q':
	case 'Q':
		return (KEY_Q);
	case 'r':
	case 'R':
		return (KEY_R);
	case 's':
	case 'S':
		return (KEY_S);
	case 't':
	case 'T':
		return (KEY_T);
	case 'u':
	case 'U':
		return (KEY_U);
	case 'v':
	case 'V':
		return (KEY_V);
	case 'w':
	case 'W':
		return (KEY_W);
	case 'x':
	case 'X':
		return (KEY_X);
	case 'y':
	case 'Y':
		return (KEY_Y);
	case 'z':
	case 'Z':
		return (KEY_Z);
	case 48: // Num0
		return (KEY_NUM0);
	case 49: // Num1
		return (KEY_NUM1);
	case 50: // Num2
		return (KEY_NUM2);
	case 51: // Num3
		return (KEY_NUM3);
	case 52: // Num4
		return (KEY_NUM4);
	case 53: // Num5
		return (KEY_NUM5);
	case 54: // Num6
		return (KEY_NUM6);
	case 55: // Num7
		return (KEY_NUM7);
	case 56: // Num8
		return (KEY_NUM8);
	case 57: // Num9
		return (KEY_NUM9);
	case 42: // NumMultiply
		return (KEY_NUMMULTIPLY);
	case 43: // NumAdd
		return (KEY_NUMADD);
	case 45: // NumSubtract
		return (KEY_NUMSUBTRACT);
		// Minus
	case 46: // NumDecimal
		return (KEY_NUMDECIMAL);
		// Period
	case 47: // NumDivide
		return (KEY_NUMDIVIDE);
		// Slash
		break;
	case 8: // Backspace
		return (KEY_BACKSPACE);
	case 9: // Tab
		return (KEY_TAB);
	case 13: // Enter
		return (KEY_ENTER);
	case 27: // Escape
		return (KEY_ESCAPE);
	case 32: // Space bar
		return (KEY_SPACE);
	case 39: // Apostrophe
		return (KEY_APOSTROPHE);
	case 44: // Comma
		return (KEY_COMMA);
	case 59: // Semicolon
		return (KEY_SEMICOLON);
		// RBracket
	case 61: // Equals
		return (KEY_EQUALS);
	case 91: // LBracket
		return (KEY_LBRACKET);
	case 92: // Backslash
		return (KEY_BACKSLASH);
	case 96: // Grave
		return (KEY_GRAVE);
	case 127: // Delete
		return (KEY_DELETE);
	}
	return NONE;
}

KEY Input::translateKeyCodeToKey(int key)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		return (KEY_F1);
	case GLUT_KEY_F2:
		return (KEY_F2);
	case GLUT_KEY_F3:
		return (KEY_F3);
	case GLUT_KEY_F4:
		return (KEY_F4);
	case GLUT_KEY_F5:
		return (KEY_F5);
	case GLUT_KEY_F6:
		return (KEY_F6);
	case GLUT_KEY_F7:
		return (KEY_F7);
	case GLUT_KEY_F8:
		return (KEY_F8);
	case GLUT_KEY_F9:
		return (KEY_F9);
	case GLUT_KEY_F10:
		return (KEY_F10);
	case GLUT_KEY_F11:
		return (KEY_F11);
	case GLUT_KEY_F12:
		return (KEY_F12);
	case GLUT_KEY_LEFT:
		return (KEY_LEFT);
	case GLUT_KEY_UP:
		return (KEY_UP);
	case GLUT_KEY_RIGHT:
		return (KEY_RIGHT);
	case GLUT_KEY_DOWN:
		return (KEY_DOWN);
	case GLUT_KEY_PAGE_UP:
		return (KEY_PAGEUP);
	case GLUT_KEY_PAGE_DOWN:
		return (KEY_PAGEDOWN);
	case GLUT_KEY_HOME:
		return (KEY_HOME);
	case GLUT_KEY_END:
		return (KEY_END);
	case GLUT_KEY_INSERT:
		return (KEY_INSERT);
	case GLUT_KEY_NUM_LOCK:
		return (KEY_NUMLOCK);
	case GLUT_KEY_BEGIN: // TODO: Find out what key
		return (KEY_HOME);
	case GLUT_KEY_DELETE:
		return (KEY_DELETE);
	case GLUT_KEY_SHIFT_L:
		return (KEY_LSHIFT);
	case GLUT_KEY_SHIFT_R:
		return (KEY_RSHIFT);
	case GLUT_KEY_CTRL_L:
		return (KEY_LCONTROL);
	case GLUT_KEY_CTRL_R:
		return (KEY_RCONTROL);
	case GLUT_KEY_ALT_L:
		return (KEY_LALT);
	case GLUT_KEY_ALT_R:
		return (KEY_RALT);
	}
	return NONE;
}

/**
 * @brief Called everytime some input happened
 * @param key Key that got pressed
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 */
void Input::onKeyInput(unsigned char key, int x, int y)
{
	KEY k = translateCharToKey(key);

	// Make a new pair to insert
	std::pair<KEY, KEYSTATE> pair;
	_pKeys->erase(k);
	pair = std::make_pair(k, PRESSED);
	_pKeys->insert(pair);

	// Call callback
	if (_keyPressedCallback != NULL)
	{
		_keyPressedCallback(k, key);
	}
}

/**
 * @brief Called once a special key on the keyboard got pressed
 * @param key Special key that got pressed
 * @param x X mouse coordinate
 * @param y Y mouse coordinate
 */
void Input::onSpecialKeyInput(int key, int x, int y)
{
	KEY k = translateKeyCodeToKey(key);

	// Make a new pair to insert
	std::pair<KEY, KEYSTATE> pair;
	_pKeys->erase(k);
	pair = std::make_pair(k, PRESSED);
	_pKeys->insert(pair);

	// Call callback
	if (_keyPressedCallback != NULL)
	{
		_keyPressedCallback(k, 0);
	}
}

/**
 * @brief Called once a key was released
 * @param key Key that has been released
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 */
void Input::onKeyInputUp(unsigned char key, int x, int y)
{
	KEY k = translateCharToKey(key);

	// Make a new pair to insert
	std::pair<KEY, KEYSTATE> pair;
	_pKeys->erase(k);
	pair = std::make_pair(k, RELEASED);
	_pKeys->insert(pair);

	// Call callback
	if (_keyReleasedCallback != NULL)
	{
		_keyReleasedCallback(k, key);
	}
}

/**
 * @brief Called once a special key was released
 * @param key Key that has been released
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 */
void Input::onSpecialKeyUp(int key, int x, int y)
{
	KEY k = translateKeyCodeToKey(key);

	// Make a new pair to insert
	std::pair<KEY, KEYSTATE> pair;
	_pKeys->erase(k);
	pair = std::make_pair(k, RELEASED);
	_pKeys->insert(pair);

	// Call callback
	if (_keyReleasedCallback != NULL)
	{
		_keyReleasedCallback(k, 0);
	}
}

/**
 * @brief Called on every mouse input
 * @param button Mouse button that changed state
 * @param state New state of the button
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 */
void Input::onMouseInput(int button, int state, int x, int y)
{
	// Make a new pair to insert
	std::pair<KEY, KEYSTATE> pair;

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		switch (state)
		{
		case GLUT_DOWN:
			pair = std::make_pair(MOUSE_LEFT, PRESSED);
			_pKeys->insert(pair);

			// Call callback
			if (_keyPressedCallback != NULL)
			{
				_keyPressedCallback(MOUSE_LEFT, 0);
			}
			break;
		case GLUT_UP:
			pair = std::make_pair(MOUSE_LEFT, RELEASED);
			_pKeys->insert(pair);

			// Call callback
			if (_keyReleasedCallback != NULL)
			{
				_keyReleasedCallback(MOUSE_LEFT, 0);
			}
			break;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		switch (state)
		{
		case GLUT_DOWN:
			pair = std::make_pair(MOUSE_MIDDLE, PRESSED);
			_pKeys->insert(pair);

			// Call callback
			if (_keyPressedCallback != NULL)
			{
				_keyPressedCallback(MOUSE_MIDDLE, 0);
			}
			break;
		case GLUT_UP:
			pair = std::make_pair(MOUSE_MIDDLE, RELEASED);
			_pKeys->insert(pair);

			// Call callback
			if (_keyReleasedCallback != NULL)
			{
				_keyReleasedCallback(MOUSE_MIDDLE, 0);
			}
			break;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		switch (state)
		{
		case GLUT_DOWN:
			pair = std::make_pair(MOUSE_RIGHT, PRESSED);
			_pKeys->insert(pair);

			// Call callback
			if (_keyPressedCallback != NULL)
			{
				_keyPressedCallback(MOUSE_RIGHT, 0);
			}
			break;
		case GLUT_UP:
			pair = std::make_pair(MOUSE_RIGHT, RELEASED);
			_pKeys->insert(pair);

			// Call callback
			if (_keyReleasedCallback != NULL)
			{
				_keyReleasedCallback(MOUSE_RIGHT, 0);
			}
			break;
		}
		break;
	}
}

/**
 * @brief Called when the mouse got moved with a mouse button pressed down
 * @param x X mouse coordinate
 * @param y Y mouse coordinate
 */
void Input::onMouseDrag(int x, int y)
{
	_lastMouseX = _mouseX;
	_lastMouseY = _mouseY;
	_mouseX = x;
	_mouseY = y;

	// Call callback
	if (_dragCallback != NULL)
	{
		_dragCallback(x, y, _lastMouseX, _lastMouseY);
	}
}

/**
 * @brief Called when the mouse got moved
 * @param x X mouse coordinate
 * @param y Y mouse coordinate
 */
void Input::onMouseMove(int x, int y)
{
	_lastMouseX = _mouseX;
	_lastMouseY = _mouseY;
	_mouseX = x;
	_mouseY = y;
}

/**
 * @brief Called once the mouse wheel changed
 * @param button Mouse button
 * @param dir Direction of scroll wheel
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 */
void Input::onMouseWheel(int button, int dir, int x, int y)
{
	// Call callback
	if (_mouseWheelCallback != NULL)
	{
		_mouseWheelCallback(dir, x, y);
	}
}

/**
 * Update the input handler
 */
void Input::update()
{
	// Check key states
	std::map<KEY, KEYSTATE>::iterator iter;
	for (iter = _pKeys->begin(); iter != _pKeys->end(); ++iter)
	{
		if (iter->second == PRESSED)
		{
			iter->second = DOWN;
		}
		else if (iter->second == RELEASED)
		{
			iter->second = UP;
		}
	}
}

}
/* namespace DBGL */
