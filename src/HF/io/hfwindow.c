#include "hfwindow.h"
#include "hfinput.h"
//#include <stdio.h>
//#include "hfpch.h"
//#include "../util/hfutil.h"

LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param){
    //memset(&hf_input_keys, 0, HF_KEY_LAST);
    //i8 was_down = !!(l_param & (1 << 30));
    i8 is_down =   !(l_param & (1 << 31));
    u64 key = w_param;
    
    if(msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP ||
       msg == WM_KEYDOWN || msg == WM_KEYUP){
        
        //hf_input_keys_old[key] = hf_input_keys[key];
        hf_input_keys[key] = is_down;
        
        //printf("key pressed: %u %u\n", hf_input_keys[HF_KEY_MINUS], hf_input_keys_old[HF_KEY_MINUS]);
        
    }
    //printf("key: %u\n", key, is_down);
    
    switch(msg)
    {
        case WM_CLOSE:
        PostQuitMessage(0);
        break;
        /* 
                case WM_CHAR:
                {
                    hf_input_keys[key] = is_down;
                    
                    return DefWindowProc(hwnd, msg, w_param, l_param);
                } break;
         */
        default:
        return DefWindowProc(hwnd, msg, w_param, l_param);
    }
    //return 0;
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
    
    w->timer_id = 0;
    
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
    /* 
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
     */
    PIXELFORMATDESCRIPTOR pfd = {};
    
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = w->bits_per_pixel;
    pfd.cDepthBits = w->bits_per_pixel;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
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
    
    // NOTE(salmoncatt): set the window size (and pos aparently)
    SetWindowPos(w->hwnd, NULL, w->x, w->y, w->width, w->height, SWP_SHOWWINDOW);
    
    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);
    
    if(!hf_gl_created)
        hf_gl_init();
    
    u32 major, minor;
    hf_gl_get_version(&major, &minor);
    
    int attribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor, 
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    
    
    w->hrc = wglCreateContextAttribsARB(w->hdc, 0, attribs);
    
    //set a basic 60fps window
    hf_window_set_ups(w, 60);
    
    hf_log("[HF] created window: [%s], size: [%u, %u], pos: [%u, %u]\n\n", w->title, w->width, w->height, w->x, w->y);
    
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
    window->x = 300;
    window->y = 200;
    window->bits_per_pixel = 32;
    window->title = "HF window";
}

b8 hf_should_window_update(hf_window* w){
    hf_update_window(w);
    return GetMessage(&w->msg, NULL, 0, 0);
}

void hf_update_window(hf_window* w){
    SwapBuffers(w->hdc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    TranslateMessage(&w->msg);
    DispatchMessage(&w->msg);
}

// NOTE(salmoncatt): windows needs this because the window needs some event to update it and a timer updates it at intervals
void hf_window_set_ups(hf_window* window, u32 ups){
    u32 interval = (u32)((f32)((1 / (f32)ups) * 1000));
    //hf_log("%i\n", interval);
    window->timer_id = SetTimer(window->hwnd, window->timer_id, interval, NULL);
}

void hf_window_remove_ups_constraint(hf_window* window){
    
}


// NOTE(salmoncatt): input handling and callbacks

void hf_window_set_key_callback(hf_window* w, void (*hf_key_callback)(hf_window*, u32, u32)){
    if(w->key_callback){
        free(w->key_callback);
    }
    
    w->key_callback = hf_key_callback;
}
