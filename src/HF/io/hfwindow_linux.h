/* date = March 23rd 2023 7:03 pm */

#ifndef HFWINDOW_LINUX_H
#define HFWINDOW_LINUX_H

void _hf_linux_window_defaults(hf_window* window);

b8 _hf_linux_create_window(hf_window* window);
b8 _hf_linux_gl_load_context();
b8 _hf_linux_destroy_window(hf_window* window);

b8 _hf_linux_should_window_update(hf_window* window);
void _hf_linux_update_window(hf_window* window);

void _hf_linux_set_window_title(hf_window* window, const char* title);
void _hf_linux_window_set_icon(hf_window* w, i32 icon_id);

// NOTE(salmoncatt): vsync
void _hf_linux_swap_interval(hf_window* window, b8 vsync);

void _hf_linux_window_set_cursor_pos(hf_window* window, v2f pos);


#endif //HFWINDOW_LINUX_H
