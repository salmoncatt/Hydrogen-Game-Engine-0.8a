#include "hfwindow.h"
#include "hfinput.h"
//#include <stdio.h>
//#include "hfpch.h"
//#include "../util/hfutil.h"

LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param){
    i8 is_down =   !(l_param & (1 << 31));
    u64 key = w_param;
    
    if(msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP || msg == WM_KEYDOWN || msg == WM_KEYUP){
        //hf_input_keys[key] = is_down;
        
        // NOTE(salmoncatt): https://handmade.network/forums/articles/t/2823-keyboard_inputs_-_scancodes%252C_raw_input%252C_text_input%252C_key_names
        
        u32 scancode = ( l_param >> 16 ) & 0xff;
        u32 extended = ( l_param >> 24 ) & 0x1;
        
        if ( extended ) {
            
            if ( scancode != 0x45 ) {
                scancode |= 0xE000;
            }
            
        } else {
            
            if ( scancode == 0x45 ) {
                scancode = 0xE11D45;
            } else if ( scancode == 0x54 ) {
                scancode = 0xE037;
            }
        }
        hf_input_keys[scancode] = is_down;
        
        
        
        /* 
                                        if(key == HF_KEY_SHIFT){
                                            u32 state = GetKeyState(VK_SHIFT);
                                            if(state & 0x80000000){
                                                printf("l shift %u\n", is_down);
                                                hf_input_keys[HF_KEY_LEFT_SHIFT] = is_down;
                                            }else{
                                                printf("r shift %u\n", is_down);
                                                hf_input_keys[HF_KEY_RIGHT_SHIFT] = is_down;
                                            }
                                        }
                                 */
        
    }else if(msg == WM_LBUTTONDOWN){
        hf_input_buttons[HF_MOUSE_BUTTON_LEFT] = 1;
    }else if(msg == WM_LBUTTONUP){
        hf_input_buttons[HF_MOUSE_BUTTON_LEFT] = 0;
    }else if(msg == WM_RBUTTONDOWN){
        hf_input_buttons[HF_MOUSE_BUTTON_RIGHT] = 1;
    }else if(msg == WM_RBUTTONUP){
        hf_input_buttons[HF_MOUSE_BUTTON_RIGHT] = 0;
    }
    
    /* 
        if(key == VK_SHIFT){
            hf_log("SHIFT PRESSED\n");
        }
     */
    
    /* 
        if(msg == WM_ENTERSIZEMOVE){
            hf_log("resizing\n");
        }
        if(msg == WM_EXITSIZEMOVE){
            hf_log("stop resizing\n");
        }
     */
    
    switch(msg)
    {
        case WM_CLOSE:
        PostQuitMessage(0);
        break;
        
        default:
        return DefWindowProc(hwnd, msg, w_param, l_param);
    }
}

// TODO(salmoncatt): add focusing support    focus(hf_window*)

b8 hf_gl_load_extenstions(){
    WNDCLASSA window_class = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = DefWindowProcA,
        .hInstance = GetModuleHandle(0),
        .lpszClassName = "Dummy_WGL_djuasiodwa",
    };
    
    if (!RegisterClassA(&window_class)) {
        hf_err("Failed to register dummy OpenGL window.");
    }
    
    HWND dummy_window = CreateWindowExA(
                                        0,
                                        window_class.lpszClassName,
                                        "Dummy OpenGL Window",
                                        0,
                                        CW_USEDEFAULT,
                                        CW_USEDEFAULT,
                                        CW_USEDEFAULT,
                                        CW_USEDEFAULT,
                                        0,
                                        0,
                                        window_class.hInstance,
                                        0);
    
    if (!dummy_window) {
        hf_err("Failed to create dummy OpenGL window.");
    }
    
    HDC dummy_dc = GetDC(dummy_window);
    
    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(pfd),
        .nVersion = 1,
        .iPixelType = PFD_TYPE_RGBA,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .cColorBits = 32,
        .cAlphaBits = 8,
        .iLayerType = PFD_MAIN_PLANE,
        .cDepthBits = 24,
        .cStencilBits = 8,
    };
    
    i32 pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
    if (!pixel_format) {
        hf_err("Failed to find a suitable pixel format.");
    }
    if (!SetPixelFormat(dummy_dc, pixel_format, &pfd)) {
        hf_err("Failed to set the pixel format.");
    }
    
    HGLRC dummy_context = wglCreateContext(dummy_dc);
    if (!dummy_context) {
        hf_err("Failed to create a dummy OpenGL rendering context.");
    }
    
    if (!wglMakeCurrent(dummy_dc, dummy_context)) {
        hf_err("Failed to activate dummy OpenGL rendering context.");
    }
    
    
    if(!hf_gl_created)
        hf_gl_init();
    
    wglMakeCurrent(dummy_dc, 0);
    wglDeleteContext(dummy_context);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
}

b8 hf_create_window(hf_window* w){
    // NOTE(salmoncatt): for memory leak detection
    w->allocated = malloc(sizeof(void*));
    
    // NOTE(salmoncatt): set windows parameters
    w->wc.cbSize = w->cbSize;
    w->wc.style = w->style;
    //w->wc.style = CS_HREDRAW | CS_VREDRAW;
    w->wc.lpfnWndProc = w->lpfnWndProc;
    w->wc.cbClsExtra = w->cbClsExtra;
    w->wc.cbWndExtra = w->cbWndExtra;
    w->wc.hInstance = w->hInstance;
    w->wc.hIcon = w->hIcon;
    w->wc.hCursor = w->hCursor;
    w->wc.hbrBackground = w->hbrBackground;
    w->wc.lpszMenuName = w->lpszMenuName;
    w->wc.lpszClassName = w->lpszClassName;
    w->wc.hIconSm = w->hIconSm;
    
    
    // NOTE(salmoncatt): register window class into windows and check status
    if(!RegisterClassEx(&w->wc)){
        hf_err("couldn't register window: $hfcc{aqua}%s$hfcc{red}", w->title);
        return 0;
    }
    
    // NOTE(salmoncatt): create window and check status 
    w->hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "HF Window Class", w->title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w->width, w->height, NULL, NULL, w->hInstance, NULL);
    if(!w->hwnd){
        hf_err("couldn't create window: $hfcc{aqua}%s$hfcc{red}", w->title);
        return 0;
    }
    
    
    // TODO(salmoncatt): add better error handling
    
    w->hdc = GetDC(w->hwnd);
    if(!w->hdc)
        hf_err("couldn't create device context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    
    /* 
        // NOTE(salmoncatt): pixel format description for wgl
        PIXELFORMATDESCRIPTOR pfd = {};
        
        pfd.nSize = w->nSize;
        pfd.nVersion = w->nVersion;
        pfd.dwFlags = w->dwFlags;
        pfd.iPixelType = w->iPixelType;
        pfd.cColorBits = w->bits_per_pixel;
        pfd.cDepthBits = w->bits_per_pixel;
        pfd.iLayerType = w->iLayerType;
        
        // NOTE(salmoncatt): getting and setting pixel format
        u32 pixelFormat[1];
     */
    
    int pixel_format_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };
    
    i32 pixel_format;
    UINT num_formats;
    wglChoosePixelFormatARB(w->hdc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
    if (!num_formats) {
        hf_err("Failed to set the OpenGL 3.3 pixel format\n");
    }
    printf("works here\n");
    
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(w->hdc, pixel_format, sizeof(pfd), &pfd);
    if (!SetPixelFormat(w->hdc, pixel_format, &pfd)) {
        hf_err("Failed to set the OpenGL 3.3 pixel format\n");
    }
    
    /* 
        pixelFormat[0] = ChoosePixelFormat(w->hdc, &pfd);
        if (!pixelFormat)
        {
            hf_err("can't find an appropriate pixel format for window: $hfcc{aqua}%s$hfcc{red}", w->title);
            return 0;
        }
     */
    
    /* 
        if(!SetPixelFormat(w->hdc, pixelFormat[0], &pfd))
        {
            hf_err("unable to set pixel format for window: $hfcc{aqua}%s$hfcc{red}", w->title);
            return 0;
        }
     */
    
    int attribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3, 
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    
    
    w->hrc = wglCreateContextAttribsARB(w->hdc, 0, attribs);
    
    //w->hrc = wglCreateContext(w->hdc);
    if(!w->hrc)
        hf_err("unable to create OpenGL rendering context for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    
    // NOTE(salmoncatt): make opengl context current
    if(!wglMakeCurrent(w->hdc, w->hrc))
        hf_err("unable to make OpenGL rendering context current for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    
    
    
    // NOTE(salmoncatt): set the window size (and pos aparently)
    SetWindowPos(w->hwnd, NULL, w->x, w->y, w->width, w->height, SWP_SHOWWINDOW);
    
    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);
    
    
    u32 major, minor;
    hf_gl_get_version(&major, &minor);
    
    
    
    glEnable(GL_DEPTH_TEST);
    
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
    
    if(!UnregisterClass("HF Window Class", w->hInstance)){
        hf_err("unable to unregister window class for window: $hfcc{aqua}%s$hfcc{red}", w->title);
    }
    
    hf_free(w->allocated);
    
    // NOTE(salmoncatt): free callbacks
    if(w->key_callback)
        free(w->key_callback);
    
    return 1;
}

void hf_window_defaults(hf_window* window){
    window->width = 1000;
    window->height = 600;
    window->x = 300;
    window->y = 200;
    window->bits_per_pixel = 32;
    window->title = "HF window";
    window->vsync = 1;
    
    // NOTE(salmoncatt): set windows parameters
    window->cbSize = sizeof(WNDCLASSEX);
    window->style = 0;
    //w->wc.style = CS_HREDRAW | CS_VREDRAW;
    window->lpfnWndProc = hf_window_procedure;
    window->cbClsExtra = 0;
    window->cbWndExtra = 0;
    // NOTE(salmoncatt): in case not using winmain
    window->hInstance = GetModuleHandle(NULL);
    window->hIcon = LoadIcon(window->hInstance, MAKEINTRESOURCE(HF_ICON));;
    window->hCursor = LoadCursor(NULL, IDC_ARROW);
    window->hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    window->lpszMenuName = NULL;
    window->lpszClassName = "HF Window Class";
    window->hIconSm = LoadIcon(window->hInstance, MAKEINTRESOURCE(HF_ICON));
    
    window->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    window->nVersion = 1;
    window->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    window->iPixelType = PFD_TYPE_RGBA;
    window->iLayerType = PFD_MAIN_PLANE;
    
}

void hf_window_set_icon(hf_window* w, i32 icon_id){
    HICON hIcon = LoadIcon(w->hInstance, MAKEINTRESOURCE(icon_id));
    SendMessage(w->hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(w->hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}

b8 hf_should_window_update(hf_window* w){
    
    // NOTE(salmoncatt): peek message always the program to run without messages coming in or a timer, much better than getMessage
    MSG msg; //having this here instead of w->msg was the solution to days of pain
    
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) //Or use an if statement
    {
        if(msg.message == WM_QUIT){
            return 0;
        }
        
        TranslateMessage (&msg);
        DispatchMessage (&msg);
        
    }
    
    hf_update_window(w);
    return 1;
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
        w->x = rect.left;
        w->y = rect.top;
        //glViewport(0, 0, w->width, w->height);
    }
    
    POINT point;
    if(GetCursorPos(&point)){
        if(ScreenToClient(w->hwnd, &point)){
            hf_input_cursor_pos.x = point.x;
            hf_input_cursor_pos.y = point.y;
            
            //hf_log("[%li %li]\n", point.x, point.y);
            
            if(hf_input_cursor_pos.x < 0)
                hf_input_cursor_pos.x = 0;
            if(hf_input_cursor_pos.y < 0)
                hf_input_cursor_pos.y = 0;
        }
    }
    
    
    // NOTE(salmoncatt): i dont understand how but i managed to ooga booga this shit into working with so little code
    
    hf_input_center = hf_v2f(w->width / 2, w->height / 2);
    hf_input_cursor_movement = hf_sub_v2f(hf_input_cursor_pos, hf_input_cursor_pos_last);
    
    if(hf_input_cursor_visibility){
        hf_input_cursor_pos_last = hf_input_cursor_pos;
    }else{
        v2f input_movement = hf_v2f(hf_abs(hf_input_cursor_movement.x), hf_abs(hf_input_cursor_movement.y));
        
        if(input_movement.x > 0 || input_movement.y > 0){
            hf_window_set_cursor_pos(w, hf_input_center);
            POINT point;
            GetCursorPos(&point);
            
            hf_input_cursor_pos_last = hf_input_center;
        }
        
    }
    
    hf_input_cursor_visibility_last = hf_input_cursor_visibility;
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

void hf_swap_interval(b8 vsync){
    wglSwapIntervalEXT(vsync);
}

void hf_window_set_cursor_pos(hf_window* window, v2f pos){
    POINT p;
    p.x = (i32)pos.x;
    p.y = (i32)pos.y;
    ClientToScreen(window->hwnd, &p);
    SetCursorPos(p.x, p.y);
}
