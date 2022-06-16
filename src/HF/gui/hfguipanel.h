/* date = June 6th 2022 10:33 pm */

#ifndef HFGUIPANEL_H
#define HFGUIPANEL_H

typedef struct hf_gui_panel{
    
    v4f color;
    u32 x, y, w, h;
    b8 selected; //for dragging
    
}hf_gui_panel;

extern hf_gui_panel* hf_current_gui_panel;

#define HF_TITLE_BAR 0x01
#define HF_SIZEABLE 0x02
#define HF_MOVEABLE 0x04

b8 hf_gui_panel_begin(hf_gui_panel* panel, u32 x, u32 y, u32 w, u32 h, u32 flags, u32 title_bar_height);
b8 hf_gui_panel_end();

b8 hf_gui_button(u32 x, u32 y, u32 w, u32 h, v4f color);

#endif //HFGUIPANEL_H
