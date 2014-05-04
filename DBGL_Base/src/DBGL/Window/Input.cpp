//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Window/Input.h"

namespace dbgl
{
    // Init static variable
    Input::KeyDescriptionMap Input::keyDescriptions = {
	{ UNKNOWN, "Unknown" },
	{ KEY_SPACE, "Space" },
	{ KEY_APOSTROPHE, "`" },
	{ KEY_COMMA, "," },
	{ KEY_MINUS, "-" },
	{ KEY_PERIOD, "." },
	{ KEY_SLASH, "/" },
    //	{KEY_0, GLFW_KEY_0},
    //	{KEY_1, GLFW_KEY_1},
    //	{KEY_2, GLFW_KEY_2},
    //	{KEY_3, GLFW_KEY_3},
    //	{KEY_4, GLFW_KEY_4},
    //	{KEY_5, GLFW_KEY_5},
    //	{KEY_6, GLFW_KEY_6},
    //	{KEY_7, GLFW_KEY_7},
    //	{KEY_8, GLFW_KEY_8},
    //	{KEY_9, GLFW_KEY_9},
	{ KEY_SEMICOLON, ";" },
	{ KEY_EQUAL, "=" },
    //	{KEY_A, GLFW_KEY_A},
    //	{KEY_B, GLFW_KEY_B},
    //	{KEY_C, GLFW_KEY_C},
    //	{KEY_D, GLFW_KEY_D},
    //	{KEY_E, GLFW_KEY_E},
    //	{KEY_F, GLFW_KEY_F},
    //	{KEY_G, GLFW_KEY_G},
    //	{KEY_H, GLFW_KEY_H},
    //	{KEY_I, GLFW_KEY_I},
    //	{KEY_J, GLFW_KEY_J},
    //	{KEY_K, GLFW_KEY_K},
    //	{KEY_L, GLFW_KEY_L},
    //	{KEY_M, GLFW_KEY_M},
    //	{KEY_N, GLFW_KEY_N},
    //	{KEY_O, GLFW_KEY_O},
    //	{KEY_P, GLFW_KEY_P},
    //	{KEY_Q, GLFW_KEY_Q},
    //	{KEY_R, GLFW_KEY_R},
    //	{KEY_S, GLFW_KEY_S},
    //	{KEY_T, GLFW_KEY_T},
    //	{KEY_U, GLFW_KEY_U},
    //	{KEY_V, GLFW_KEY_V},
    //	{KEY_W, GLFW_KEY_W},
    //	{KEY_X, GLFW_KEY_X},
    //	{KEY_Y, GLFW_KEY_Y},
    //	{KEY_Z, GLFW_KEY_Z},
	{ KEY_LEFT_BRACKET, "[" },
	{ KEY_BACKSLASH, "\\" },
	{ KEY_RIGHT_BRACKET, "]" },
	{ KEY_GRAVE_ACCENT, "~" },
    //	{KEY_WORLD_1, GLFW_KEY_WORLD_1},
    //	{KEY_WORLD_2, GLFW_KEY_WORLD_2},
	{ KEY_ESCAPE, "Escape" },
	{ KEY_ENTER, "Enter" },
	{ KEY_TAB, "Tab" },
	{ KEY_BACKSPACE, "Backspace" },
	{ KEY_INSERT, "Insert" },
	{ KEY_DELETE, "Delete" },
	{ KEY_RIGHT, "Right" },
	{ KEY_LEFT, "Left" },
	{ KEY_DOWN, "Down" },
	{ KEY_UP, "Up" },
	{ KEY_PAGE_UP, "Page Up" },
	{ KEY_PAGE_DOWN, "Page Down" },
	{ KEY_HOME, "Home" },
	{ KEY_END, "End" },
	{ KEY_CAPS_LOCK, "Caps Lock" },
	{ KEY_SCROLL_LOCK, "Scroll Lock" },
	{ KEY_NUM_LOCK, "Num Lock" },
	{ KEY_PRINT_SCREEN, "Print" },
	{ KEY_PAUSE, "Pause" },
	{ KEY_F1, "F1" },
	{ KEY_F2, "F2" },
	{ KEY_F3, "F3" },
	{ KEY_F4, "F4" },
	{ KEY_F5, "F5" },
	{ KEY_F6, "F6" },
	{ KEY_F7, "F7" },
	{ KEY_F8, "F8" },
	{ KEY_F9, "F9" },
	{ KEY_F10, "F10" },
	{ KEY_F11, "F11" },
	{ KEY_F12, "F12" },
	{ KEY_F13, "F13" },
	{ KEY_F14, "F14" },
	{ KEY_F15, "F15" },
	{ KEY_F16, "F16" },
	{ KEY_F17, "F17" },
	{ KEY_F18, "F18" },
	{ KEY_F19, "F19" },
	{ KEY_F20, "F20" },
	{ KEY_F21, "F21" },
	{ KEY_F22, "F22" },
	{ KEY_F23, "F23" },
	{ KEY_F24, "F24" },
	{ KEY_F25, "F25" },
    //	{KEY_KP_0, GLFW_KEY_KP_0},
    //	{KEY_KP_1, GLFW_KEY_KP_1},
    //	{KEY_KP_2, GLFW_KEY_KP_2},
    //	{KEY_KP_3, GLFW_KEY_KP_3},
    //	{KEY_KP_4, GLFW_KEY_KP_4},
    //	{KEY_KP_5, GLFW_KEY_KP_5},
    //	{KEY_KP_6, GLFW_KEY_KP_6},
    //	{KEY_KP_7, GLFW_KEY_KP_7},
    //	{KEY_KP_8, GLFW_KEY_KP_8},
    //	{KEY_KP_9, GLFW_KEY_KP_9},
	{ KEY_KP_DECIMAL, "KP Decimal" },
	{ KEY_KP_DIVIDE, "KP Divide" },
	{ KEY_KP_MULTIPLY, "KP Multiply" },
	{ KEY_KP_SUBTRACT, "KP Subtract" },
	{ KEY_KP_ADD, "KP Add" },
	{ KEY_KP_ENTER, "KP Enter" },
	{ KEY_KP_EQUAL, "KP Equal" },
	{ KEY_LEFT_SHIFT, "Left Shift" },
	{ KEY_LEFT_CONTROL, "Left Control" },
	{ KEY_LEFT_ALT, "Left Alt" },
	{ KEY_LEFT_SUPER, "Left Super" },
	{ KEY_RIGHT_SHIFT, "Right Shift" },
	{ KEY_RIGHT_CONTROL, "Right Control" },
	{ KEY_RIGHT_ALT, "Right Alt" },
	{ KEY_RIGHT_SUPER, "Right Super" },
	{ KEY_MENU, "Menu" },
	{ KEY_LAST, "Last" },
	{ MOUSE_BUTTON_1, "Left Mouse" },
	{ MOUSE_BUTTON_2, "Right Mouse" },
	{ MOUSE_BUTTON_3, "Middle Mouse" },
	{ MOUSE_BUTTON_4, "Mouse 4" },
	{ MOUSE_BUTTON_5, "Mouse 5" },
	{ MOUSE_BUTTON_6, "Mouse 6" },
	{ MOUSE_BUTTON_7, "Mouse 7" },
	{ MOUSE_BUTTON_8, "Mouse 8" },
    //	{MOUSE_BUTTON_LAST, "Mouse Last"},
    //	{MOUSE_BUTTON_LEFT, "Mouse Left"},
    //	{MOUSE_BUTTON_RIGHT, "Mouse Right"},
    //	{MOUSE_BUTTON_MIDDLE, "Mouse Middle"},
	{ JOYSTICK_1, "Joystick 1" },
	{ JOYSTICK_2, "Joystick 2" },
	{ JOYSTICK_3, "Joystick 3" },
	{ JOYSTICK_4, "Joystick 4" },
	{ JOYSTICK_5, "Joystick 5" },
	{ JOYSTICK_6, "Joystick 6" },
	{ JOYSTICK_7, "Joystick 7" },
	{ JOYSTICK_8, "Joystick 8" },
	{ JOYSTICK_9, "Joystick 9" },
	{ JOYSTICK_10, "Joystick 10" },
	{ JOYSTICK_11, "Joystick 11" },
	{ JOYSTICK_12, "Joystick 12" },
	{ JOYSTICK_13, "Joystick 13" },
	{ JOYSTICK_14, "Joystick 14" },
	{ JOYSTICK_15, "Joystick 15" },
	{ JOYSTICK_16, "Joystick 16" },
//	{JOYSTICK_LAST, GLFW_JOYSTICK_LAST},
    };

    bool Input::isDown(Key key)
    {
	auto iter = m_keys.find(key);
	return iter != m_keys.end() && (iter->second == DOWN || iter->second == PRESSED);
    }

    bool Input::isUp(Key key)
    {
	auto iter = m_keys.find(key);
	return iter == m_keys.end() || iter->second == UP || iter->second == RELEASED;
    }

    bool Input::isPressed(Key key)
    {
	auto iter = m_keys.find(key);
	return iter != m_keys.end() && iter->second == PRESSED;
    }

    bool Input::isReleased(Key key)
    {
	auto iter = m_keys.find(key);
	return iter != m_keys.end() && iter->second == RELEASED;
    }

    Input::Key Input::charToKey(char character)
    {
	switch (character)
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
	    case '0':
	    case ')':
		return (KEY_0);
	    case '1':
	    case '!':
		return (KEY_1);
	    case '2':
	    case '@':
		return (KEY_2);
	    case '3':
	    case '#':
		return (KEY_3);
	    case '4':
	    case '$':
		return (KEY_4);
	    case '5':
	    case '%':
		return (KEY_5);
	    case '6':
	    case '^':
		return (KEY_6);
	    case '7':
	    case '&':
		return (KEY_7);
	    case '8':
	    case '*':
		return (KEY_8);
	    case '9':
	    case '(':
		return (KEY_9);
	    case '[':
	    case '{':
		return (KEY_LEFT_BRACKET);
	    case ']':
	    case '}':
		return (KEY_RIGHT_BRACKET);
	    case '´':
	    case '~':
		return (KEY_GRAVE_ACCENT);
	    case '-':
	    case '_':
		return (KEY_MINUS);
	    case '=':
	    case '+':
		return (KEY_EQUAL);
	    case '\\':
	    case '|':
		return (KEY_BACKSLASH);
	    case ';':
	    case ':':
		return (KEY_SEMICOLON);
	    case '\'':
	    case '"':
		return (KEY_APOSTROPHE);
	    case '/':
	    case '?':
		return (KEY_SLASH);
	    case '.':
	    case '>':
		return (KEY_PERIOD);
	    case ',':
	    case '<':
		return (KEY_COMMA);
	    case ' ':
		return (KEY_SPACE);
	    case '\n':
		return (KEY_ENTER);
	}
	return UNKNOWN;
    }

    char Input::keyToChar(Key key)
    {
	switch (key)
	{
	    case KEY_A:
		return ('A');
	    case KEY_B:
		return ('B');
	    case KEY_C:
		return ('C');
	    case KEY_D:
		return ('D');
	    case KEY_E:
		return ('E');
	    case KEY_F:
		return ('F');
	    case KEY_G:
		return ('G');
	    case KEY_H:
		return ('H');
	    case KEY_I:
		return ('I');
	    case KEY_J:
		return ('J');
	    case KEY_K:
		return ('K');
	    case KEY_L:
		return ('L');
	    case KEY_M:
		return ('M');
	    case KEY_N:
		return ('N');
	    case KEY_O:
		return ('O');
	    case KEY_P:
		return ('P');
	    case KEY_Q:
		return ('Q');
	    case KEY_R:
		return ('R');
	    case KEY_S:
		return ('S');
	    case KEY_T:
		return ('T');
	    case KEY_U:
		return ('U');
	    case KEY_V:
		return ('V');
	    case KEY_W:
		return ('W');
	    case KEY_X:
		return ('X');
	    case KEY_Y:
		return ('Y');
	    case KEY_Z:
		return ('Z');
	    case KEY_0:
	    case KEY_KP_0:
		return ('0');
	    case KEY_1:
	    case KEY_KP_1:
		return ('1');
	    case KEY_2:
	    case KEY_KP_2:
		return ('2');
	    case KEY_3:
	    case KEY_KP_3:
		return ('3');
	    case KEY_4:
	    case KEY_KP_4:
		return ('4');
	    case KEY_5:
	    case KEY_KP_5:
		return ('5');
	    case KEY_6:
	    case KEY_KP_6:
		return ('6');
	    case KEY_7:
	    case KEY_KP_7:
		return ('7');
	    case KEY_8:
	    case KEY_KP_8:
		return ('8');
	    case KEY_9:
	    case KEY_KP_9:
		return ('9');
	    case KEY_LEFT_BRACKET:
		return ('[');
	    case KEY_RIGHT_BRACKET:
		return ('[');
	    case KEY_GRAVE_ACCENT:
		return ('´');
	    case KEY_MINUS:
	    case KEY_KP_SUBTRACT:
		return ('-');
	    case KEY_EQUAL:
		return ('=');
	    case KEY_BACKSLASH:
		return ('\\');
	    case KEY_SEMICOLON:
		return (';');
	    case KEY_APOSTROPHE:
		return ('\'');
	    case KEY_SLASH:
	    case KEY_KP_DIVIDE:
		return ('/');
	    case KEY_PERIOD:
	    case KEY_KP_DECIMAL:
		return ('.');
	    case KEY_COMMA:
		return (',');
	    case KEY_KP_MULTIPLY:
		return ('*');
	    case KEY_KP_ADD:
		return ('+');
	    case KEY_SPACE:
		return (' ');
	    case KEY_ENTER:
		return ('\n');
	    default:
		return '\0';
	}
	return '\0';
    }

    std::string Input::keyToString(Key key)
    {
	std::string description;
	auto it = keyDescriptions.find(key);
	if (it != keyDescriptions.end())
	    description = it->second;
	else
	{
	    auto character = keyToChar(key);
	    if (character != '\0')
		description = character;
	}
	if(description.empty())
	    return "Unknown";
	else
	    return description;
    }

    void Input::update()
    {
	// Check key states and promote PRESSED and RELEASED keys to DOWN or UP
	for (auto iter = m_keys.begin(); iter != m_keys.end(); ++iter)
	{
	    if (iter->second == PRESSED)
		iter->second = DOWN;
	    else if (iter->second == RELEASED)
		iter->second = UP;
	}
    }

    void Input::updateKey(Key key, KeyState state)
    {
	auto pair = std::make_pair(key, state);
	m_keys.insert(pair);
    }
}
