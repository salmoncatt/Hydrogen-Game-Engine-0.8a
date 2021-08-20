#include "hfwindow.h"
#include <stdio.h>

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
        // release the RC
        if (!wglMakeCurrent(NULL,NULL))
        {
            MessageBox(NULL, "Unable to release rendering context", "Error", MB_OK | MB_ICONINFORMATION);
        }
        break;
        case WM_DESTROY:
        PostQuitMessage(0);
        // release the RC
        if (!wglMakeCurrent(NULL,NULL))
        {
            MessageBox(NULL, "Unable to release rendering context", "Error", MB_OK | MB_ICONINFORMATION);
        }
        break;
        default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// TODO(salmoncatt): add focusing support focus(hf_window*)

b8 hf_create_window(hf_window* w){
    // NOTE(salmoncatt): in case not using winmain
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    
    
    // NOTE(salmoncatt): set windows parameters
    w->wc.cbSize = sizeof(WNDCLASSEX);
    w->wc.style = 0;
    w->wc.lpfnWndProc = hf_window_procedure;
    w->wc.cbClsExtra = 0;
    w->wc.cbWndExtra = 0;
    w->wc.hInstance = hInstance;
    w->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    w->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    w->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    w->wc.lpszMenuName = NULL;
    w->wc.lpszClassName = w->title;
    w->wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    // NOTE(salmoncatt): register window class into windows and check status
    if(!RegisterClassEx(&w->wc)){
        printf("couldn't register window: %s\n", w->title);
        MessageBox(NULL, "couldn't register window", "error", MB_ICONERROR | MB_OK);
        return 0;
    }
    
    // NOTE(salmoncatt): create window and check status
    w->hwnd = CreateWindowEx(0, w->title, w->title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w->width, w->height, NULL, NULL, hInstance, NULL);
    if(w->hwnd == NULL){
        printf("couldn't create window: %s\n", w->title);
        MessageBox(NULL, "couldn't create window", "error", MB_ICONERROR | MB_OK);
        return 0;
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
    u32 pixelformat;
    
    if (!(pixelFormat = ChoosePixelFormat(g_hdc, &pfd)))
    {
        MessageBox(NULL, "Can't find an appropriate pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    
    if(!SetPixelFormat(g_hdc, pixelFormat,&pfd))
    {
        MessageBox(NULL, "Unable to set pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    
    
    // NOTE(salmoncatt): make opengl context
    if(!wglMakeCurrent(w->hdc, w->hrc))
    {
        MessageBox(NULL,"Unable to activate OpenGL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    
    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);
    
    return 1;
}

b8 hf_should_window_update(hf_window* w){
    return GetMessage(&w->msg, NULL, 0, 0);
}

void hf_update_window(hf_window* w){
    TranslateMessage(&w->msg);
    DispatchMessage(&w->msg);
}