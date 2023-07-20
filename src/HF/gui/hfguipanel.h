/* date = June 6th 2022 10:33 pm */

#ifndef HFGUIPANEL_H
#define HFGUIPANEL_H

#include "../text/hf_font.h"
#include "hf_gui_button.h"
#include "hf_gui_image.h"
#include "hf_gui_progress_bar.h"
#include "hf_gui_rectangle.h"
#include "hf_gui_text.h"
#include "hf_gui_slider.h"


typedef struct hf_gui_panel{
    
    v4f color, title_bar_color;
    i32 x, y;
    u32 w, h, title_bar_height;
    b8 selected; //for dragging
    b8 sizing; //for sizing
    hf_font* font;
    u32 element_spacing; //distance between gui elements (10 pixels is default)
    
    b8 clicked_last_frame; //for making buttons go dark when clicked
    
    v2f cursor_pos;
    
}hf_gui_panel;

extern hf_gui_panel* hf_current_gui_panel;

#define HF_TITLE_BAR 0x01
#define HF_SIZEABLE 0x02
#define HF_MOVEABLE 0x04

b8 hf_gui_panel_begin(hf_gui_panel* panel, char* title, u32 flags);
b8 hf_gui_panel_end();

hf_gui_panel hf_gui_panel_defaults();

v2f hf_gui_get_cursor_pos();
void hf_gui_set_cursor_pos(v2f in);






#endif //HFGUIPANEL_H
