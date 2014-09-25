//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include <string>
#include <GLFW/glfw3.h>

namespace dbgl
{
    /**
     * @brief This class unifies all input methods (currently keyboard, mouse and joystick)
     */
    class Input
    {
	private:
	    static const unsigned int keyboard_offset = 0;
	    static const unsigned int mouse_offset = 400;
	    static const unsigned int joystick_offset = 450;
	public:
	    /**
	     * @brief All known input methods
	     * @details This does not only cover keyboards, but also mouse and joystick.
	     * 		Keyboard keys are prefixed KEY_, mouse buttons are prefixed
	     * 		MOUSE_ and joystick buttons are prefixed JOYSTICK_
	     */
	    enum Key
	    {
		UNKNOWN = keyboard_offset + GLFW_KEY_UNKNOWN,                                   //!< KEY_UNKNOWN
		KEY_SPACE = keyboard_offset + GLFW_KEY_SPACE,                                   //!< KEY_SPACE
		KEY_APOSTROPHE = keyboard_offset + GLFW_KEY_APOSTROPHE, /* ' */                 //!< KEY_APOSTROPHE
		KEY_COMMA = keyboard_offset + GLFW_KEY_COMMA, /* , */                           //!< KEY_COMMA
		KEY_MINUS = keyboard_offset + GLFW_KEY_MINUS, /* - */                           //!< KEY_MINUS
		KEY_PERIOD = keyboard_offset + GLFW_KEY_PERIOD, /* . */                         //!< KEY_PERIOD
		KEY_SLASH = keyboard_offset + GLFW_KEY_SLASH, /* / */                           //!< KEY_SLASH
		KEY_0 = keyboard_offset + GLFW_KEY_0,                                           //!< KEY_0
		KEY_1 = keyboard_offset + GLFW_KEY_1,                                           //!< KEY_1
		KEY_2 = keyboard_offset + GLFW_KEY_2,                                           //!< KEY_2
		KEY_3 = keyboard_offset + GLFW_KEY_3,                                           //!< KEY_3
		KEY_4 = keyboard_offset + GLFW_KEY_4,                                           //!< KEY_4
		KEY_5 = keyboard_offset + GLFW_KEY_5,                                           //!< KEY_5
		KEY_6 = keyboard_offset + GLFW_KEY_6,                                           //!< KEY_6
		KEY_7 = keyboard_offset + GLFW_KEY_7,                                           //!< KEY_7
		KEY_8 = keyboard_offset + GLFW_KEY_8,                                           //!< KEY_8
		KEY_9 = keyboard_offset + GLFW_KEY_9,                                           //!< KEY_9
		KEY_SEMICOLON = keyboard_offset + GLFW_KEY_SEMICOLON, /* ; */                   //!< KEY_SEMICOLON
		KEY_EQUAL = keyboard_offset + GLFW_KEY_EQUAL, /* = */                           //!< KEY_EQUAL
		KEY_A = keyboard_offset + GLFW_KEY_A,                                           //!< KEY_A
		KEY_B = keyboard_offset + GLFW_KEY_B,                                           //!< KEY_B
		KEY_C = keyboard_offset + GLFW_KEY_C,                                           //!< KEY_C
		KEY_D = keyboard_offset + GLFW_KEY_D,                                           //!< KEY_D
		KEY_E = keyboard_offset + GLFW_KEY_E,                                           //!< KEY_E
		KEY_F = keyboard_offset + GLFW_KEY_F,                                           //!< KEY_F
		KEY_G = keyboard_offset + GLFW_KEY_G,                                           //!< KEY_G
		KEY_H = keyboard_offset + GLFW_KEY_H,                                           //!< KEY_H
		KEY_I = keyboard_offset + GLFW_KEY_I,                                           //!< KEY_I
		KEY_J = keyboard_offset + GLFW_KEY_J,                                           //!< KEY_J
		KEY_K = keyboard_offset + GLFW_KEY_K,                                           //!< KEY_K
		KEY_L = keyboard_offset + GLFW_KEY_L,                                           //!< KEY_L
		KEY_M = keyboard_offset + GLFW_KEY_M,                                           //!< KEY_M
		KEY_N = keyboard_offset + GLFW_KEY_N,                                           //!< KEY_N
		KEY_O = keyboard_offset + GLFW_KEY_O,                                           //!< KEY_O
		KEY_P = keyboard_offset + GLFW_KEY_P,                                           //!< KEY_P
		KEY_Q = keyboard_offset + GLFW_KEY_Q,                                           //!< KEY_Q
		KEY_R = keyboard_offset + GLFW_KEY_R,                                           //!< KEY_R
		KEY_S = keyboard_offset + GLFW_KEY_S,                                           //!< KEY_S
		KEY_T = keyboard_offset + GLFW_KEY_T,                                           //!< KEY_T
		KEY_U = keyboard_offset + GLFW_KEY_U,                                           //!< KEY_U
		KEY_V = keyboard_offset + GLFW_KEY_V,                                           //!< KEY_V
		KEY_W = keyboard_offset + GLFW_KEY_W,                                           //!< KEY_W
		KEY_X = keyboard_offset + GLFW_KEY_X,                                           //!< KEY_X
		KEY_Y = keyboard_offset + GLFW_KEY_Y,                                           //!< KEY_Y
		KEY_Z = keyboard_offset + GLFW_KEY_Z,                                           //!< KEY_Z
		KEY_LEFT_BRACKET = keyboard_offset + GLFW_KEY_LEFT_BRACKET, /* [ */             //!< KEY_LEFT_BRACKET
		KEY_BACKSLASH = keyboard_offset + GLFW_KEY_BACKSLASH, /* \ */                   //!< KEY_BACKSLASH
		KEY_RIGHT_BRACKET = keyboard_offset + GLFW_KEY_RIGHT_BRACKET, /* ] */           //!< KEY_RIGHT_BRACKET
		KEY_GRAVE_ACCENT = keyboard_offset + GLFW_KEY_GRAVE_ACCENT, /* ` */             //!< KEY_GRAVE_ACCENT
		KEY_WORLD_1 = keyboard_offset + GLFW_KEY_WORLD_1, /* non-US #1 */               //!< KEY_WORLD_1
		KEY_WORLD_2 = keyboard_offset + GLFW_KEY_WORLD_2, /* non-US #2 */               //!< KEY_WORLD_2
		KEY_ESCAPE = keyboard_offset + GLFW_KEY_ESCAPE,                                 //!< KEY_ESCAPE
		KEY_ENTER = keyboard_offset + GLFW_KEY_ENTER,                                   //!< KEY_ENTER
		KEY_TAB = keyboard_offset + GLFW_KEY_TAB,                                       //!< KEY_TAB
		KEY_BACKSPACE = keyboard_offset + GLFW_KEY_BACKSPACE,                           //!< KEY_BACKSPACE
		KEY_INSERT = keyboard_offset + GLFW_KEY_INSERT,                                 //!< KEY_INSERT
		KEY_DELETE = keyboard_offset + GLFW_KEY_DELETE,                                 //!< KEY_DELETE
		KEY_RIGHT = keyboard_offset + GLFW_KEY_RIGHT,                                   //!< KEY_RIGHT
		KEY_LEFT = keyboard_offset + GLFW_KEY_LEFT,                                     //!< KEY_LEFT
		KEY_DOWN = keyboard_offset + GLFW_KEY_DOWN,                                     //!< KEY_DOWN
		KEY_UP = keyboard_offset + GLFW_KEY_UP,                                         //!< KEY_UP
		KEY_PAGE_UP = keyboard_offset + GLFW_KEY_PAGE_UP,                               //!< KEY_PAGE_UP
		KEY_PAGE_DOWN = keyboard_offset + GLFW_KEY_PAGE_DOWN,                           //!< KEY_PAGE_DOWN
		KEY_HOME = keyboard_offset + GLFW_KEY_HOME,                                     //!< KEY_HOME
		KEY_END = keyboard_offset + GLFW_KEY_END,                                       //!< KEY_END
		KEY_CAPS_LOCK = keyboard_offset + GLFW_KEY_CAPS_LOCK,                           //!< KEY_CAPS_LOCK
		KEY_SCROLL_LOCK = keyboard_offset + GLFW_KEY_SCROLL_LOCK,                       //!< KEY_SCROLL_LOCK
		KEY_NUM_LOCK = keyboard_offset + GLFW_KEY_NUM_LOCK,                             //!< KEY_NUM_LOCK
		KEY_PRINT_SCREEN = keyboard_offset + GLFW_KEY_PRINT_SCREEN,                     //!< KEY_PRINT_SCREEN
		KEY_PAUSE = keyboard_offset + GLFW_KEY_PAUSE,                                   //!< KEY_PAUSE
		KEY_F1 = keyboard_offset + GLFW_KEY_F1,                                         //!< KEY_F1
		KEY_F2 = keyboard_offset + GLFW_KEY_F2,                                         //!< KEY_F2
		KEY_F3 = keyboard_offset + GLFW_KEY_F3,                                         //!< KEY_F3
		KEY_F4 = keyboard_offset + GLFW_KEY_F4,                                         //!< KEY_F4
		KEY_F5 = keyboard_offset + GLFW_KEY_F5,                                         //!< KEY_F5
		KEY_F6 = keyboard_offset + GLFW_KEY_F6,                                         //!< KEY_F6
		KEY_F7 = keyboard_offset + GLFW_KEY_F7,                                         //!< KEY_F7
		KEY_F8 = keyboard_offset + GLFW_KEY_F8,                                         //!< KEY_F8
		KEY_F9 = keyboard_offset + GLFW_KEY_F9,                                         //!< KEY_F9
		KEY_F10 = keyboard_offset + GLFW_KEY_F10,                                       //!< KEY_F10
		KEY_F11 = keyboard_offset + GLFW_KEY_F11,                                       //!< KEY_F11
		KEY_F12 = keyboard_offset + GLFW_KEY_F12,                                       //!< KEY_F12
		KEY_F13 = keyboard_offset + GLFW_KEY_F13,                                       //!< KEY_F13
		KEY_F14 = keyboard_offset + GLFW_KEY_F14,                                       //!< KEY_F14
		KEY_F15 = keyboard_offset + GLFW_KEY_F15,                                       //!< KEY_F15
		KEY_F16 = keyboard_offset + GLFW_KEY_F16,                                       //!< KEY_F16
		KEY_F17 = keyboard_offset + GLFW_KEY_F17,                                       //!< KEY_F17
		KEY_F18 = keyboard_offset + GLFW_KEY_F18,                                       //!< KEY_F18
		KEY_F19 = keyboard_offset + GLFW_KEY_F19,                                       //!< KEY_F19
		KEY_F20 = keyboard_offset + GLFW_KEY_F20,                                       //!< KEY_F20
		KEY_F21 = keyboard_offset + GLFW_KEY_F21,                                       //!< KEY_F21
		KEY_F22 = keyboard_offset + GLFW_KEY_F22,                                       //!< KEY_F22
		KEY_F23 = keyboard_offset + GLFW_KEY_F23,                                       //!< KEY_F23
		KEY_F24 = keyboard_offset + GLFW_KEY_F24,                                       //!< KEY_F24
		KEY_F25 = keyboard_offset + GLFW_KEY_F25,                                       //!< KEY_F25
		KEY_KP_0 = keyboard_offset + GLFW_KEY_KP_0,                                     //!< KEY_KP_0
		KEY_KP_1 = keyboard_offset + GLFW_KEY_KP_1,                                     //!< KEY_KP_1
		KEY_KP_2 = keyboard_offset + GLFW_KEY_KP_2,                                     //!< KEY_KP_2
		KEY_KP_3 = keyboard_offset + GLFW_KEY_KP_3,                                     //!< KEY_KP_3
		KEY_KP_4 = keyboard_offset + GLFW_KEY_KP_4,                                     //!< KEY_KP_4
		KEY_KP_5 = keyboard_offset + GLFW_KEY_KP_5,                                     //!< KEY_KP_5
		KEY_KP_6 = keyboard_offset + GLFW_KEY_KP_6,                                     //!< KEY_KP_6
		KEY_KP_7 = keyboard_offset + GLFW_KEY_KP_7,                                     //!< KEY_KP_7
		KEY_KP_8 = keyboard_offset + GLFW_KEY_KP_8,                                     //!< KEY_KP_8
		KEY_KP_9 = keyboard_offset + GLFW_KEY_KP_9,                                     //!< KEY_KP_9
		KEY_KP_DECIMAL = keyboard_offset + GLFW_KEY_KP_DECIMAL,                         //!< KEY_KP_DECIMAL
		KEY_KP_DIVIDE = keyboard_offset + GLFW_KEY_KP_DIVIDE,                           //!< KEY_KP_DIVIDE
		KEY_KP_MULTIPLY = keyboard_offset + GLFW_KEY_KP_MULTIPLY,                       //!< KEY_KP_MULTIPLY
		KEY_KP_SUBTRACT = keyboard_offset + GLFW_KEY_KP_SUBTRACT,                       //!< KEY_KP_SUBTRACT
		KEY_KP_ADD = keyboard_offset + GLFW_KEY_KP_ADD,                                 //!< KEY_KP_ADD
		KEY_KP_ENTER = keyboard_offset + GLFW_KEY_KP_ENTER,                             //!< KEY_KP_ENTER
		KEY_KP_EQUAL = keyboard_offset + GLFW_KEY_KP_EQUAL,                             //!< KEY_KP_EQUAL
		KEY_LEFT_SHIFT = keyboard_offset + GLFW_KEY_LEFT_SHIFT,                         //!< KEY_LEFT_SHIFT
		KEY_LEFT_CONTROL = keyboard_offset + GLFW_KEY_LEFT_CONTROL,                     //!< KEY_LEFT_CONTROL
		KEY_LEFT_ALT = keyboard_offset + GLFW_KEY_LEFT_ALT,                             //!< KEY_LEFT_ALT
		KEY_LEFT_SUPER = keyboard_offset + GLFW_KEY_LEFT_SUPER,                         //!< KEY_LEFT_SUPER
		KEY_RIGHT_SHIFT = keyboard_offset + GLFW_KEY_RIGHT_SHIFT,                       //!< KEY_RIGHT_SHIFT
		KEY_RIGHT_CONTROL = keyboard_offset + GLFW_KEY_RIGHT_CONTROL,                   //!< KEY_RIGHT_CONTROL
		KEY_RIGHT_ALT = keyboard_offset + GLFW_KEY_RIGHT_ALT,                           //!< KEY_RIGHT_ALT
		KEY_RIGHT_SUPER = keyboard_offset + GLFW_KEY_RIGHT_SUPER,                       //!< KEY_RIGHT_SUPER
		KEY_MENU = keyboard_offset + GLFW_KEY_MENU,                                     //!< KEY_MENU
		KEY_LAST = keyboard_offset + GLFW_KEY_LAST,                                     //!< KEY_LAST
		MOUSE_BUTTON_1 = mouse_offset + GLFW_MOUSE_BUTTON_1,          //!< MOUSE_BUTTON_1
		MOUSE_BUTTON_2 = mouse_offset + GLFW_MOUSE_BUTTON_2,          //!< MOUSE_BUTTON_2
		MOUSE_BUTTON_3 = mouse_offset + GLFW_MOUSE_BUTTON_3,          //!< MOUSE_BUTTON_3
		MOUSE_BUTTON_4 = mouse_offset + GLFW_MOUSE_BUTTON_4,          //!< MOUSE_BUTTON_4
		MOUSE_BUTTON_5 = mouse_offset + GLFW_MOUSE_BUTTON_5,          //!< MOUSE_BUTTON_5
		MOUSE_BUTTON_6 = mouse_offset + GLFW_MOUSE_BUTTON_6,          //!< MOUSE_BUTTON_6
		MOUSE_BUTTON_7 = mouse_offset + GLFW_MOUSE_BUTTON_7,          //!< MOUSE_BUTTON_7
		MOUSE_BUTTON_8 = mouse_offset + GLFW_MOUSE_BUTTON_8,          //!< MOUSE_BUTTON_8
		MOUSE_BUTTON_LAST = mouse_offset + GLFW_MOUSE_BUTTON_LAST,    //!< MOUSE_BUTTON_LAST
		MOUSE_BUTTON_LEFT = mouse_offset + GLFW_MOUSE_BUTTON_LEFT,    //!< MOUSE_BUTTON_LEFT
		MOUSE_BUTTON_RIGHT = mouse_offset + GLFW_MOUSE_BUTTON_RIGHT,  //!< MOUSE_BUTTON_RIGHT
		MOUSE_BUTTON_MIDDLE = mouse_offset + GLFW_MOUSE_BUTTON_MIDDLE,//!< MOUSE_BUTTON_MIDDLE
		JOYSTICK_1 = joystick_offset + GLFW_JOYSTICK_1,               //!< JOYSTICK_1
		JOYSTICK_2 = joystick_offset + GLFW_JOYSTICK_2,               //!< JOYSTICK_2
		JOYSTICK_3 = joystick_offset + GLFW_JOYSTICK_3,               //!< JOYSTICK_3
		JOYSTICK_4 = joystick_offset + GLFW_JOYSTICK_4,               //!< JOYSTICK_4
		JOYSTICK_5 = joystick_offset + GLFW_JOYSTICK_5,               //!< JOYSTICK_5
		JOYSTICK_6 = joystick_offset + GLFW_JOYSTICK_6,               //!< JOYSTICK_6
		JOYSTICK_7 = joystick_offset + GLFW_JOYSTICK_7,               //!< JOYSTICK_7
		JOYSTICK_8 = joystick_offset + GLFW_JOYSTICK_8,               //!< JOYSTICK_8
		JOYSTICK_9 = joystick_offset + GLFW_JOYSTICK_9,               //!< JOYSTICK_9
		JOYSTICK_10 = joystick_offset + GLFW_JOYSTICK_10,             //!< JOYSTICK_10
		JOYSTICK_11 = joystick_offset + GLFW_JOYSTICK_11,             //!< JOYSTICK_11
		JOYSTICK_12 = joystick_offset + GLFW_JOYSTICK_12,             //!< JOYSTICK_12
		JOYSTICK_13 = joystick_offset + GLFW_JOYSTICK_13,             //!< JOYSTICK_13
		JOYSTICK_14 = joystick_offset + GLFW_JOYSTICK_14,             //!< JOYSTICK_14
		JOYSTICK_15 = joystick_offset + GLFW_JOYSTICK_15,             //!< JOYSTICK_15
		JOYSTICK_16 = joystick_offset + GLFW_JOYSTICK_16,             //!< JOYSTICK_16
		JOYSTICK_LAST = joystick_offset + GLFW_JOYSTICK_LAST,         //!< JOYSTICK_LAST
	    };
	    /**
	     * @brief Known states for buttons
	     */
	    enum KeyState
	    {
		RELEASED = GLFW_RELEASE,//!< RELEASED Key got just released
		PRESSED = GLFW_PRESS, 	//!< PRESSED Key got just pressed
		DOWN = GLFW_REPEAT,    	//!< DOWN Key is currently held down
		UP,     		//!< UP Key is currently not held down
	    };
	    /**
	     * @brief Modifier key constants
	     */
	    enum Modifier
	    {
		KEY_ALT = GLFW_MOD_ALT,
		KEY_CONTROL = GLFW_MOD_CONTROL,
		KEY_SHIFT = GLFW_MOD_SHIFT,
		KEY_SUPER = GLFW_MOD_SUPER,
	    };

	    /**
	     * @brief Constructor
	     */
	    Input() = default;
	    /**
	     * @brief Checks if the passed key is currently held down
	     * @param key Key to check
	     * @return \code True \endcode in case the key is down, otherwise \code false \endcode
	     */
	    bool isDown(Key key) const;
	    /**
	     * @brief Checks if the passed modifier key is currently held down
	     * @param mod Modifier to check
	     * @return \code True \endcode in case the key is down, otherwise \code false \endcode
	     */
	    bool isDown(Modifier mod) const;
	    /**
	     * @brief Checks if the passed key is currently not held down
	     * @param key Key to check
	     * @return \code True \endcode in case the key is up, otherwise \code false \endcode
	     */
	    bool isUp(Key key) const;
	    /**
	     * @brief Checks if the passed key was just pressed down
	     * @param key Key to check
	     * @return \code True \endcode in case the key is pressed, otherwise \code false \endcode
	     */
	    bool isPressed(Key key) const;
	    /**
	     * @brief Checks if the passed key was just released
	     * @param key Key to check
	     * @return \code True \endcode in case the key is released, otherwise \code false \endcode
	     */
	    bool isReleased(Key key) const;
	    /**
	     * @brief Retrieves the current key state for a specific key
	     * @param key Key to check
	     * @return KeyState of that key
	     */
	    KeyState getState(Key key) const;
	    /**
	     * @brief Updates the underlying data structures
	     * @pre Needs to be called once per update cycle
	     */
	    void update();
	    /**
	     * @brief Updates the passed key to the passed key state
	     * @param key Key to update
	     * @param state New key state
	     */
	    void updateKey(Key key, KeyState state);
	    /**
	     * @brief Translates a character to a key constant
	     * @param character Character to translate
	     * @return The key constant representing that character
	     * @note This does currently not consider the keyboard layout of the user but
	     * 	     assumes a US keyboard
	     */
	    static Key charToKey(char character);
	    /**
	     * @brief Translates a key constant into a character if possible
	     * @param key Key to translate
	     * @return The character representing the passed key or an empty character
	     * 	       if the key can not be translated into a character
	     */
	    static char keyToChar(Key key);
	    /**
	     * @brief Translates a key constant into an appropriate string
	     * @param key Key to translate
	     * @return A string describing the passed key
	     */
	    static std::string keyToString(Key key);
	private:
	    Input(Input const& other); // Prevent copies
	    Input& operator=(Input const& other);

	    using KeyDescriptionMap = std::map<Key, std::string>;

	    /**
	     * @brief Map of all keys and their current key state
	     */
	    std::map<Key, KeyState> m_keys;
	    /**
	     * @brief Mapping between key constants and descriptive strings.
	     * @note English descriptions, but might be modified in later versions to
	     * 	     allow for easy localization
	     */
	    static KeyDescriptionMap keyDescriptions;

	    friend class GLOpenGL33;
	    friend class Window;
    };
}

#endif /* INPUT_H_ */
