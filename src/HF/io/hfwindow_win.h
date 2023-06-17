/* date = June 16th 2023 8:04 pm */

#ifndef HFWINDOW_WIN_H
#define HFWINDOW_WIN_H


//sets default values for a window
void _hf_win_window_defaults(hf_window* window);

b8 _hf_win_create_window(hf_window* window);
//b8 _hf_win_gl_load_context();
b8 _hf_win_destroy_window(hf_window* window);

b8 _hf_win_should_window_update(hf_window* window);
void _hf_win_update_window(hf_window* window);

void _hf_win_set_window_title(hf_window* window, const char* title);
void _hf_win_window_set_icon(hf_window* w, i32 icon_id);

//void hf_window_set_ups(hf_window* window, u32 ups);
//void hf_window_remove_ups_constraint(hf_window* window);
#ifdef _WIN32
LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

// NOTE(salmoncatt): input handling and callbacks

// NOTE(salmoncatt):     window handle      [callback function]         [keycode] [key up or down]
//void hf_window_set_key_callback(hf_window* window, void (*hf_key_callback)(hf_window*, u32, u32));

// NOTE(salmoncatt): vsync
void _hf_win_swap_interval(hf_window* window, b8 vsync);

void _hf_win_window_set_cursor_pos(hf_window* window, v2f pos);


#endif //HFWINDOW_WIN_H
