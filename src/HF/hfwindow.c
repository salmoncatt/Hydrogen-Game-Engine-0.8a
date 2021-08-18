#include "hfwindow.h"
#include <stdio.h>

LRESULT CALLBACK hf_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg)
    {
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