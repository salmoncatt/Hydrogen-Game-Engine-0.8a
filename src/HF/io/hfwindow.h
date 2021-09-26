/* date = August 15th 2021 8:14 pm */

#ifndef _WINDOW_H
#define _WINDOW_H

#include "../math/hfmath.h"
//#include <windows.h>

// NOTE(salmoncatt): do platform specific functions like foo (calls wfoo or xfoo)

//https://www.cprogramming.com/tutorial/opengl_projections.html the god send of a website



// TODO(salmoncatt): get this to not error in console pls
//typedef (*hf_key_callback)(hf_window*, u32, u32);

// TODO(salmoncatt): come up with a better solution for callbacks than (typedef struct hf_def_window_struct)
typedef struct hf_window{
    u32 width;
    u32 height;
    u32 x;
    u32 y;
    u32 bits_per_pixel;
    const char* title;
    
    HINSTANCE hInstance;
    HWND hwnd;
    WNDCLASSEX wc;
    MSG msg;
    HDC hdc;
    HGLRC hrc;
    
    //struct hf_window* test;
    // TODO(salmoncatt): get these callbacks to work
    /* 
        struct{
            hf_key_callback key_callback;
            
        }callbacks;
     */
    
    void (*key_callback)(struct hf_window*, u32, u32);
    
} hf_window;


b8 hf_create_window(hf_window* window);
b8 hf_destroy_window(hf_window* window);

b8 hf_should_window_update(hf_window* window);
void hf_update_window(hf_window* window);
void hf_swap_buffers(hf_window* window);

LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


// NOTE(salmoncatt): input handling and callbacks

// NOTE(salmoncatt):     window handle      [callback function]         [keycode] [key up or down]
void hf_window_set_key_callback(hf_window* window, void (*hf_key_callback)(hf_window*, u32, u32));


#endif //_WINDOW_H
