/* date = August 23rd 2021 8:08 pm */

#ifndef INPUT_H
#define INPUT_H

//#define HF_KEY_LAST 348
#define HF_KEY_LAST 348000

#define HF_MOUSE_BUTTON_LAST 10

#include "../core/hfapp.h"
#include "../math/hfmath.h"
//#include "../datatypes/hfvector.h"

extern b8 hf_input_keys[HF_KEY_LAST];
extern b8 hf_input_keys_old[HF_KEY_LAST];

extern b8 hf_input_buttons[HF_MOUSE_BUTTON_LAST];
extern b8 hf_input_buttons_old[HF_MOUSE_BUTTON_LAST];

extern b8 hf_input_cursor_visibility;
extern b8 hf_input_cursor_visibility_last;

extern v2f hf_input_cursor_pos;
extern v2f hf_input_cursor_pos_last;
extern v2f hf_input_cursor_movement;
extern v2f hf_input_center;

void hf_input_update(hf_app* app);

b8 hf_input_get_key(u32 key);
b8 hf_input_get_key_down(u32 key);
b8 hf_input_get_key_up(u32 key);

void hf_input_set_clipboard(const char* text);

b8 hf_input_get_mouse_button(u32 button);
b8 hf_input_get_mouse_button_down(u32 button);
b8 hf_input_get_mouse_button_up(u32 button);

v2f hf_input_get_mouse_movement();

void hf_input_show_cursor(b8 visibility);
void hf_input_toggle_cursor();
b8 hf_input_get_cursor_visibility();

void hf_input_destroy();

#ifdef _WIN32

#define HF_MOUSE_BUTTON_0 0
#define HF_MOUSE_BUTTON_1 2
#define HF_MOUSE_BUTTON_2 1
#define HF_MOUSE_BUTTON_3 3
#define HF_MOUSE_BUTTON_4 4
#define HF_MOUSE_BUTTON_5 5
#define HF_MOUSE_BUTTON_6 6
#define HF_MOUSE_BUTTON_7 7

#define HF_MOUSE_BUTTON_LEFT HF_MOUSE_BUTTON_0
#define HF_MOUSE_BUTTON_RIGHT HF_MOUSE_BUTTON_1
#define HF_MOUSE_BUTTON_MIDDLE HF_MOUSE_BUTTON_2


#define HF_KEY_ESCAPE 0x01
#define HF_KEY_1 0x02
#define HF_KEY_2 0x03
#define HF_KEY_3 0x04
#define HF_KEY_4 0x05
#define HF_KEY_5 0x06
#define HF_KEY_6 0x07
#define HF_KEY_7 0x08
#define HF_KEY_8 0x09
#define HF_KEY_9 0x0A
#define HF_KEY_0 0x0B
#define HF_KEY_MINUS 0x0C
#define HF_KEY_EQUALS 0x0D
#define HF_KEY_BACKSPACE 0x0E
#define HF_KEY_TAB 0x0F
#define HF_KEY_Q 0x10
#define HF_KEY_W 0x11
#define HF_KEY_E 0x12
#define HF_KEY_R 0x13
#define HF_KEY_T 0x14
#define HF_KEY_Y 0x15
#define HF_KEY_U 0x16
#define HF_KEY_I 0x17
#define HF_KEY_O 0x18
#define HF_KEY_P 0x19
#define HF_KEY_LEFT_BRACKET 0x1A
#define HF_KEY_RIGHT_BRACKET 0x1B
#define HF_KEY_ENTER 0x1C
#define HF_KEY_LEFT_CONTROL 0x1D
#define HF_KEY_A 0x1E
#define HF_KEY_S 0x1F
#define HF_KEY_D 0x20
#define HF_KEY_F 0x21
#define HF_KEY_G 0x22
#define HF_KEY_H 0x23
#define HF_KEY_J 0x24
#define HF_KEY_K 0x25
#define HF_KEY_L 0x26
#define HF_KEY_SEMICOLON 0x27
#define HF_KEY_APOSTROPHE 0x28
#define HF_KEY_GRAVE 0x29 // `
#define HF_KEY_LEFT_SHIFT 0x2A
#define HF_KEY_BACKSLASH 0x2B
#define HF_KEY_Z 0x2C
#define HF_KEY_X 0x2D
#define HF_KEY_C 0x2E
#define HF_KEY_V 0x2F
#define HF_KEY_B 0x30
#define HF_KEY_N 0x31
#define HF_KEY_M 0x32
#define HF_KEY_COMMA 0x33
#define HF_KEY_PERIOD 0x34
#define HF_KEY_SLASH 0x35
#define HF_KEY_RIGHT_SHIFT 0x36
#define HF_KEY_NP_MULTIPLY 0x37
#define HF_KEY_LEFT_ALT 0x38
#define HF_KEY_SPACE 0x39
#define HF_KEY_CAPS_LOCK 0x3A
#define HF_KEY_F1 0x3B
#define HF_KEY_F2 0x3C
#define HF_KEY_F3 0x3D
#define HF_KEY_F4 0x3E
#define HF_KEY_F5 0x3F
#define HF_KEY_F6 0x40
#define HF_KEY_F7 0x41
#define HF_KEY_F8 0x42
#define HF_KEY_F9 0x43
#define HF_KEY_F10 0x44
#define HF_KEY_NUM_LOCK 0x45
#define HF_KEY_SCROLL_LOCK 0x46
#define HF_KEY_NP_7 0x47
#define HF_KEY_NP_8 0x48
#define HF_KEY_NP_9 0x49
#define HF_KEY_NP_minus 0x4A
#define HF_KEY_NP_4 0x4B
#define HF_KEY_NP_5 0x4C
#define HF_KEY_NP_6 0x4D
#define HF_KEY_NP_plus 0x4E
#define HF_KEY_NP_1 0x4F
#define HF_KEY_NP_2 0x50
#define HF_KEY_NP_3 0x51
#define HF_KEY_NP_0 0x52
#define HF_KEY_NP_period 0x53
#define HF_KEY_ALT_PRINT_SCREEN 0x54 /* Alt + print screen. MapVirtualKeyEx( VK_SNAPSHOT, MAPVK_VK_TO_VSC_EX, 0 ) returns scancode 0x54. */
#define HF_KEY_BRACKET_ANGLE 0x56 /* Key between the left shift and Z. */
#define HF_KEY_F11 0x57
#define HF_KEY_F12 0x58
#define HF_KEY_OEM_1 0x5a /* VK_OEM_WSCTRL */
#define HF_KEY_OEM_2 0x5b /* VK_OEM_FINISH */
#define HF_KEY_OEM_3 0x5c /* VK_OEM_JUMP */
#define HF_KEY_ERASE_EOF 0x5d
#define HF_KEY_OEM_4 0x5e /* VK_OEM_BACKTAB */
#define HF_KEY_OEM_5 0x5f /* VK_OEM_AUTO */
#define HF_KEY_ZOOM 0x62
#define HF_KEY_HELP 0x63
#define HF_KEY_F13 0x64
#define HF_KEY_F14 0x65
#define HF_KEY_F15 0x66
#define HF_KEY_F16 0x67
#define HF_KEY_F17 0x68
#define HF_KEY_F18 0x69
#define HF_KEY_F19 0x6a
#define HF_KEY_F20 0x6b
#define HF_KEY_F21 0x6c
#define HF_KEY_F22 0x6d
#define HF_KEY_F23 0x6e
#define HF_KEY_OEM_6 0x6f /* VK_OEM_PA3 */
#define HF_KEY_KATAKANA 0x70
#define HF_KEY_OEM_7 0x71 /* VK_OEM_RESET */
#define HF_KEY_F24 0x76
#define HF_KEY_SBCSCHAR 0x77
#define HF_KEY_CONVERT 0x79
#define HF_KEY_NONCONVERT 0x7B /* VK_OEM_PA1 */

#define HF_KEY_MEDIA_PREVIOUS 0xE010
#define HF_KEY_MEDIA_NEXT 0xE019
#define HF_KEY_NP_ENTER 0xE01C
#define HF_KEY_RIGHT_CONTROL 0xE01D
#define HF_KEY_VOLUME_MUTE 0xE020
#define HF_KEY_LAUNCH_APP2 0xE021
#define HF_KEY_MEDIA_PLAY 0xE022
#define HF_KEY_MEDIA_STOP 0xE024
#define HF_KEY_VOLUME_DOWN 0xE02E
#define HF_KEY_VOLUME_UP 0xE030
#define HF_KEY_BROWSER_HOME 0xE032
#define HF_KEY_NP_DIVIDE 0xE035
#define HF_KEY_PRINT_SCREEN 0xE037
/*
#define HF_KEY_printScreen:
#define HF_KEY_ake: 0xE02A 0xE037
#define HF_KEY_reak: 0xE0B7 0xE0AA
#define HF_KEY_apVirtualKeyEx( VK_SNAPSHOT, MAPVK_VK_TO_VSC_EX, 0 ) returns scancode 0x54;
#define HF_KEY_here is no VK_KEYDOWN with VK_SNAPSHOT.
*/
#define HF_KEY_RIGHT_ALT 0xE038
#define HF_KEY_CANCEL 0xE046 /* CTRL + Pause */
#define HF_KEY_HOME 0xE047
#define HF_KEY_UP 0xE048
#define HF_KEY_PAGE_UP 0xE049
#define HF_KEY_LEFT 0xE04B
#define HF_KEY_RIGHT 0xE04D
#define HF_KEY_END 0xE04F
#define HF_KEY_DOWN 0xE050
#define HF_KEY_PAGE_DOWN 0xE051
#define HF_KEY_INSERT 0xE052
#define HF_KEY_DELETE 0xE053
#define HF_KEY_META_LEFT 0xE05B
#define HF_KEY_META_RIGHT 0xE05C
#define HF_KEY_APPLICATION 0xE05D
#define HF_KEY_POWER 0xE05E
#define HF_KEY_SLEEP 0xE05F
#define HF_KEY_WAKE 0xE063
#define HF_KEY_BROWSER_SEARCH 0xE065
#define HF_KEY_BROWSER_FAVORITES 0xE066
#define HF_KEY_BROWSER_REFRESH 0xE067
#define HF_KEY_BROWSER_STOP 0xE068
#define HF_KEY_BROWSER_FORWARD 0xE069
#define HF_KEY_BROWSER_BACK 0xE06A
#define HF_KEY_LAUNCH_APP1 0xE06B
#define HF_KEY_LAUNCH_EMAIL 0xE06C
#define HF_KEY_LAUNCH_MEDIA 0xE06D

#define HF_KEY_PAUSE 0xE11D45

#elif defined(__linux__)

#define HF_MOUSE_BUTTON_LEFT 1
#define HF_MOUSE_BUTTON_RIGHT 3
#define HF_MOUSE_BUTTON_MIDDLE 2



#define HF_KEY_ESCAPE XK_Escape
#define HF_KEY_1 XK_1
#define HF_KEY_2 XK_2
#define HF_KEY_3 XK_3
#define HF_KEY_4 XK_4
#define HF_KEY_5 XK_5
#define HF_KEY_6 XK_6
#define HF_KEY_7 XK_7
#define HF_KEY_8 XK_8
#define HF_KEY_9 XK_9
#define HF_KEY_0 XK_0
#define HF_KEY_MINUS XK_minus
#define HF_KEY_EQUALS XK_equal
#define HF_KEY_BACKSPACE XK_backspace
#define HF_KEY_TAB XK_tab
#define HF_KEY_Q XK_q
#define HF_KEY_W XK_w
#define HF_KEY_E XK_e
#define HF_KEY_R XK_r
#define HF_KEY_T XK_t
#define HF_KEY_Y XK_y
#define HF_KEY_U XK_u
#define HF_KEY_I XK_i
#define HF_KEY_O XK_o
#define HF_KEY_P XK_p
//#define HF_KEY_LEFT_BRACKET 0x1A
//#define HF_KEY_RIGHT_BRACKET 0x1B
//#define HF_KEY_ENTER 0x1C
#define HF_KEY_LEFT_CONTROL XK_Control_L
#define HF_KEY_A XK_a
#define HF_KEY_S XK_s
#define HF_KEY_D XK_d
#define HF_KEY_F XK_f
#define HF_KEY_G XK_g
#define HF_KEY_H XK_h
#define HF_KEY_J XK_j
#define HF_KEY_K XK_k
#define HF_KEY_L XK_l
//#define HF_KEY_SEMICOLON 0x27
//#define HF_KEY_APOSTROPHE 0x28
//#define HF_KEY_GRAVE 0x29 // `
#define HF_KEY_LEFT_SHIFT XK_Shift_L
#define HF_KEY_BACKSLASH XK_backslash
#define HF_KEY_Z XK_z
#define HF_KEY_X XK_x
#define HF_KEY_C XK_c
#define HF_KEY_V XK_v
#define HF_KEY_B XK_b
#define HF_KEY_N XK_n
#define HF_KEY_M XK_m




#define HF_KEY_SPACE XK_space

#endif




/*
sc_pause:
- make: 0xE11D 45 0xE19D C5
- make in raw input: 0xE11D 0x45
- break: none
- No repeat when you hold the key down
- There are no break so I don't know how the key down/up is expected to work. Raw input sends "keydown" and "keyup" messages, and it appears that the keyup message is sent directly after the keydown message (you can't hold the key down) so depending on when GetMessage or PeekMessage will return messages, you may get both a keydown and keyup message "at the same time". If you use VK messages most of the time you only get keydown messages, but some times you get keyup messages too.
- when pressed at the same time as one or both control keys, generates a 0xE046 (sc_cancel) and the string for that scancode is "break".
*/



// From glfw3.h
//#define HF_KEY_SPACE VK_SPACE
//#define HF_KEY_APOSTROPHE VK_7 /* ' */
//#define HF_KEY_COMMA VK_OEM_COMMA /* , */
//#define HF_KEY_MINUS VK_OEM_MINUS /* - */
//#define HF_KEY_PERIOD VK_OEM_PERIOD /* . */
//#define HF_KEY_SLASH VK_OEM_2 /* / */

//#define HF_KEY_D0 48 /* 0 */
//#define HF_KEY_D1 49 /* 1 */
//#define HF_KEY_D2 50 /* 2 */
//#define HF_KEY_D3 51 /* 3 */
//#define HF_KEY_D4 52 /* 4 */
//#define HF_KEY_D5 53 /* 5 */
//#define HF_KEY_D6 54 /* 6 */
//#define HF_KEY_D7 55 /* 7 */
//#define HF_KEY_D8 56 /* 8 */
//#define HF_KEY_D9 57 /* 9 */

//#define HF_KEY_SEMICOLON 59 /* ; */
//#define HF_KEY_EQUAL 60  /* = */ //bad

/* 
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
 */

//#define HF_KEY_LEFT_BRACKET VK_OEM_4   /* [ */
//#define HF_KEY_BACKSLASH VK_OEM_5   /* \ */
//#define HF_KEY_RIGHT_BRACKET VK_OEM_6   /* ] */
//#define HF_KEY_GRAVE_ACCENT VK_OEM_3  /* ` */  //bad

//#define HF_KEY_WORLD_1 161 /* non-US #1 */
//#define HF_KEY_WORLD_2 162 /* non-US #2 */

/* Function keys */
/* 
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
 */

/* Keypad */
/* 
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
 */
//#define HF_KEY_KP_ENTER VK_NUMPADENTER
//#define HF_KEY_KP_EQUAL 336

//#define HF_KEY_LEFT_SHIFT VK_LSHIFT
//#define HF_KEY_SHIFT 400
//#define HF_KEY_LEFT_CONTROL VK_LCONTROL
//#define HF_KEY_CONTROL 401
//#define HF_KEY_LEFT_ALT VK_LMENU
//#define HF_KEY_ALT 402
/* 
//#define HF_KEY_LEFT_SUPER 343
#define HF_KEY_RIGHT_SHIFT VK_RSHIFT
#define HF_KEY_RIGHT_CONTROL VK_RCONTROL
#define HF_KEY_RIGHT_ALT VK_RMENU
//#define HF_KEY_RIGHT_SUPER 347
#define HF_KEY_MENU VK_MENU
 */


#endif //INPUT_H
