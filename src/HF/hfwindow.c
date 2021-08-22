#include "hfwindow.h"
#include <stdio.h>
#include "hfutil.h"

LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg)
    {
        /* 
                case WM_ACTIVATE:
                printf("goober0\n");
                break;
         */
        case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
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
        print_windows_last_error();
        printf("couldn't register window: %s\n", w->title);
        MessageBox(NULL, "couldn't register window", "error", MB_ICONERROR | MB_OK);
        return 0;
    }
    
    // NOTE(salmoncatt): create window and check status
    w->hwnd = CreateWindowEx(0, w->title, w->title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w->width, w->height, NULL, NULL, w->hInstance, NULL);
    if(!w->hwnd){
        print_windows_last_error();
        printf("couldn't create window: %s\n", w->title);
        MessageBox(NULL, "couldn't create window", "error", MB_ICONERROR | MB_OK);
        return 0;
    }
    
    
    // TODO(salmoncatt): add better error handling
    
    w->hdc = GetDC(w->hwnd);
    if(!w->hdc){
        print_windows_last_error();
        MessageBox(NULL, "couldn't create device context", "error", MB_ICONERROR | MB_OK);
    }
    
    // NOTE(salmoncatt): pixel format description for wgl
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  // size of structure
        1,                              // default version
        PFD_DRAW_TO_WINDOW |            // window drawing support
            PFD_SUPPORT_OPENGL |            // OpenGL support
            PFD_DOUBLEBUFFER,               // double buffering support
        PFD_TYPE_RGBA,                  // RGBA color mode
        w->bitsPerPixel,                // color mode
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
        print_windows_last_error();
        MessageBox(NULL, "Can't find an appropriate pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
        return 0;
    }
    
    if(!SetPixelFormat(w->hdc, pixelFormat,&pfd))
    {
        print_windows_last_error();
        MessageBox(NULL, "Unable to set pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
        return 0;
    }
    
    // NOTE(salmoncatt): make opengl context
    w->hrc = wglCreateContext(w->hdc);
    if(!w->hrc)
    {
        print_windows_last_error();
        MessageBox(NULL,"Unable to create OpenGL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    }
    
    // NOTE(salmoncatt): make opengl context current
    if(!wglMakeCurrent(w->hdc, w->hrc))
    {
        print_windows_last_error();
        MessageBox(NULL,"Unable to activate OpenGL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    }
    
    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);
    
    return 1;
}

b8 hf_destroy_window(hf_window* w){
    
    if(w->hrc){
        // release the RC
        if (!wglMakeCurrent(NULL,NULL))
        {
            print_windows_last_error();
            MessageBox(NULL, "Unable to release rendering context", "Error", MB_OK | MB_ICONINFORMATION);
        }
        
        if (!wglDeleteContext(w->hrc))
        {
            print_windows_last_error();
            MessageBox(NULL, "Unable to delete rendering context", "Error", MB_OK | MB_ICONINFORMATION);
        }
    }
    
    if(w->hdc && !ReleaseDC(w->hwnd, w->hdc)){
        print_windows_last_error();
        MessageBox(NULL, "Unable to release device context", "Error", MB_OK | MB_ICONINFORMATION);
        w->hdc = NULL;
    }
    
    if(w->hwnd && !DestroyWindow(w->hwnd)){
        print_windows_last_error();
        MessageBox(NULL, "Unable to destroy window", "Error", MB_OK | MB_ICONINFORMATION);
        w->hwnd = NULL;
    }
    
    if(!UnregisterClass(w->title, w->hInstance)){
        print_windows_last_error();
        MessageBox(NULL, "Unable to unregister window class", "Error", MB_OK | MB_ICONINFORMATION);
    }
    
    return 1;
}

b8 hf_should_window_update(hf_window* w){
    return GetMessage(&w->msg, NULL, 0, 0);
}

void hf_update_window(hf_window* w){
    TranslateMessage(&w->msg);
    DispatchMessage(&w->msg);
}