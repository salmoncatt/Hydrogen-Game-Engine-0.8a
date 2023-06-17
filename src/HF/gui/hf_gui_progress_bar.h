/* date = June 17th 2023 0:03 am */

#ifndef HF_GUI_PROGRESS_BAR_H
#define HF_GUI_PROGRESS_BAR_H


void hf_gui_progress_bar(u32 w, u32 h, u32 percent, v4f foreground_color, v4f background_color);
void hf_gui_progress_bar_text(u32 w, u32 h, u32 percent, v4f foreground_color, v4f background_color, char* text);

#endif //HF_GUI_PROGRESS_BAR_H
