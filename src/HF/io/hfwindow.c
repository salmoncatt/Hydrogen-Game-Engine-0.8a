#include "hfwindow.h"
#include "hfinput.h"
#include "hfwindow_linux.h"
#include "hfwindow_win.h"


void hf_window_defaults(hf_window* window){
#ifdef _WIN32
    _hf_win_window_defaults(window);
#elif defined(__linux__)
    _hf_linux_window_defaults(window);
#endif
}

b8 hf_create_window(hf_window* window){
#ifdef _WIN32
    _hf_win_create_window(window);
#elif defined(__linux__)
    _hf_linux_create_window(window);
#endif
}

b8 hf_gl_load_context(){
#ifdef _WIN32
    _hf_win_gl_load_context();
    //#elif defined(__linux__)
    //_hf_linux_gl_load_context();
#endif
}

b8 hf_destroy_window(hf_window* window){
#ifdef _WIN32
    _hf_win_destroy_window(window);
#elif defined(__linux__)
    _hf_linux_destroy_window(window);
#endif
}

b8 hf_should_window_update(hf_window* window){
#ifdef _WIN32
    _hf_win_should_window_update(window);
#elif defined(__linux__)
    _hf_linux_should_window_update(window);
#endif
}

void hf_update_window(hf_window* window){
#ifdef _WIN32
    _hf_win_update_window(window);
#elif defined(__linux__)
    _hf_linux_update_window(window);
#endif
}

void hf_set_window_title(hf_window* window, const char* title){
#ifdef _WIN32
    _hf_win_set_window_title(window, title);
#elif defined(__linux__)
    _hf_linux_set_window_title(window, title);
#endif
}

void hf_window_set_icon(hf_window* w, i32 icon_id){
#ifdef _WIN32
    _hf_win_window_set_icon(w, icon_id);
#elif defined(__linux__)
    _hf_linux_window_set_icon(w, icon_id);
#endif
}

// NOTE(salmoncatt): vsync
void hf_swap_interval(hf_window* window, b8 vsync){
#ifdef _WIN32
    _hf_win_swap_interval(window, vsync);
#elif defined(__linux__)
    _hf_linux_swap_interval(window, vsync);
#endif
}

void hf_window_set_cursor_pos(hf_window* window, v2f pos){
#ifdef _WIN32
    _hf_win_window_set_cursor_pos(window, pos);
#elif defined(__linux__)
    _hf_linux_window_set_cursor_pos(window, pos);
#endif
}