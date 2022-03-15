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
    
    if(msg == WM_ENTERSIZEMOVE){
        hf_log("resizing\n");
    }
    if(msg == WM_EXITSIZEMOVE){
        hf_log("stop resizing\n");
    }
    
    switch(msg)
    {
        case WM_DESTROY:
        PostQuitMessage(0);
        break;
        /* 
                case WM_ENTERSIZEMOVE:
                SetTimer(hwnd, 1, 0, NULL);
                return 0;
                case WM_EXITSIZEMOVE:
                KillTimer(hwnd, 1);
                return 0;
         */
        /* 
                case WM_SIZING:
                PostMessage(hwnd, WM_USER, 0, 0);
                break;
         */
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
    //w->wc.style = CS_HREDRAW | CS_VREDRAW;
    w->wc.lpfnWndProc = hf_window_procedure;
    w->wc.cbClsExtra = 0;
    w->wc.cbWndExtra = 0;
    w->wc.hInstance = w->hInstance;
    w->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    w->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    w->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    w->wc.lpszMenuName = NULL;
    w->wc.lpszClassName = "HF Window Class";
    w->wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    w->timer_id = 0;
    
    // NOTE(salmoncatt): register window class into windows and check status
    if(!RegisterClassEx(&w->wc)){
        hf_err("couldn't register window: $hfcc{aqua}%s$hfcc{red}", w->title);
        return 0;
    }
    
    // NOTE(salmoncatt): create window and check status 
    w->hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "HF Window Class", w->title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w->width, w->height, NULL, NULL, NULL, NULL);
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
    /* 
        PIXELFORMATDESCRIPTOR pfd = {};
        
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = w->bits_per_pixel;
        pfd.cDepthBits = w->bits_per_pixel;
        pfd.iLayerType = PFD_MAIN_PLANE;
        
        // NOTE(salmoncatt): getting and setting pixel format
        u32 pixelFormat[1];
        
        
        pixelFormat[0] = ChoosePixelFormat(w->hdc, &pfd);
        if (!pixelFormat)
        {
            hf_err("can't find an appropriate pixel format for window: $hfcc{aqua}%s$hfcc{red}", w->title);
            return 0;
        }
        
        if(!SetPixelFormat(w->hdc, pixelFormat[0], &pfd))
        {
            hf_err("unable to set pixel format for window: $hfcc{aqua}%s$hfcc{red}", w->title);
            return 0;
        }
        
        w->hrc = wglCreateContext(w->hdc);
        if(!w->hrc)
            hf_err("unable to create OpenGL rendering context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
        
        // NOTE(salmoncatt): make opengl context current
        if(!wglMakeCurrent(w->hdc, w->hrc))
            hf_err("unable to make OpenGL rendering context current for window: $hfcc{aqua}%s$hfcc{red}", w->title);
     */
    
    
    // NOTE(salmoncatt): set the window size (and pos aparently)
    SetWindowPos(w->hwnd, NULL, w->x, w->y, w->width, w->height, SWP_SHOWWINDOW);
    
    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);
    
    
    //if(!hf_gl_created)
    //hf_gl_init();
    
    /* 
        u32 attributeListInt[19];
        
        // Support for OpenGL rendering.
        attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
        attributeListInt[1] = 1;
        
        // Support for rendering to a window.
        attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
        attributeListInt[3] = 1;
        
        // Support for hardware acceleration.
        attributeListInt[4] = WGL_ACCELERATION_ARB;
        attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;
        
        // Support for 24bit color.
        attributeListInt[6] = WGL_COLOR_BITS_ARB;
        attributeListInt[7] = 24;
        
        // Support for 24 bit depth buffer.
        attributeListInt[8] = WGL_DEPTH_BITS_ARB;
        attributeListInt[9] = 24;
        
        // Support for double buffer.
        attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
        attributeListInt[11] = 1;
        
        // Support for swapping front and back buffer.
        attributeListInt[12] = WGL_SWAP_METHOD_ARB;
        attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;
        
        // Support for the RGBA pixel type.
        attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
        attributeListInt[15] = WGL_TYPE_RGBA_ARB;
        
        // Support for a 8 bit stencil buffer.
        attributeListInt[16] = WGL_STENCIL_BITS_ARB;
        attributeListInt[17] = 8;
        
        // Null terminate the attribute list.
        attributeListInt[18] = 0;
        
        u32 formatCount;
        
        // Query for a pixel format that fits the attributes we want.
        i32 result = wglChoosePixelFormatARB(w->hdc, attributeListInt, NULL, 1, pixelFormat, &formatCount);
        if(result != 1)
        {
            hf_err("[HF GL] couldn't load neccesary extensions\n");
        }
     */
    
    // If the video card/display can handle our desired pixel format then we set it as the current one.
    /* 
        result = SetPixelFormat(w->hdc, pixelFormat[0], &pfd);
        if(result != 1)
        {
            hf_err("[HF GL] couldn't set pixel format\n");
        }
     */
    
    
    
    /* 
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
        
        // NOTE(salmoncatt): make opengl context
        
        wglSwapIntervalEXT(1);
     */
    
    
    //set a basic 60fps window
    //hf_window_set_ups(w, 60);
    
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
    
    // NOTE(salmoncatt): peek message always the program to run without messages coming in or a timer, much better than getMessage
    
    /* 
        while(PeekMessage(&w->msg, 0, 0, 0, PM_REMOVE)){
            
            if(w->msg.message == WM_QUIT){
                return 0;
            }
            
            TranslateMessage(&w->msg);
            DispatchMessage(&w->msg);
        }
     */
    
    MSG msg;
    
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) //Or use an if statement
    {
        if(msg.message == WM_QUIT){
            return 0;
        }
        
        TranslateMessage (&msg);
        DispatchMessage (&msg);
        
    }
    
    /* 
        while(GetMessage(&w->msg, NULL, 0, 0) == FALSE){
            if(w->msg.message == WM_QUIT){
                return 0;
            }
            
            TranslateMessage(&w->msg);
            DispatchMessage(&w->msg);
        }
     */
    
    hf_update_window(w);
    return 1;
    //return GetMessage(&w->msg, NULL, 0, 0);
}

void hf_update_window(hf_window* w){
    SwapBuffers(w->hdc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    TranslateMessage(&w->msg);
    DispatchMessage(&w->msg);
    
    
    // NOTE(salmoncatt): update window size and openGL viewport
    RECT rect;
    if(GetWindowRect(w->hwnd, &rect)){
        w->width = rect.right - rect.left;
        w->height = rect.bottom - rect.top;
        glViewport(0, 0, w->width, w->height);
    }
    
    POINT point;
    if(GetCursorPos(&point)){
        if(ScreenToClient(w->hwnd, &point)){
            hf_input_cursor_pos.x = point.x;
            hf_input_cursor_pos.y = point.y;
            
            if(hf_input_cursor_pos.x < 0)
                hf_input_cursor_pos.x = 0;
            if(hf_input_cursor_pos.y < 0)
                hf_input_cursor_pos.y = 0;
            //hf_log("[%u %u]\n", point.x, point.y);
        }
    }
    
    // NOTE(salmoncatt): update window as fast as possible instead of when a message comes in
    //UpdateWindow(w->hwnd);
    //RedrawWindow(w->hwnd, NULL, NULL, RDW_UPDATENOW);
    
}


// NOTE(salmoncatt): input handling and callbacks

void hf_window_set_key_callback(hf_window* w, void (*hf_key_callback)(hf_window*, u32, u32)){
    if(w->key_callback){
        free(w->key_callback);
    }
    
    w->key_callback = hf_key_callback;
}


void hf_set_window_title(hf_window* window, const char* title){
    SetWindowText(window->hwnd, title);
}