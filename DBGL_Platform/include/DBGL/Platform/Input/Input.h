//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include <string>

namespace dbgl
{
    /**
     * @brief This class unifies all input methods (currently keyboard, mouse and joystick)
     */
    class Input
    {
	public:
	    /**
	     * @brief Starting point for keys on the keyboard inside the Key enum
	     */
	    static const unsigned int keyboard_offset = 0;
	    /**
	     * @brief Starting point for mouse buttons inside the Key enum
	     */
	    static const unsigned int mouse_offset = 400;
	    /**
	     * @brief Starting point for joystick buttons inside the Key enum
	     */
	    static const unsigned int joystick_offset = 450;

	    /**
	     * @brief All known input methods
	     * @details This does not only cover keyboards, but also mouse and joystick.
	     * 		Keyboard keys are prefixed KEY_, mouse buttons are prefixed
	     * 		MOUSE_ and joystick buttons are prefixed JOYSTICK_
	     */
	    enum Key
	    {
		UNKNOWN = keyboard_offset + -1,                                //!< KEY_UNKNOWN
		KEY_SPACE = keyboard_offset + 32,                              //!< KEY_SPACE
		KEY_APOSTROPHE = keyboard_offset + 39, /* ' */                 //!< KEY_APOSTROPHE
		KEY_COMMA = keyboard_offset + 44, /* , */                      //!< KEY_COMMA
		KEY_MINUS = keyboard_offset + 45, /* - */                      //!< KEY_MINUS
		KEY_PERIOD = keyboard_offset + 46, /* . */                     //!< KEY_PERIOD
		KEY_SLASH = keyboard_offset + 47, /* / */                      //!< KEY_SLASH
		KEY_0 = keyboard_offset + 48,                                  //!< KEY_0
		KEY_1 = keyboard_offset + 49,                                  //!< KEY_1
		KEY_2 = keyboard_offset + 50,                                  //!< KEY_2
		KEY_3 = keyboard_offset + 51,                                  //!< KEY_3
		KEY_4 = keyboard_offset + 52,                                  //!< KEY_4
		KEY_5 = keyboard_offset + 53,                                  //!< KEY_5
		KEY_6 = keyboard_offset + 54,                                  //!< KEY_6
		KEY_7 = keyboard_offset + 55,                                  //!< KEY_7
		KEY_8 = keyboard_offset + 56,                                  //!< KEY_8
		KEY_9 = keyboard_offset + 57,                                  //!< KEY_9
		KEY_SEMICOLON = keyboard_offset + 59, /* ; */                  //!< KEY_SEMICOLON
		KEY_EQUAL = keyboard_offset + 61, /* = */                      //!< KEY_EQUAL
		KEY_A = keyboard_offset + 65,                                  //!< KEY_A
		KEY_B = keyboard_offset + 66,                                  //!< KEY_B
		KEY_C = keyboard_offset + 67,                                  //!< KEY_C
		KEY_D = keyboard_offset + 68,                                  //!< KEY_D
		KEY_E = keyboard_offset + 69,                                  //!< KEY_E
		KEY_F = keyboard_offset + 70,                                  //!< KEY_F
		KEY_G = keyboard_offset + 71,                                  //!< KEY_G
		KEY_H = keyboard_offset + 72,                                  //!< KEY_H
		KEY_I = keyboard_offset + 73,                                  //!< KEY_I
		KEY_J = keyboard_offset + 74,                                  //!< KEY_J
		KEY_K = keyboard_offset + 75,                                  //!< KEY_K
		KEY_L = keyboard_offset + 76,                                  //!< KEY_L
		KEY_M = keyboard_offset + 77,                                  //!< KEY_M
		KEY_N = keyboard_offset + 78,                                  //!< KEY_N
		KEY_O = keyboard_offset + 79,                                  //!< KEY_O
		KEY_P = keyboard_offset + 80,                                  //!< KEY_P
		KEY_Q = keyboard_offset + 81,                                  //!< KEY_Q
		KEY_R = keyboard_offset + 82,                                  //!< KEY_R
		KEY_S = keyboard_offset + 83,                                  //!< KEY_S
		KEY_T = keyboard_offset + 84,                                  //!< KEY_T
		KEY_U = keyboard_offset + 85,                                  //!< KEY_U
		KEY_V = keyboard_offset + 86,                                  //!< KEY_V
		KEY_W = keyboard_offset + 87,                                  //!< KEY_W
		KEY_X = keyboard_offset + 88,                                  //!< KEY_X
		KEY_Y = keyboard_offset + 89,                                  //!< KEY_Y
		KEY_Z = keyboard_offset + 90,                                  //!< KEY_Z
		KEY_LEFT_BRACKET = keyboard_offset + 91, /* [ */               //!< KEY_LEFT_BRACKET
		KEY_BACKSLASH = keyboard_offset + 92, /* \ */                  //!< KEY_BACKSLASH
		KEY_RIGHT_BRACKET = keyboard_offset + 93, /* ] */              //!< KEY_RIGHT_BRACKET
		KEY_GRAVE_ACCENT = keyboard_offset + 96, /* ` */               //!< KEY_GRAVE_ACCENT
		KEY_WORLD_1 = keyboard_offset + 161, /* non-US #1 */           //!< KEY_WORLD_1
		KEY_WORLD_2 = keyboard_offset + 162, /* non-US #2 */           //!< KEY_WORLD_2
		KEY_ESCAPE = keyboard_offset + 256,                            //!< KEY_ESCAPE
		KEY_ENTER = keyboard_offset + 257,                             //!< KEY_ENTER
		KEY_TAB = keyboard_offset + 258,                               //!< KEY_TAB
		KEY_BACKSPACE = keyboard_offset + 259,                         //!< KEY_BACKSPACE
		KEY_INSERT = keyboard_offset + 260,                            //!< KEY_INSERT
		KEY_DELETE = keyboard_offset + 261,                            //!< KEY_DELETE
		KEY_RIGHT = keyboard_offset + 262,                             //!< KEY_RIGHT
		KEY_LEFT = keyboard_offset + 263,                              //!< KEY_LEFT
		KEY_DOWN = keyboard_offset + 264,                              //!< KEY_DOWN
		KEY_UP = keyboard_offset + 265,                                //!< KEY_UP
		KEY_PAGE_UP = keyboard_offset + 266,                           //!< KEY_PAGE_UP
		KEY_PAGE_DOWN = keyboard_offset + 267,                         //!< KEY_PAGE_DOWN
		KEY_HOME = keyboard_offset + 268,                              //!< KEY_HOME
		KEY_END = keyboard_offset + 269,                               //!< KEY_END
		KEY_CAPS_LOCK = keyboard_offset + 280,                         //!< KEY_CAPS_LOCK
		KEY_SCROLL_LOCK = keyboard_offset + 281,                       //!< KEY_SCROLL_LOCK
		KEY_NUM_LOCK = keyboard_offset + 282,                          //!< KEY_NUM_LOCK
		KEY_PRINT_SCREEN = keyboard_offset + 283,                      //!< KEY_PRINT_SCREEN
		KEY_PAUSE = keyboard_offset + 284,                             //!< KEY_PAUSE
		KEY_F1 = keyboard_offset + 290,                                //!< KEY_F1
		KEY_F2 = keyboard_offset + 291,                                //!< KEY_F2
		KEY_F3 = keyboard_offset + 292,                                //!< KEY_F3
		KEY_F4 = keyboard_offset + 293,                                //!< KEY_F4
		KEY_F5 = keyboard_offset + 294,                                //!< KEY_F5
		KEY_F6 = keyboard_offset + 295,                                //!< KEY_F6
		KEY_F7 = keyboard_offset + 296,                                //!< KEY_F7
		KEY_F8 = keyboard_offset + 297,                                //!< KEY_F8
		KEY_F9 = keyboard_offset + 298,                                //!< KEY_F9
		KEY_F10 = keyboard_offset + 299,                               //!< KEY_F10
		KEY_F11 = keyboard_offset + 300,                               //!< KEY_F11
		KEY_F12 = keyboard_offset + 301,                               //!< KEY_F12
		KEY_F13 = keyboard_offset + 302,                               //!< KEY_F13
		KEY_F14 = keyboard_offset + 303,                               //!< KEY_F14
		KEY_F15 = keyboard_offset + 304,                               //!< KEY_F15
		KEY_F16 = keyboard_offset + 305,                               //!< KEY_F16
		KEY_F17 = keyboard_offset + 306,                               //!< KEY_F17
		KEY_F18 = keyboard_offset + 307,                               //!< KEY_F18
		KEY_F19 = keyboard_offset + 308,                               //!< KEY_F19
		KEY_F20 = keyboard_offset + 309,                               //!< KEY_F20
		KEY_F21 = keyboard_offset + 310,                               //!< KEY_F21
		KEY_F22 = keyboard_offset + 311,                               //!< KEY_F22
		KEY_F23 = keyboard_offset + 312,                               //!< KEY_F23
		KEY_F24 = keyboard_offset + 313,                               //!< KEY_F24
		KEY_F25 = keyboard_offset + 314,                               //!< KEY_F25
		KEY_KP_0 = keyboard_offset + 320,                              //!< KEY_KP_0
		KEY_KP_1 = keyboard_offset + 321,                              //!< KEY_KP_1
		KEY_KP_2 = keyboard_offset + 322,                              //!< KEY_KP_2
		KEY_KP_3 = keyboard_offset + 323,                              //!< KEY_KP_3
		KEY_KP_4 = keyboard_offset + 324,                              //!< KEY_KP_4
		KEY_KP_5 = keyboard_offset + 325,                              //!< KEY_KP_5
		KEY_KP_6 = keyboard_offset + 326,                              //!< KEY_KP_6
		KEY_KP_7 = keyboard_offset + 327,                              //!< KEY_KP_7
		KEY_KP_8 = keyboard_offset + 328,                              //!< KEY_KP_8
		KEY_KP_9 = keyboard_offset + 329,                              //!< KEY_KP_9
		KEY_KP_DECIMAL = keyboard_offset + 330,                        //!< KEY_KP_DECIMAL
		KEY_KP_DIVIDE = keyboard_offset + 331,                         //!< KEY_KP_DIVIDE
		KEY_KP_MULTIPLY = keyboard_offset + 332,                       //!< KEY_KP_MULTIPLY
		KEY_KP_SUBTRACT = keyboard_offset + 333,                       //!< KEY_KP_SUBTRACT
		KEY_KP_ADD = keyboard_offset + 334,                            //!< KEY_KP_ADD
		KEY_KP_ENTER = keyboard_offset + 335,                          //!< KEY_KP_ENTER
		KEY_KP_EQUAL = keyboard_offset + 336,                          //!< KEY_KP_EQUAL
		KEY_LEFT_SHIFT = keyboard_offset + 340,                        //!< KEY_LEFT_SHIFT
		KEY_LEFT_CONTROL = keyboard_offset + 341,                      //!< KEY_LEFT_CONTROL
		KEY_LEFT_ALT = keyboard_offset + 342,                          //!< KEY_LEFT_ALT
		KEY_LEFT_SUPER = keyboard_offset + 343,                        //!< KEY_LEFT_SUPER
		KEY_RIGHT_SHIFT = keyboard_offset + 344,                       //!< KEY_RIGHT_SHIFT
		KEY_RIGHT_CONTROL = keyboard_offset + 345,                     //!< KEY_RIGHT_CONTROL
		KEY_RIGHT_ALT = keyboard_offset + 346,                         //!< KEY_RIGHT_ALT
		KEY_RIGHT_SUPER = keyboard_offset + 347,                       //!< KEY_RIGHT_SUPER
		KEY_MENU = keyboard_offset + 348,                              //!< KEY_MENU
		KEY_LAST = keyboard_offset + 348,                              //!< KEY_LAST
		MOUSE_BUTTON_1 = mouse_offset + 0,                             //!< MOUSE_BUTTON_1
		MOUSE_BUTTON_2 = mouse_offset + 1,                             //!< MOUSE_BUTTON_2
		MOUSE_BUTTON_3 = mouse_offset + 2,                             //!< MOUSE_BUTTON_3
		MOUSE_BUTTON_4 = mouse_offset + 3,                             //!< MOUSE_BUTTON_4
		MOUSE_BUTTON_5 = mouse_offset + 4,                             //!< MOUSE_BUTTON_5
		MOUSE_BUTTON_6 = mouse_offset + 5,                             //!< MOUSE_BUTTON_6
		MOUSE_BUTTON_7 = mouse_offset + 6,                             //!< MOUSE_BUTTON_7
		MOUSE_BUTTON_8 = mouse_offset + 7,                             //!< MOUSE_BUTTON_8
		MOUSE_BUTTON_LAST = mouse_offset + 7,                          //!< MOUSE_BUTTON_LAST
		MOUSE_BUTTON_LEFT = mouse_offset + MOUSE_BUTTON_1,             //!< MOUSE_BUTTON_LEFT
		MOUSE_BUTTON_RIGHT = mouse_offset + MOUSE_BUTTON_2,            //!< MOUSE_BUTTON_RIGHT
		MOUSE_BUTTON_MIDDLE = mouse_offset + MOUSE_BUTTON_3,           //!< MOUSE_BUTTON_MIDDLE
		JOYSTICK_1 = joystick_offset + 0,                              //!< JOYSTICK_1
		JOYSTICK_2 = joystick_offset + 1,                              //!< JOYSTICK_2
		JOYSTICK_3 = joystick_offset + 2,                              //!< JOYSTICK_3
		JOYSTICK_4 = joystick_offset + 3,                              //!< JOYSTICK_4
		JOYSTICK_5 = joystick_offset + 4,                              //!< JOYSTICK_5
		JOYSTICK_6 = joystick_offset + 5,                              //!< JOYSTICK_6
		JOYSTICK_7 = joystick_offset + 6,                              //!< JOYSTICK_7
		JOYSTICK_8 = joystick_offset + 7,                              //!< JOYSTICK_8
		JOYSTICK_9 = joystick_offset + 8,                              //!< JOYSTICK_9
		JOYSTICK_10 = joystick_offset + 9,                             //!< JOYSTICK_10
		JOYSTICK_11 = joystick_offset + 10,                            //!< JOYSTICK_11
		JOYSTICK_12 = joystick_offset + 11,                            //!< JOYSTICK_12
		JOYSTICK_13 = joystick_offset + 12,                            //!< JOYSTICK_13
		JOYSTICK_14 = joystick_offset + 13,                            //!< JOYSTICK_14
		JOYSTICK_15 = joystick_offset + 14,                            //!< JOYSTICK_15
		JOYSTICK_16 = joystick_offset + 15,                            //!< JOYSTICK_16
		JOYSTICK_LAST = joystick_offset + 15,                          //!< JOYSTICK_LAST
	    };
	    /**
	     * @brief Known states for buttons
	     */
	    enum KeyState
	    {
		RELEASED,	//!< RELEASED Key got just released
		PRESSED, 	//!< PRESSED Key got just pressed
		DOWN,    	//!< DOWN Key is currently held down
		UP,     	//!< UP Key is currently not held down
	    };
	    /**
	     * @brief Modifier key constants
	     */
	    enum Modifier
	    {
		NONE,
		KEY_ALT,
		KEY_CONTROL,
		KEY_SHIFT,
		KEY_SUPER,
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
    };
}

#endif /* INPUT_H_ */
