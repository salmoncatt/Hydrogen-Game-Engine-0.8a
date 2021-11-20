/* date = August 23rd 2021 8:08 pm */

#ifndef INPUT_H
#define INPUT_H

#define HF_KEY_LAST 348

#include "../core/hfapp.h"
//#include "../datatypes/hfvector.h"

extern b8 hf_input_keys[HF_KEY_LAST];
extern b8 hf_input_keys_down[HF_KEY_LAST];

void hf_input_init();

b8 hf_input_get_key(u32 key);

b8 hf_input_get_key_down(u32 key);

b8 hf_input_get_key_up();

void hf_input_set_clipboard(const char* text);

b8 hf_input_get_mouse_button();

b8 hf_input_get_mouse_button_down();

b8 hf_input_get_mouse_button_up();

void hf_input_destroy();

// From glfw3.h
#define HF_KEY_SPACE VK_SPACE
#define HF_KEY_APOSTROPHE VK_7 /* ' */
#define HF_KEY_COMMA VK_OEM_COMMA /* , */
#define HF_KEY_MINUS VK_OEM_MINUS /* - */
#define HF_KEY_PERIOD VK_OEM_PERIOD /* . */
#define HF_KEY_SLASH VK_OEM_2 /* / */

#define HF_KEY_D0 48 /* 0 */
#define HF_KEY_D1 49 /* 1 */
#define HF_KEY_D2 50 /* 2 */
#define HF_KEY_D3 51 /* 3 */
#define HF_KEY_D4 52 /* 4 */
#define HF_KEY_D5 53 /* 5 */
#define HF_KEY_D6 54 /* 6 */
#define HF_KEY_D7 55 /* 7 */
#define HF_KEY_D8 56 /* 8 */
#define HF_KEY_D9 57 /* 9 */

#define HF_KEY_SEMICOLON 59 /* ; */
#define HF_KEY_EQUAL 60  /* = */ //bad

#define HF_KEY_A 65
#define HF_KEY_B 66
#define HF_KEY_C 67
#define HF_KEY_D 68
#define HF_KEY_E 69
#define HF_KEY_F 70
#define HF_KEY_G 71
#define HF_KEY_H 72
#define HF_KEY_I 73
#define HF_KEY_J 74
#define HF_KEY_K 75
#define HF_KEY_L 76
#define HF_KEY_M 77
#define HF_KEY_N 78
#define HF_KEY_O 79
#define HF_KEY_P 80
#define HF_KEY_Q 81
#define HF_KEY_R 82
#define HF_KEY_S 83
#define HF_KEY_T 84
#define HF_KEY_U 85
#define HF_KEY_V 86
#define HF_KEY_W 87
#define HF_KEY_X 88
#define HF_KEY_Y 89
#define HF_KEY_Z 90

#define HF_KEY_LEFT_BRACKET VK_OEM_4   /* [ */
#define HF_KEY_BACKSLASH VK_OEM_5   /* \ */
#define HF_KEY_RIGHT_BRACKET VK_OEM_6   /* ] */
#define HF_KEY_GRAVE_ACCENT VK_OEM_3  /* ` */  //bad

//#define HF_KEY_WORLD_1 161 /* non-US #1 */
//#define HF_KEY_WORLD_2 162 /* non-US #2 */

/* Function keys */
#define HF_KEY_ESCAPE VK_ESCAPE
#define HF_KEY_ENTER VK_RETURN
#define HF_KEY_TAB VK_TAB
#define HF_KEY_BACKSPACE VK_BACK
#define HF_KEY_INSERT VK_INSERT //bad
#define HF_KEY_DELETE VK_DELETE
#define HF_KEY_RIGHT VK_RIGHT
#define HF_KEY_LEFT VK_LEFT
#define HF_KEY_DOWN VK_DOWN
#define HF_KEY_UP VK_UP
#define HF_KEY_PAGE_UP VK_PRIOR
#define HF_KEY_PAGE_DOWN VK_NEXT
#define HF_KEY_HOME VK_HOME
#define HF_KEY_END VK_END
#define HF_KEY_CAPS_LOCK VK_CAPITAL
#define HF_KEY_SCROLL_LOCK VK_SCROLL
#define HF_KEY_NUM_LOCK VK_NUMLOCK
#define HF_KEY_PRINT_SCREEN VK_SNAPSHOT
#define HF_KEY_PAUSE VK_PAUSE
#define HF_KEY_F1 VK_F1
#define HF_KEY_F2 VK_F2
#define HF_KEY_F3 VK_F3
#define HF_KEY_F4 VK_F4
#define HF_KEY_F5 VK_F5
#define HF_KEY_F6 VK_F6
#define HF_KEY_F7 VK_F7
#define HF_KEY_F8 VK_F8
#define HF_KEY_F9 VK_F9
#define HF_KEY_F10 VK_F10
#define HF_KEY_F11 VK_F11
#define HF_KEY_F12 VK_F12
#define HF_KEY_F13 VK_F13
#define HF_KEY_F14 VK_F14
#define HF_KEY_F15 VK_F15
#define HF_KEY_F16 VK_F16
#define HF_KEY_F17 VK_F17
#define HF_KEY_F18 VK_F18
#define HF_KEY_F19 VK_F19
#define HF_KEY_F20 VK_F20
#define HF_KEY_F21 VK_F21
#define HF_KEY_F22 VK_F22
#define HF_KEY_F23 VK_F23
#define HF_KEY_F24 VK_F24
#define HF_KEY_F25 VK_F25

/* Keypad */
#define HF_KEY_KP_0 VK_NUMPAD0
#define HF_KEY_KP_1 VK_NUMPAD1
#define HF_KEY_KP_2 VK_NUMPAD2
#define HF_KEY_KP_3 VK_NUMPAD3
#define HF_KEY_KP_4 VK_NUMPAD4
#define HF_KEY_KP_5 VK_NUMPAD5
#define HF_KEY_KP_6 VK_NUMPAD6
#define HF_KEY_KP_7 VK_NUMPAD7
#define HF_KEY_KP_8 VK_NUMPAD8
#define HF_KEY_KP_9 VK_NUMPAD9
#define HF_KEY_KP_DECIMAL VK_DECIMAL
#define HF_KEY_KP_DIVIDE VK_DIVIDE
#define HF_KEY_KP_MULTIPLY VK_MULTIPLY
#define HF_KEY_KP_SUBTRACT VK_SUBRACT
#define HF_KEY_KP_ADD VK_ADD
//#define HF_KEY_KP_ENTER VK_NUMPADENTER
//#define HF_KEY_KP_EQUAL 336

#define HF_KEY_LEFT_SHIFT VK_LSHIFT
#define HF_KEY_LEFT_CONTROL VK_LCONTROL
#define HF_KEY_LEFT_ALT VK_LMENU
//#define HF_KEY_LEFT_SUPER 343
#define HF_KEY_RIGHT_SHIFT VK_RSHIFT
#define HF_KEY_RIGHT_CONTROL VK_RCONTROL
#define HF_KEY_RIGHT_ALT VK_RMENU
//#define HF_KEY_RIGHT_SUPER 347
#define HF_KEY_MENU VK_MENU

#endif //INPUT_H
