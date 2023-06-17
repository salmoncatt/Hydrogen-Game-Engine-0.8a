#include "hfguipanel.h"

void hf_gui_progress_bar(u32 w, u32 h, u32 percent, v4f foreground_color, v4f background_color){
    hf_current_gui_panel->cursor_pos.y += hf_current_gui_panel->element_spacing;
    
    // NOTE(salmoncatt): screen space (pixel) coords
    u32 ss_x = hf_current_gui_panel->cursor_pos.x + hf_current_gui_panel->x;
    u32 ss_y = hf_current_gui_panel->cursor_pos.y + hf_current_gui_panel->y;
    
    hf_current_gui_panel->cursor_pos.y += h;
    
    hf_render_rect(ss_x, ss_y, w, h, background_color);
    hf_render_rect(ss_x + 1, ss_y + 1, (u32)((f32)(w - 2) * ((f32)percent / 100)), h - 2, foreground_color);
}

void hf_gui_progress_bar_text(u32 w, u32 h, u32 percent, v4f foreground_color, v4f background_color, char* text){
    if(text == NULL)
        return;
    hf_gui_progress_bar(w, h, percent, foreground_color, background_color);
    
    // NOTE(salmoncatt): WHY THE FUCK DOES LEAVING X & Y AS THEIR OWN VARIABLES AND NOT PLUGGING THE EQUATIONS DIRECTLY INTO THE FUNCTION FIX THE ISSUE OF THE CAMERA INPUT RANDOMLY REVERSING AFTER ABOUT 3 SECONDS
    float x = (hf_current_gui_panel->cursor_pos.x + (w / 2)) - (hf_font_get_bitmap_length(hf_current_gui_panel->font, text) / 2);
    float y = (hf_current_gui_panel->cursor_pos.y - (h / 2)) + ((f32)(hf_current_gui_panel->font->glyph_height) / 2);
    hf_gui_title_text(text, hf_current_gui_panel->font, x, y);
}