/* date = August 15th 2021 8:14 pm */

#ifndef _WINDOW_H
#define _WINDOW_H

//const char* hf_window_classname = "HF_WINDOW";

#include "math/hfmath.h"
#include <windows.h>

// NOTE(salmoncatt): do platform specific functions like foo (calls wfoo or xfoo)

typedef struct {
    u32 width;
    u32 height;
    u32 x;
    u32 y;
    
    HWND hwnd;
    WNDCLASSEX wc;
    MSG msg;
    HDC hdc;
    
    const char* title;
    
} hf_window;

b8 hf_create_window(hf_window* window);
void hf_update_window(hf_window* window);
b8 hf_should_window_update(hf_window* window);

LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);




#endif //_WINDOW_H
