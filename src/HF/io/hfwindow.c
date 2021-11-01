#include "hfwindow.h"
//#include <stdio.h>
//#include "hfpch.h"
//#include "../util/hfutil.h"

LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg)
    {
        case WM_CLOSE:
        PostQuitMessage(0);
        break;
        default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// TODO(salmoncatt): add focusing support    focus(hf_window*)

b8 hf_create_window(hf_window* w){
    // NOTE(salmoncatt): in case not using winmain
    w->hInstance = GetModuleHandle(NULL);
    
    // NOTE(salmoncatt): for memory leak detection
    w->allocated = malloc(sizeof(void*));
    
    // NOTE(salmoncatt): set windows parameters
    w->wc.cbSize = sizeof(WNDCLASSEX);
    w->wc.style = 0;
    w->wc.lpfnWndProc = hf_window_procedure;
    w->wc.cbClsExtra = 0;
    w->wc.cbWndExtra = 0;
    w->wc.hInstance = w->hInstance;
    w->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    w->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    w->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    w->wc.lpszMenuName = NULL;
    w->wc.lpszClassName = w->title;
    w->wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    // NOTE(salmoncatt): register window class into windows and check status
    if(!RegisterClassEx(&w->wc)){
        hf_err("couldn't register window: $hfcc{aqua}%s$hfcc{red}", w->title);
        return 0;
    }
    
    // NOTE(salmoncatt): create window and check status 
    w->hwnd = CreateWindowEx(0, w->title, w->title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w->width, w->height, NULL, NULL, w->hInstance, NULL);
    if(!w->hwnd){
        hf_err("couldn't create window: $hfcc{aqua}%s$hfcc{red}", w->title);
        return 0;
    }
    
    
    // TODO(salmoncatt): add better error handling
    
    w->hdc = GetDC(w->hwnd);
    if(!w->hdc)
        hf_err("couldn't create device context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    
    // NOTE(salmoncatt): pixel format description for wgl
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  // size of structure
        1,                              // default version
        PFD_DRAW_TO_WINDOW |            // window drawing support
            PFD_SUPPORT_OPENGL |            // OpenGL support
            PFD_DOUBLEBUFFER,               // double buffering support
        PFD_TYPE_RGBA,                  // RGBA color mode
        w->bits_per_pixel,                // color mode
        0, 0, 0, 0, 0, 0,               // ignore color bits, non-palettized mode
        0,                              // no alpha buffer
        0,                              // ignore shift bit
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // ignore accumulation bits
        16,                             // 16 bit z-buffer size
        8,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main drawing plane
        0,                              // reserved
        0, 0, 0 };                      // layer masks ignored
    
    
    // NOTE(salmoncatt): getting and setting pixel format
    u32 pixelFormat = ChoosePixelFormat(w->hdc, &pfd);
    
    if (!pixelFormat)
    {
        hf_err("can't find an appropriate pixel format for window: $hfcc{aqua}%s$hfcc{red}", w->title);
        return 0;
    }
    
    if(!SetPixelFormat(w->hdc, pixelFormat,&pfd))
    {
        hf_err("unable to set pixel format for window: $hfcc{aqua}%s$hfcc{red}", w->title);
        return 0;
    }
    
    // NOTE(salmoncatt): make opengl context
    w->hrc = wglCreateContext(w->hdc);
    if(!w->hrc)
        hf_err("unable to create OpenGL rendering context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    
    // NOTE(salmoncatt): make opengl context current
    if(!wglMakeCurrent(w->hdc, w->hrc))
        hf_err("unable to make OpenGL rendering context current for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    
    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);
    
    return 1;
}

b8 hf_destroy_window(hf_window* w){
    // NOTE(salmoncatt): destroy windows window things
    if(w->hrc){
        // release the RC
        if (!wglMakeCurrent(NULL,NULL))
            hf_err("unable to release rendering context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
        
        if (!wglDeleteContext(w->hrc))
            hf_err("unable to delete rendering context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
        
        w->hrc = NULL;
    }
    
    if(w->hdc && !ReleaseDC(w->hwnd, w->hdc)){
        hf_err("unable to release device context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
        w->hdc = NULL;
    }
    
    if(w->hwnd && !DestroyWindow(w->hwnd)){
        hf_err("unable to destroy window: $hfcc{aqua}%s$hfcc{red}", w->title);
        w->hwnd = NULL;
    }
    
    if(!UnregisterClass(w->title, w->hInstance)){
        hf_err("unable to unregister window class for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    }
    
    hf_free(w->allocated);
    
    // NOTE(salmoncatt): free callbacks
    if(w->key_callback)
        free(w->key_callback);
    
    return 1;
}

void hf_window_init(hf_window* window){
    window->width = 1000;
    window->height = 600;
    window->bits_per_pixel = 32;
    window->title = "what a goober";
}

b8 hf_should_window_update(hf_window* w){
    return GetMessage(&w->msg, NULL, 0, 0);
}

void hf_update_window(hf_window* w){
    TranslateMessage(&w->msg);
    DispatchMessage(&w->msg);
}

void hf_swap_buffers(hf_window* w){
    SwapBuffers(w->hdc);
}


// NOTE(salmoncatt): input handling and callbacks

void hf_window_set_key_callback(hf_window* w, void (*hf_key_callback)(hf_window*, u32, u32)){
    if(w->key_callback){
        free(w->key_callback);
    }
    
    w->key_callback = hf_key_callback;
}
