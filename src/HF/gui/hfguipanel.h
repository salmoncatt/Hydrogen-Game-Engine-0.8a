/* date = June 6th 2022 10:33 pm */

#ifndef HFGUIPANEL_H
#define HFGUIPANEL_H

#include "../text/hf_font.h"

typedef struct hf_gui_panel{
    
    v4f color, title_bar_color;
    i32 x, y;
    u32 w, h;
    b8 selected; //for dragging
    hf_font* font;
    u32 element_spacing; //distance between gui elements (10 pixels is default)
    
    b8 clicked_last_frame; //for making buttons go dark when clicked
    
    v2f cursor_pos;
    
}hf_gui_panel;

extern hf_gui_panel* hf_current_gui_panel;

#define HF_TITLE_BAR 0x01
#define HF_SIZEABLE 0x02
#define HF_MOVEABLE 0x04

b8 hf_gui_panel_begin(hf_gui_panel* panel, char* text, u32 x, u32 y, u32 w, u32 h, u32 flags, u32 title_bar_height);
b8 hf_gui_panel_end();
v2f hf_gui_get_cursor_pos();
void hf_gui_set_cursor_pos(v2f in);

b8 hf_gui_button(u32 w, u32 h, v4f color);
b8 hf_gui_button_text(u32 w, u32 h, v4f color, char* text);

void hf_gui_progress_bar(u32 w, u32 h, u32 percent, v4f foreground_color, v4f background_color);
void hf_gui_progress_bar_text(u32 w, u32 h, u32 percent, v4f foreground_color, v4f background_color, char* text);

/* 
b8 hf_gui_button_smart(u32 w, u32 h, v4f color, char* text, b8* pressed_last);
b8 hf_gui_button_text_simple(u32 w, u32 h, v4f color, char* text);
b8 hf_gui_button_text_advanced(u32 w, u32 h, v4f color, char* normal, char* hovered, char* pressed);
 */
void hf_gui_rect(u32 w, u32 h, v4f color);
void hf_gui_image(u32 w, u32 h, hf_texture* texture);

//anchoring styles
#define HF_TEXT_CENTERED 0x01
#define HF_TEXT_BOTTOM 0x02
#define HF_TEXT_DONT_USE_SPACING 0x04 // not using this lets you specify exactly where to render text with set_cursor_pos without worrying about element spacing

void hf_gui_text(char* text, hf_font* font, u32 flags);
void hf_gui_title_text(char* text, hf_font* font, i32 x, i32 y);
void hf_gui_text_advanced(u32 max_w, u32 height, b8 centered, char* text, hf_font* font, u32 render_type);



#endif //HFGUIPANEL_H
