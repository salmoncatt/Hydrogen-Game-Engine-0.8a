/* date = June 17th 2023 0:03 am */

#ifndef HF_GUI_TEXT_H
#define HF_GUI_TEXT_H


//anchoring styles
#define HF_TEXT_CENTERED 0x01
#define HF_TEXT_BOTTOM 0x02
#define HF_TEXT_DONT_USE_SPACING 0x04 // using this lets you specify exactly where to render text with set_cursor_pos without worrying about element spacing


void hf_gui_text(char* text, u32 flags);



//void hf_gui_screen_text(char* text, hf_font* font, u32 flags); //TODO



void hf_gui_title_text(char* text, hf_font* font, i32 x, i32 y);
void hf_gui_text_advanced(u32 max_w, u32 height, b8 centered, char* text, hf_font* font, u32 render_type);


#endif //HF_GUI_TEXT_H
