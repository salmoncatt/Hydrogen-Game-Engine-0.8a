/* date = June 17th 2023 0:02 am */

#ifndef HF_GUI_BUTTON_H
#define HF_GUI_BUTTON_H

/* 
b8 hf_gui_button_smart(u32 w, u32 h, v4f color, char* text, b8* pressed_last);
b8 hf_gui_button_text_simple(u32 w, u32 h, v4f color, char* text);
b8 hf_gui_button_text_advanced(u32 w, u32 h, v4f color, char* normal, char* hovered, char* pressed);
 */


b8 hf_gui_button(u32 w, u32 h, v4f color);
b8 hf_gui_button_text(u32 w, u32 h, v4f color, char* text);

#endif //HF_GUI_BUTTON_H
