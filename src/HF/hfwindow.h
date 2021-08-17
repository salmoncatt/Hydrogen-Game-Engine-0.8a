/* date = August 15th 2021 8:14 pm */

#ifndef _WINDOW_H
#define _WINDOW_H

//const char* hf_window_classname = "HF_WINDOW";

// NOTE(salmoncatt): do platform specific functions like foo (calls wfoo or xfoo)

typedef struct {
    u32 width;
    u32 height;
    u32 x;
    u32 y;
    
    HWND hwnd;
    WNDCLASSEX wc;
    MSG msg;
    
    const char* title;
    
} hf_window;

void create_window(hf_window* window);
LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);




#endif //_WINDOW_H
